%option noyywrap nounput noinput nounistd never-interactive yylineno

%{
#include <cstdio>

#include "parser.hpp"

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

static std::string* copyText()
{
    return new std::string(yytext, yyleng);
}

// Instructions are recognised as identifiers first, then classified by
// the shape of their operand so the grammar stays small.
//
static int identifierToken()
{
    const OpcodeInfo* info = findOpcode(yytext);
    if (info == nullptr)
    {
        yylval.text = copyText();
        return NAME;
    }

    yylval.opcode = info->opcode;
    switch (info->operandSyntax)
    {
    case OperandSyntax::None:     return OP_IMPLIED;
    case OperandSyntax::Required: return OP_REQUIRED;
    case OperandSyntax::Optional: return OP_OPTIONAL;
    case OperandSyntax::Label:    return OP_LABEL;
    }
    return NAME;
}
%}

IDENTIFIER [a-zA-Z][a-zA-Z0-9_]*

%%

[ \t\r\n]+          ;
;[^\r\n]*           parsedProgram->comments[yylineno] = yytext + 1;
\.db                return DATABYTES;
\.dw                return DATAWORDS;
\.[a-z]+            { yylval.text = copyText(); return DIRECTIVE; }
{IDENTIFIER}:       { yylval.text = new std::string(yytext, yyleng - 1); return LABEL; }
[xy]                return *yytext;
{IDENTIFIER}        return identifierToken();
\$[0-9A-Fa-f]+      { yylval.text = copyText(); return HEXCONST; }
%[01]+              { yylval.text = copyText(); return BINCONST; }
[0-9]+              { yylval.text = copyText(); return DECCONST; }
[-=+<>#,()]         return *yytext;
.                   {
                        std::fprintf(stderr, "line %d: invalid token '%s'\n", yylineno, yytext);
                        yyerror("invalid token");
                    }

%%
