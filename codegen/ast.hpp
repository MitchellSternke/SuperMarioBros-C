#ifndef AST_HPP
#define AST_HPP

#include <map>
#include <string>
#include <vector>

// The 6502 instructions understood by the assembler front end.
//
enum class Opcode
{
    ADC, AND, ASL, BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS, CLC,
    CLD, CLI, CLV, CMP, CPX, CPY, DEC, DEX, DEY, EOR, INC, INX, INY, JMP,
    JSR, LDA, LDX, LDY, LSR, NOP, ORA, PHA, PHP, PLA, PLP, ROL, ROR, RTI,
    RTS, SBC, SEC, SED, SEI, STA, STX, STY, TAX, TAY, TSX, TXA, TXS, TYA
};

// How the operand of an instruction is written in the assembly source.
//
enum class OperandSyntax
{
    None,       // e.g. "tax"
    Required,   // e.g. "lda #$00"
    Optional,   // e.g. "asl" (accumulator) or "asl $00"
    Label       // e.g. "jsr Subroutine", "bne Loop"
};

struct OpcodeInfo
{
    const char* mnemonic;
    Opcode opcode;
    OperandSyntax operandSyntax;
};

// Look up an instruction by its (lowercase) mnemonic. Returns nullptr for non-instructions.
//
const OpcodeInfo* findOpcode(const char* mnemonic);

enum class ExprType
{
    Name,
    Constant,
    Immediate,  // #expr
    Indirect,   // (expr)
    IndexedX,   // expr,x
    IndexedY,   // expr,y
    LowByte,    // <expr
    HighByte,   // >expr
    Add,
    Subtract
};

// AST nodes are created by the parser and live until the program exits.
//
struct Expr
{
    ExprType type;
    std::string text;     // Name and Constant only
    Expr* lhs = nullptr;  // Operand of unary expressions, left side of binary ones
    Expr* rhs = nullptr;  // Right side of binary expressions
};

// An instruction or a data directive (.db/.dw) beneath a label.
//
struct Statement
{
    enum class Kind { Instruction, Bytes, Words };

    Kind kind;
    int line = 0;
    Opcode opcode = Opcode::NOP;  // Instructions only
    Expr* operand = nullptr;      // Instructions only (branch targets are Name expressions)
    std::vector<Expr*> data;      // Data directives only
};

enum class LabelType
{
    Alias, // Shares its address with the label that follows it
    Code,
    Data
};

struct Label
{
    std::string name; // Without the trailing ':'
    int line = 0;     // Zero for aliases
    LabelType type = LabelType::Alias;
    std::vector<Statement*> statements;
};

// A constant declaration such as "PPU_STATUS = $2002".
//
struct Decl
{
    std::string name;
    Expr* value;
    int line;
};

struct Program
{
    std::vector<Decl*> decls;
    std::vector<Label*> labels;
    std::map<int, std::string> comments; // Source line -> comment text (without the leading ';')
};

#endif // AST_HPP
