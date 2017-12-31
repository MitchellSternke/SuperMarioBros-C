%option noyywrap
%option yylineno

%{
#include <string.h>
#include "ast.hpp"
#include "util.hpp"
#include "parser.hpp"

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

void yyerror(const char *);
%}

%%
[ \t\r\n]+ {
    ;
}

;.* {
    mapComment(yylineno, yytext);
}

\.db {
    return DATABYTES;
}

\.dw {
    return DATAWORDS;
}

\.[a-z]+ {
    yylval.str = DUP_YYTEXT;
    return DIRECTIVE;
}

[a-zA-Z]+[a-zA-Z0-9_]*: {
    yylval.str = DUP_YYTEXT;
    return LABEL;
}

x {
    return *yytext;
}

y {
    return *yytext;
}

lda {
    return LDA;
}

ldx {
    return LDX;
}

ldy {
    return LDY;
}

sta {
    return STA;
}

stx {
    return STX;
}

sty {
    return STY;
}

tax {
    return TAX;
}

tay {
    return TAY;
}

txa {
    return TXA;
}

tya {
    return TYA;
}

tsx {
    return TSX;
}

txs {
    return TXS;
}

pha {
    return PHA;
}

php {
    return PHP;
}

pla {
    return PLA;
}

plp {
    return PLP;
}

and {
    return AND;
}

eor {
    return EOR;
}

ora {
    return ORA;
}

bit {
    return BIT;
}

adc {
    return ADC;
}

sbc {
    return SBC;
}

cmp {
    return CMP;
}

cpx {
    return CPX;
}

cpy {
    return CPY;
}

inc {
    return INC;
}

inx {
    return INX;
}

iny {
    return INY;
}

dec {
    return DEC;
}

dex {
    return DEX;
}

dey {
    return DEY;
}

asl {
    return ASL;
}

lsr {
    return LSR;
}

rol {
    return ROL;
}

ror {
    return ROR;
}

jmp {
    return JMP;
}

jsr {
    return JSR;
}

rts {
    return RTS;
}

bcc {
    return BCC;
}

bcs {
    return BCS;
}

beq {
    return BEQ;
}

bmi {
    return BMI;
}

bne {
    return BNE;
}

bpl {
    return BPL;
}

bvc {
    return BVC;
}

bvs {
    return BVS;
}

clc {
    return CLC;
}

cld {
    return CLD;
}

cli {
    return CLI;
}

clv {
    return CLV;
}

sec {
    return SEC;
}

sed {
    return SED;
}

sei {
    return SEI;
}

brk {
    return BRK;
}

nop {
    return NOP;
}

rti {
    return RTI;
}

[a-zA-Z]+[a-zA-Z0-9_]* {
    yylval.str = DUP_YYTEXT;
    return NAME;
}

\$[0-9A-Fa-f]+ {
    yylval.str = DUP_YYTEXT;
    return HEXCONST;
}

%[0|1]+ {
    yylval.str = DUP_YYTEXT;
    return BINCONST;
}

[0-9]+ {
    yylval.str = DUP_YYTEXT;
    return DECCONST;
}

= {
    return *yytext;
}

\+ {
    return *yytext;
}

\- {
    return *yytext;
}

\< {
    return *yytext;
}

\> {
    return *yytext;
}

# {
    return *yytext;
}

, {
    return *yytext;
}

\( {
    return *yytext;
}

\) {
    return *yytext;
}

. {
    printf("invalid token (line %d): %s\n", yylineno, yytext);
    yyerror(yytext);
}

%%
