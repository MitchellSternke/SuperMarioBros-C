%define parse.error verbose
%locations

%code requires {
#include <string>
#include <vector>

#include "ast.hpp"
}

%code provides {
// Parse a 6502 assembly file. Exits with an error message on failure.
Program parseProgram(const std::string& path);

// The program currently being parsed (also receives comments from the lexer).
extern Program* parsedProgram;

int yylex();
void yyerror(const char* message);
}

%code {
#include <cstdio>
#include <cstdlib>
#include <utility>

Program* parsedProgram = nullptr;

static std::string take(std::string* text)
{
    std::string result = std::move(*text);
    delete text;
    return result;
}

static Label* makeLabel(std::string* name, int line)
{
    Label* label = new Label();
    label->name = take(name);
    label->line = line;
    return label;
}

static Expr* makeExpr(ExprType type, Expr* lhs, Expr* rhs = nullptr)
{
    return new Expr{type, "", lhs, rhs};
}

static Expr* makeLeaf(ExprType type, std::string* text)
{
    return new Expr{type, take(text)};
}

static Statement* makeStatement(Statement::Kind kind, int line)
{
    Statement* statement = new Statement();
    statement->kind = kind;
    statement->line = line;
    return statement;
}

static Statement* makeInstruction(Opcode opcode, Expr* operand, int line)
{
    Statement* statement = makeStatement(Statement::Kind::Instruction, line);
    statement->opcode = opcode;
    statement->operand = operand;
    return statement;
}

static Statement* makeData(Statement::Kind kind, std::vector<Expr*>* data, int line)
{
    Statement* statement = makeStatement(kind, line);
    statement->data = std::move(*data);
    delete data;
    return statement;
}

// A run of consecutive labels shares one block of statements: every label but
// the last becomes an alias for the address of the last one.
//
static void addSection(std::vector<Label*>* labels, std::vector<Statement*>* statements)
{
    Label* owner = labels->back();
    owner->statements = std::move(*statements);
    switch (owner->statements.front()->kind)
    {
    case Statement::Kind::Instruction: owner->type = LabelType::Code; break;
    case Statement::Kind::Bytes:       owner->type = LabelType::Data; break;
    case Statement::Kind::Words:
        std::fprintf(stderr, "line %d: label '%s' cannot start with .dw\n", owner->line, owner->name.c_str());
        std::exit(EXIT_FAILURE);
    }

    for (Label* label : *labels)
    {
        if (label != owner)
        {
            label->line = 0;
        }
        parsedProgram->labels.push_back(label);
    }
    delete labels;
    delete statements;
}
}

%union {
    std::string* text;
    Opcode opcode;
    Expr* expr;
    Decl* decl;
    Statement* statement;
    std::vector<Expr*>* exprs;
    std::vector<Label*>* labels;
    std::vector<Statement*>* statements;
}

%token <text> DIRECTIVE NAME LABEL HEXCONST BINCONST DECCONST
%token <opcode> OP_IMPLIED OP_REQUIRED OP_OPTIONAL OP_LABEL
%token DATABYTES DATAWORDS

%type <text> constant
%type <expr> expr operand
%type <exprs> exprs
%type <decl> decl
%type <labels> labels
%type <statement> statement instruction
%type <statements> statements

// "asl Name" takes Name as its operand rather than starting a new declaration,
// and the unary operators (#, <, >) apply to the whole expression that follows.
//
%precedence ACCUMULATOR
%precedence NAME
%precedence '#' '<' '>'
%left '+' '-'

%%

program
    : %empty
    | program directive
    | program decl              { parsedProgram->decls.push_back($2); }
    | program labels statements { addSection($2, $3); }
    ;

directive
    : DIRECTIVE constant        { delete $1; delete $2; }
    ;

decl
    : NAME '=' expr             { $$ = new Decl{take($1), $3, @1.first_line}; }
    ;

labels
    : LABEL                     { $$ = new std::vector<Label*>{makeLabel($1, @1.first_line)}; }
    | labels LABEL              { $$ = $1; $$->push_back(makeLabel($2, @2.first_line)); }
    ;

statements
    : statement                 { $$ = new std::vector<Statement*>{$1}; }
    | statements statement      { $$ = $1; $$->push_back($2); }
    ;

statement
    : instruction
    | DATABYTES exprs           { $$ = makeData(Statement::Kind::Bytes, $2, @1.first_line); }
    | DATAWORDS exprs           { $$ = makeData(Statement::Kind::Words, $2, @1.first_line); }
    ;

instruction
    : OP_IMPLIED                        { $$ = makeInstruction($1, nullptr, @1.first_line); }
    | OP_OPTIONAL %prec ACCUMULATOR     { $$ = makeInstruction($1, nullptr, @1.first_line); }
    | OP_OPTIONAL operand               { $$ = makeInstruction($1, $2, @1.first_line); }
    | OP_REQUIRED operand               { $$ = makeInstruction($1, $2, @1.first_line); }
    | OP_LABEL NAME                     { $$ = makeInstruction($1, makeLeaf(ExprType::Name, $2), @1.first_line); }
    ;

exprs
    : expr                      { $$ = new std::vector<Expr*>{$1}; }
    | exprs ',' expr            { $$ = $1; $$->push_back($3); }
    ;

constant
    : HEXCONST
    | BINCONST
    | DECCONST
    ;

expr
    : NAME                      { $$ = makeLeaf(ExprType::Name, $1); }
    | constant                  { $$ = makeLeaf(ExprType::Constant, $1); }
    | '#' expr                  { $$ = makeExpr(ExprType::Immediate, $2); }
    | '<' expr                  { $$ = makeExpr(ExprType::LowByte, $2); }
    | '>' expr                  { $$ = makeExpr(ExprType::HighByte, $2); }
    | '(' expr ')'              { $$ = makeExpr(ExprType::Indirect, $2); }
    | expr '+' expr             { $$ = makeExpr(ExprType::Add, $1, $3); }
    | expr '-' expr             { $$ = makeExpr(ExprType::Subtract, $1, $3); }
    ;

operand
    : expr
    | expr ',' 'x'              { $$ = makeExpr(ExprType::IndexedX, $1); }
    | expr ',' 'y'              { $$ = makeExpr(ExprType::IndexedY, $1); }
    ;

%%

extern FILE* yyin;

Program parseProgram(const std::string& path)
{
    yyin = std::fopen(path.c_str(), "r");
    if (yyin == nullptr)
    {
        std::fprintf(stderr, "Unable to open \"%s\"\n", path.c_str());
        std::exit(EXIT_FAILURE);
    }

    Program program;
    parsedProgram = &program;
    yyparse();
    std::fclose(yyin);
    parsedProgram = nullptr;

    return program;
}

void yyerror(const char* message)
{
    std::fprintf(stderr, "Parse error: %s\n", message);
    std::exit(EXIT_FAILURE);
}
