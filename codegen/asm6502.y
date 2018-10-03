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
#define INST(t, r, c, o) \
    r = new InstructionNode(c, o); r->lineNumber = t.first_line;
%}

%locations

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
            $$->lineNumber = @1.first_line;
        }
    ;

section: LABEL code
        {
            $$ = new LabelNode($1, $2);
            $$->lineNumber = @1.first_line;
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
            $$->lineNumber = @1.first_line;
            $$->value.node = $2;
            $2->parent = $$;
        }
    | DATAWORDS dlist
        {
            $$ = new AstNode(AST_DATA16);
            $$->lineNumber = @1.first_line;
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
     
inst: LDA iexpr { INST(@1, $$, LDA, $2); }
    | LDX iexpr { INST(@1, $$, LDX, $2); }
    | LDY iexpr { INST(@1, $$, LDY, $2); }
    | STA iexpr { INST(@1, $$, STA, $2); }
    | STX iexpr { INST(@1, $$, STX, $2); }
    | STY iexpr { INST(@1, $$, STY, $2); }
    | TAX       { INST(@1, $$, TAX, NULL); }
    | TAY       { INST(@1, $$, TAY, NULL); }
    | TXA       { INST(@1, $$, TXA, NULL); }
    | TYA       { INST(@1, $$, TYA, NULL); }
    | TSX       { INST(@1, $$, TSX, NULL); }
    | TXS       { INST(@1, $$, TXS, NULL); }
    | PHA       { INST(@1, $$, PHA, NULL); }
    | PHP       { INST(@1, $$, PHP, NULL); }
    | PLA       { INST(@1, $$, PLA, NULL); }
    | PLP       { INST(@1, $$, PLP, NULL); }
    | AND iexpr { INST(@1, $$, AND, $2); }
    | EOR iexpr { INST(@1, $$, EOR, $2); }
    | ORA iexpr { INST(@1, $$, ORA, $2); }
    | BIT iexpr { INST(@1, $$, BIT, $2); }
    | ADC iexpr { INST(@1, $$, ADC, $2); }
    | SBC iexpr { INST(@1, $$, SBC, $2); }
    | CMP iexpr { INST(@1, $$, CMP, $2); }
    | CPX iexpr { INST(@1, $$, CPX, $2); }
    | CPY iexpr { INST(@1, $$, CPY, $2); }
    | INC iexpr { INST(@1, $$, INC, $2); }
    | INX       { INST(@1, $$, INX, NULL); }
    | INY       { INST(@1, $$, INY, NULL); }
    | DEC iexpr { INST(@1, $$, DEC, $2); }
    | DEX       { INST(@1, $$, DEX, NULL); }
    | DEY       { INST(@1, $$, DEY, NULL); }
    | ASL       { INST(@1, $$, ASL, NULL); }
    | ASL iexpr { INST(@1, $$, ASL, $2); }
    | LSR       { INST(@1, $$, LSR, NULL); }
    | LSR iexpr { INST(@1, $$, LSR, $2); }
    | ROL       { INST(@1, $$, ROL, NULL); }
    | ROL iexpr { INST(@1, $$, ROL, $2); }
    | ROR       { INST(@1, $$, ROR, NULL); }
    | ROR iexpr { INST(@1, $$, ROR, $2); }
    | JMP iexpr { INST(@1, $$, JMP, $2); }
    | JSR NAME  { INST(@1, $$, JSR, $2); }
    | RTS       { INST(@1, $$, RTS, NULL); }
    | BCC NAME  { INST(@1, $$, BCC, $2); }
    | BCS NAME  { INST(@1, $$, BCS, $2); }
    | BEQ NAME  { INST(@1, $$, BEQ, $2); }
    | BMI NAME  { INST(@1, $$, BMI, $2); }
    | BNE NAME  { INST(@1, $$, BNE, $2); }
    | BPL NAME  { INST(@1, $$, BPL, $2); }
    | BVC NAME  { INST(@1, $$, BVC, $2); }
    | BVS NAME  { INST(@1, $$, BVS, $2); }
    | CLC       { INST(@1, $$, CLC, NULL); }
    | CLD       { INST(@1, $$, CLD, NULL); }
    | CLI       { INST(@1, $$, CLI, NULL); }
    | CLV       { INST(@1, $$, CLV, NULL); }
    | SEC       { INST(@1, $$, SEC, NULL); }
    | SED       { INST(@1, $$, SED, NULL); }
    | SEI       { INST(@1, $$, SEI, NULL); }
    | BRK       { INST(@1, $$, BRK, NULL); }
    | NOP       { INST(@1, $$, NOP, NULL); }
    | RTI       { INST(@1, $$, RTI, NULL); }
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
    if (argc < 3)
    {
        printf("usage: codegen <INPUT ASM FILE> <OUTPUT ROOT DIRECTORY>\n");
        exit(1);
    }

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

    std::string outputDir(argv[2]);

    std::string sourceFilePath = outputDir + "/source/SMB/SMB.cpp";
    std::ofstream sourceFile(sourceFilePath.c_str());
    sourceFile << translator.getSourceOutput();

    std::string dataFilePath = outputDir + "/source/SMB/SMBData.cpp";
    std::ofstream dataFile(dataFilePath.c_str());
    dataFile << translator.getDataOutput();

    std::string dataHeaderFilePath = outputDir + "/source/SMB/SMBDataPointers.hpp";
    std::ofstream dataHeaderFile(dataHeaderFilePath.c_str());
    dataHeaderFile << translator.getDataHeaderOutput();

    std::string constantHeaderFilePath = outputDir + "/source/SMB/SMBConstants.hpp";
    std::ofstream constantHeaderFile(constantHeaderFilePath.c_str());
    constantHeaderFile << translator.getConstantHeaderOutput();
    
    return 0;
}

void yyerror(const char* s)
{
    printf("Parse error: %s\n", s);
    exit(-1);
}
