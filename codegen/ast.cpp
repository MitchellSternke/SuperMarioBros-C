#include <cstring>

#include "ast.hpp"

static const OpcodeInfo opcodeTable[] = {
    {"adc", Opcode::ADC, OperandSyntax::Required},
    {"and", Opcode::AND, OperandSyntax::Required},
    {"asl", Opcode::ASL, OperandSyntax::Optional},
    {"bcc", Opcode::BCC, OperandSyntax::Label},
    {"bcs", Opcode::BCS, OperandSyntax::Label},
    {"beq", Opcode::BEQ, OperandSyntax::Label},
    {"bit", Opcode::BIT, OperandSyntax::Required},
    {"bmi", Opcode::BMI, OperandSyntax::Label},
    {"bne", Opcode::BNE, OperandSyntax::Label},
    {"bpl", Opcode::BPL, OperandSyntax::Label},
    {"brk", Opcode::BRK, OperandSyntax::None},
    {"bvc", Opcode::BVC, OperandSyntax::Label},
    {"bvs", Opcode::BVS, OperandSyntax::Label},
    {"clc", Opcode::CLC, OperandSyntax::None},
    {"cld", Opcode::CLD, OperandSyntax::None},
    {"cli", Opcode::CLI, OperandSyntax::None},
    {"clv", Opcode::CLV, OperandSyntax::None},
    {"cmp", Opcode::CMP, OperandSyntax::Required},
    {"cpx", Opcode::CPX, OperandSyntax::Required},
    {"cpy", Opcode::CPY, OperandSyntax::Required},
    {"dec", Opcode::DEC, OperandSyntax::Required},
    {"dex", Opcode::DEX, OperandSyntax::None},
    {"dey", Opcode::DEY, OperandSyntax::None},
    {"eor", Opcode::EOR, OperandSyntax::Required},
    {"inc", Opcode::INC, OperandSyntax::Required},
    {"inx", Opcode::INX, OperandSyntax::None},
    {"iny", Opcode::INY, OperandSyntax::None},
    {"jmp", Opcode::JMP, OperandSyntax::Required},
    {"jsr", Opcode::JSR, OperandSyntax::Label},
    {"lda", Opcode::LDA, OperandSyntax::Required},
    {"ldx", Opcode::LDX, OperandSyntax::Required},
    {"ldy", Opcode::LDY, OperandSyntax::Required},
    {"lsr", Opcode::LSR, OperandSyntax::Optional},
    {"nop", Opcode::NOP, OperandSyntax::None},
    {"ora", Opcode::ORA, OperandSyntax::Required},
    {"pha", Opcode::PHA, OperandSyntax::None},
    {"php", Opcode::PHP, OperandSyntax::None},
    {"pla", Opcode::PLA, OperandSyntax::None},
    {"plp", Opcode::PLP, OperandSyntax::None},
    {"rol", Opcode::ROL, OperandSyntax::Optional},
    {"ror", Opcode::ROR, OperandSyntax::Optional},
    {"rti", Opcode::RTI, OperandSyntax::None},
    {"rts", Opcode::RTS, OperandSyntax::None},
    {"sbc", Opcode::SBC, OperandSyntax::Required},
    {"sec", Opcode::SEC, OperandSyntax::None},
    {"sed", Opcode::SED, OperandSyntax::None},
    {"sei", Opcode::SEI, OperandSyntax::None},
    {"sta", Opcode::STA, OperandSyntax::Required},
    {"stx", Opcode::STX, OperandSyntax::Required},
    {"sty", Opcode::STY, OperandSyntax::Required},
    {"tax", Opcode::TAX, OperandSyntax::None},
    {"tay", Opcode::TAY, OperandSyntax::None},
    {"tsx", Opcode::TSX, OperandSyntax::None},
    {"txa", Opcode::TXA, OperandSyntax::None},
    {"txs", Opcode::TXS, OperandSyntax::None},
    {"tya", Opcode::TYA, OperandSyntax::None},
};

const OpcodeInfo* findOpcode(const char* mnemonic)
{
    for (const OpcodeInfo& info : opcodeTable)
    {
        if (std::strcmp(info.mnemonic, mnemonic) == 0)
        {
            return &info;
        }
    }
    return nullptr;
}
