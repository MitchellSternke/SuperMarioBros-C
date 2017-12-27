%error-verbose

%{
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "ast.hpp"
#include "translator.hpp"

extern int yylex();
extern FILE* yyin;
extern int yylineno;

RootNode* root = NULL;

void yyerror(const char* s);

// Short hand for an instruction AST node
// there are so many of them, so this saves some typing
//
#define INST(r, c, o) \
    r = new InstructionNode(c, o); r->lineNumber = yylineno
%}

%union {
    const char* str;
    AstNode* node;
    ListNode* list;
    InstructionNode* instruction;
}

%token<str> DIRECTIVE 
%token<str> NAME 
%token<str> LABEL 
%token DATABYTES
%token DATAWORDS
%token<str> HEXCONST
%token<str> BINCONST
%token<str> DECCONST
%token LDA
%token LDX
%token LDY
%token STA
%token STX
%token STY
%token TAX
%token TAY
%token TXA
%token TYA
%token TSX
%token TXS
%token PHA
%token PHP
%token PLA
%token PLP
%token AND
%token EOR
%token ORA
%token BIT
%token ADC
%token SBC
%token CMP
%token CPX
%token CPY
%token INC
%token INX
%token INY
%token DEC
%token DEX
%token DEY
%token ASL
%token LSR
%token ROL
%token ROR
%token JMP
%token JSR
%token RTS
%token BCC
%token BCS
%token BEQ
%token BMI
%token BNE
%token BPL
%token BVC
%token BVS
%token CLC
%token CLD
%token CLI
%token CLV
%token SEC
%token SED
%token SEI
%token BRK
%token NOP
%token RTI

%type <node> decl
%type <node> section
%type <list> code
%type <node> data
%type <list> dlist
%type <instruction> inst
%type <str> const
%type <node> expr
%type <node> iexpr

%%

program: plist
       ;

plist: dir
     | decl 
        {
            root->children.push_back($1);
            $1->parent = root;
        }
     | section
        {
            root->children.push_back($1);
            $1->parent = root;
        }
     | plist dir
     | plist decl 
        {
            root->children.push_back($2);
            $2->parent = root;
        }
     | plist section
        {
            root->children.push_back($2);
            $2->parent = root;
        }
     ;

dir: DIRECTIVE const 
   ;

decl: NAME '=' expr 
        {
            $$ = new DeclNode($1, $3);
        }
    ;

section: LABEL code
        {
            $$ = new LabelNode($1, $2);
            $2->parent = $$;
        }
       | LABEL section
        {
            $$ = new LabelNode($1, $2);
            $2->parent = $$;
        }
       ;

code: inst
        {
            $$ = new ListNode();
            $$->value.node = $1;
            $1->parent = $$;
        }
    | data
        {
            $$ = new ListNode();
            $$->value.node = $1;
            $1->parent = $$;
        }
    | code inst
        {
            $$ = new ListNode();
            $$->value.node = $2;
            $2->parent = $$;
            $$->next = $1;
        }
    | code data
        {
            $$ = new ListNode();
            $$->value.node = $2;
            $2->parent = $$;
            $$->next = $1;
        }
    ;
    
data: DATABYTES dlist
        {
            $$ = new AstNode(AST_DATA8);
            $$->value.node = $2;
            $2->parent = $$;
        }
    | DATAWORDS dlist
        {
            $$ = new AstNode(AST_DATA16);
            $$->value.node = $2;
            $2->parent = $$;
        }
    ;

dlist: expr
        {
            $$ = new ListNode();
            $$->value.node = $1;
            $1->parent = $$;
        }
     | dlist ',' expr
        {
            $$ = new ListNode();
            $$->value.node = $3;
            $3->parent = $$;
            $$->next = $1;
        }
     ;
     
inst: LDA iexpr { INST($$, LDA, $2); }
    | LDX iexpr { INST($$, LDX, $2); }
    | LDY iexpr { INST($$, LDY, $2); }
    | STA iexpr { INST($$, STA, $2); }
    | STX iexpr { INST($$, STX, $2); }
    | STY iexpr { INST($$, STY, $2); }
    | TAX       { INST($$, TAX, NULL); }
    | TAY       { INST($$, TAY, NULL); }
    | TXA       { INST($$, TXA, NULL); }
    | TYA       { INST($$, TYA, NULL); }
    | TSX       { INST($$, TSX, NULL); }
    | TXS       { INST($$, TXS, NULL); }
    | PHA       { INST($$, PHA, NULL); }
    | PHP       { INST($$, PHP, NULL); }
    | PLA       { INST($$, PLA, NULL); }
    | PLP       { INST($$, PLP, NULL); }
    | AND iexpr { INST($$, AND, $2); }
    | EOR iexpr { INST($$, EOR, $2); }
    | ORA iexpr { INST($$, ORA, $2); }
    | BIT iexpr { INST($$, BIT, $2); }
    | ADC iexpr { INST($$, ADC, $2); }
    | SBC iexpr { INST($$, SBC, $2); }
    | CMP iexpr { INST($$, CMP, $2); }
    | CPX iexpr { INST($$, CPX, $2); }
    | CPY iexpr { INST($$, CPY, $2); }
    | INC iexpr { INST($$, INC, $2); }
    | INX       { INST($$, INX, NULL); }
    | INY       { INST($$, INY, NULL); }
    | DEC iexpr { INST($$, DEC, $2); }
    | DEX       { INST($$, DEX, NULL); }
    | DEY       { INST($$, DEY, NULL); }
    | ASL       { INST($$, ASL, NULL); }
    | ASL iexpr { INST($$, ASL, $2); }
    | LSR       { INST($$, LSR, NULL); }
    | LSR iexpr { INST($$, LSR, $2); }
    | ROL       { INST($$, ROL, NULL); }
    | ROL iexpr { INST($$, ROL, $2); }
    | ROR       { INST($$, ROR, NULL); }
    | ROR iexpr { INST($$, ROR, $2); }
    | JMP iexpr { INST($$, JMP, $2); }
    | JSR NAME  { INST($$, JSR, $2); }
    | RTS       { INST($$, RTS, NULL); }
    | BCC NAME  { INST($$, BCC, $2); }
    | BCS NAME  { INST($$, BCS, $2); }
    | BEQ NAME  { INST($$, BEQ, $2); }
    | BMI NAME  { INST($$, BMI, $2); }
    | BNE NAME  { INST($$, BNE, $2); }
    | BPL NAME  { INST($$, BPL, $2); }
    | BVC NAME  { INST($$, BVC, $2); }
    | BVS NAME  { INST($$, BVS, $2); }
    | CLC       { INST($$, CLC, NULL); }
    | CLD       { INST($$, CLD, NULL); }
    | CLI       { INST($$, CLI, NULL); }
    | CLV       { INST($$, CLV, NULL); }
    | SEC       { INST($$, SEC, NULL); }
    | SED       { INST($$, SED, NULL); }
    | SEI       { INST($$, SEI, NULL); }
    | BRK       { INST($$, BRK, NULL); }
    | NOP       { INST($$, NOP, NULL); }
    | RTI       { INST($$, RTI, NULL); }
    ;

const: HEXCONST
        {
            $$ = $1;
        }
     | BINCONST
        {
            $$ = $1;
        }
     | DECCONST
        {
            $$ = $1;
        }
     ;

expr: NAME
        {
            $$ = new AstNode(AST_NAME, $1);
        }
    | const
        {
            $$ = new AstNode(AST_CONST, $1);
        }
    | '#' expr
        {
            $$ = new UnaryNode(AST_IMMEDIATE, $2);
        }
    | expr '+' expr
        {
            $$ = new BinaryNode(AST_ADD, $1, $3);
        }
    | expr '-' expr
        {
            $$ = new BinaryNode(AST_SUBTRACT, $1, $3);
        }
    | '<' expr
        {
            $$ = new UnaryNode(AST_LOBYTE, $2);
        }
    | '>' expr
        {
            $$ = new UnaryNode(AST_HIBYTE, $2);
        }
    | '(' expr ')'
        {
            $$ = new UnaryNode(AST_INDIRECT, $2);
        }
    ;

iexpr: expr
        {
            $$ = $1;
        }
     | expr ',' 'x'
        {
            $$ = new UnaryNode(AST_INDEXED_X, $1);
        }
     | expr ',' 'y'
        {
            $$ = new UnaryNode(AST_INDEXED_Y, $1);
        }
     ;

%%

int main(int argc, char** argv)
{
    root = new RootNode();
    
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    
    cleanupAst(root);
    
    /*
    for (std::list<AstNode*>::iterator it = root->children.begin(); it != root->children.end(); ++it)
    {
        AstNode* node = (*it);
        printNode(node);
    }
    */

    Translator translator(argv[1], root);

    std::ofstream sourceFile("SMB.cpp");
    sourceFile << translator.getSourceOutput();

    std::ofstream dataHeaderFile("SMBDataPointers.hpp");
    dataHeaderFile << translator.getDataHeaderOutput();

    std::ofstream constantHeaderFile("SMBConstants.hpp");
    constantHeaderFile << translator.getConstantHeaderOutput();
    
    return 0;
}

void yyerror(const char* s)
{
    printf("Parse error: %s\n", s);
    exit(-1);
}
