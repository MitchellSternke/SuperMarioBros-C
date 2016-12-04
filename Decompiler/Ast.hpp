#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <list>
#include <set>
#include <vector>

#include "Token.hpp"

extern std::set<unsigned> dataLabelNameHashes;
unsigned int hash(const std::string& str);

enum AstNodeType
{
    AST_ROOT,
    AST_COMMENT, // Can be under root or attached to a code/constant node

    AST_CONSTANT,
    AST_LABEL,

    AST_CODE,
    AST_DATA,

    AST_EXPRESSION
};

// Flag that is set when we encounter .db $2c (BIT instruction)
// This sabotages the next instruction, so we need to translate these into goto's that skip the next instruction
static bool skipNextInstruction = false;
static int skipNextInstructionIndex = 0;

void printTabs(int depth);

/**
 * Optional parameters for translation.
 */
struct TranslationParams
{
    bool substituteNames; /**< Whether names should be substituted with addresses e.g. Name -> Name__addr */

    TranslationParams()
    {
        substituteNames = false;
    }
};

struct AstNode
{
    AstNodeType type;
    AstNode* parent;

    AstNode() {parent = nullptr;}
    virtual ~AstNode() {}
    virtual int getSize() const {return 0;}
    virtual void print(int depth)=0;
    virtual std::string translate(TranslationParams* params) const {return "";}
};

struct AstRootNode : public AstNode
{
    std::list<AstNode*> children;

    AstRootNode() {this->type = AST_ROOT;}
    ~AstRootNode()
    {
        // TODO
    }

    void print(int depth)
    {
        for( auto& node : children )
        {
            node->print(depth);
        }
    }
};

struct AstCommentNode : public AstNode
{
    std::string text;

    AstCommentNode() {this->type = AST_COMMENT;}

    void print(int depth)
    {
        printTabs(depth);
        std::cout << "comment: " << text << std::endl;
    }
};

struct AstLabelNode : public AstNode
{
    std::string name;
    std::list<AstNode*> children;

    AstLabelNode() {this->type = AST_LABEL;}
    ~AstLabelNode()
    {
        // TODO
    }

    void print(int depth)
    {
        printTabs(depth);
        std::cout << "label: " << name << std::endl;
        for( auto& node : children )
        {
            node->print(depth + 1);
        }
    }
};

struct AstConstantNode : public AstNode
{
    std::string name;
    AstNode* value;
    AstNode* comment;

    AstConstantNode()
    {
        this->type = AST_CONSTANT;
        value = nullptr;
        comment = nullptr;
    }
    ~AstConstantNode()
    {
        // TODO
    }

    void print(int depth)
    {
        printTabs(depth);
        std::cout << "constant: " << name << std::endl;
        if( value != nullptr )
            value->print(depth + 1);
    }

    std::string translate(TranslationParams* params) const
    {
        return std::string("#define ") + name + " " + value->translate(params);
    }
};

enum AstExpressionType
{
    EXPR_BIN_CONSTANT,
    EXPR_DEC_CONSTANT,
    EXPR_HEX_CONSTANT,
    EXPR_IMMEDIATE,
    EXPR_INDIRECT,
    EXPR_PLUS,
    EXPR_MINUS,
    EXPR_INDEX_X,
    EXPR_INDEX_Y,
    EXPR_NAME,
    EXPR_HIBYTE,
    EXPR_LOBYTE
};

struct AstExpressionNode : public AstNode
{
    AstExpressionType expressionType;

    AstExpressionNode() {this->type = AST_EXPRESSION;}
    AstExpressionNode(AstExpressionType type) {this->type = AST_EXPRESSION; this->expressionType = type;}
    virtual ~AstExpressionNode() {}

    std::string translateAsOperand(TranslationParams* params) const
    {
        if( expressionType == EXPR_IMMEDIATE )
        {
            return translate(params);
        }
        else
        {
            return "M(" + translate(params) + ")";
        }
    }
};

struct AstNumericConstantNode : public AstExpressionNode
{
    std::string value;

    AstNumericConstantNode(AstExpressionType type) {this->expressionType = type;}

    void print(int depth)
    {
        printTabs(depth);
        switch(expressionType)
        {
        case EXPR_BIN_CONSTANT:
            std::cout << "0b" << value << std::endl;
            break;
        case EXPR_DEC_CONSTANT:
            std::cout << value << std::endl;
            break;
        case EXPR_HEX_CONSTANT:
            std::cout << "0x" << value << std::endl;
            break;
        }
    }

    std::string translate(TranslationParams* params) const
    {
        switch(expressionType)
        {
        case EXPR_BIN_CONSTANT:
            return std::string("BOOST_BINARY(") + value + ")";
        case EXPR_DEC_CONSTANT:
            return value;
        case EXPR_HEX_CONSTANT:
            return std::string("0x") + value;
        }
    }
};

struct AstDataNode : public AstNode
{
    int bits;
    std::list<AstNode*> data;
    AstNode* comment;

    AstDataNode() {this->type = AST_DATA;}
    ~AstDataNode()
    {
        // TODO
    }

    void print(int depth)
    {
        printTabs(depth);
        std::cout << "data (" << bits << "-bit)" << std::endl;
        for( auto& node : data )
        {
            node->print(depth + 1);
        }
    }

    std::string translate(TranslationParams* params) const
    {
        // Only translate the special case: .db $2c
        if( data.size() == 1 )
        {
            AstNode* node = data.back();
            if( node->type == AST_EXPRESSION )
            {
                AstExpressionNode* expr = static_cast<AstExpressionNode*>(node);
                if( expr->expressionType == EXPR_HEX_CONSTANT )
                {
                    AstNumericConstantNode* constant = static_cast<AstNumericConstantNode*>(expr);
                    if( constant->value.compare("2c") == 0 )
                    {
                        // .db $2c
                        // We need to goto the next instruction
                        skipNextInstruction = true;
                        char indexStr[8];
                        sprintf(indexStr, "%d", skipNextInstructionIndex);
                        return std::string("\tgoto Skip_") + indexStr + ";\n";
                    }
                }
            }
        }

        return "";
    }
};

struct AstBinaryOperatorNode : public AstExpressionNode
{
    AstExpressionNode* lhs;
    AstExpressionNode* rhs;
    AstBinaryOperatorNode(AstExpressionType type) {this->expressionType = type;}
    ~AstBinaryOperatorNode()
    {
        // TODO
    }

    void print(int depth)
    {
        printTabs(depth);
        switch(expressionType)
        {
        case EXPR_PLUS:
            std::cout << "add\n";
            break;
        case EXPR_MINUS:
            std::cout << "sub\n";
            break;
        }
        lhs->print(depth + 1);
        rhs->print(depth + 1);
    }

    std::string translate(TranslationParams* params) const
    {
        std::string op = " + ";
        if( expressionType == EXPR_MINUS )
        {
            op = " - ";
        }
        return lhs->translate(params) + op + rhs->translate(params);
    }
};

struct AstAddressingModeNode : public AstExpressionNode
{
    AstExpressionNode* child;
    AstAddressingModeNode(AstExpressionType type) {this->expressionType = type;}
    ~AstAddressingModeNode()
    {
        // TODO
    }

    void print(int depth)
    {
        printTabs(depth);
        switch(expressionType)
        {
        case EXPR_IMMEDIATE:
            std::cout << "immediate\n";
            break;
        case EXPR_INDIRECT:
            std::cout << "indirect\n";
            break;
        }
        child->print(depth + 1);
    }

    std::string translate(TranslationParams* params) const
    {
        if( expressionType == EXPR_IMMEDIATE )
        {
            return child->translate(params);
        }
        else
        {
            return std::string("M(") + child->translate(params) + ")";
        }
    }
};

struct AstNameNode : public AstExpressionNode
{
    std::string text;

    AstNameNode() {this->expressionType = EXPR_NAME;}

    void print(int depth)
    {
        printTabs(depth);
        std::cout << "name: " << text << std::endl;
    }

    std::string translate(TranslationParams* params) const
    {
        /*
        if( params && params->substituteNames && dataLabelNameHashes.find(hash(text)) != dataLabelNameHashes.end() )
        {
            return text + "__addr";
        }
        else*/ if( text.compare("$07d6") == 0 )
        {
            return "0x07d6";
        }
        else if( text.compare("$07fe") == 0 )
        {
            return "0x07fe";
        }
        else
        {
            return text;
        }
    }
};

struct AstByteNode : public AstExpressionNode
{
    AstNameNode* name;

    AstByteNode(AstExpressionType type)
    {
        this->expressionType = type;
        name = nullptr;
    }
    ~AstByteNode()
    {
        delete name;
    }

    void print(int depth)
    {
        printTabs(depth);
        if( expressionType == EXPR_LOBYTE )
            std::cout << "low byte" << std::endl;
        else
            std::cout << "high byte" << std::endl;
        name->print(depth + 1);
    }

    std::string translate(TranslationParams* params) const
    {
        if( expressionType == EXPR_LOBYTE )
        {
            return std::string("LOBYTE(") + name->translate(params) + ")";
        }
        else
        {
            return std::string("HIBYTE(") + name->translate(params) + ")";
        }
    }
};

struct AstIndexNode : public AstExpressionNode
{
    AstExpressionNode* child;

    AstIndexNode(AstExpressionType type)
    {
        child = nullptr;
        this->expressionType = type;
    }

    ~AstIndexNode()
    {
        delete child;
    }

    void print(int depth)
    {
        printTabs(depth);
        switch(expressionType)
        {
        case EXPR_INDEX_X:
            std::cout << "x" << std::endl;
            break;
        case EXPR_INDEX_Y:
            std::cout << "y" << std::endl;
            break;
        }
        child->print(depth + 1);
    }

    std::string translate(TranslationParams* params) const
    {
        if( expressionType == EXPR_INDEX_X )
        {
            return child->translate(params) + " + x";
        }
        else // EXPR_INDEX_Y
        {
            // Special case for indirect indexed addressing
            AstAddressingModeNode* indirect = static_cast<AstAddressingModeNode*>(child);
            if (indirect != nullptr && indirect->expressionType == EXPR_INDIRECT)
            {
                return std::string("W(") + indirect->child->translate(params) + ") + y";
            }
            else
            {
                return child->translate(params) + " + y";
            }
        }
    }
};

struct AstCodeNode : public AstNode
{
    std::string instruction;
    AstExpressionNode* operand;
    AstNode* comment;
    static int returnLabelIndex;

    AstCodeNode()
    {
        this->type = AST_CODE;
        operand = nullptr;
        comment = nullptr;
    }
    ~AstCodeNode()
    {
        // TODO
    }

    void print(int depth)
    {
        printTabs(depth);
        std::cout << "code: " << instruction << std::endl;
        if( operand != nullptr )
            operand->print(depth + 1);
    }

    std::string translateHelper(TranslationParams* params) const
    {
        std::string result = "\t";
        if( instruction.compare("lda") == 0 )
        {
            result += "a = " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("ldx") == 0 )
        {
            result += "x = " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("ldy") == 0 )
        {
            result += "y = " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("sta") == 0 )
        {
            result += std::string("writeData(") + operand->translate(params) + ", a)";
        }
        else if( instruction.compare("stx") == 0 )
        {
            result += std::string("writeData(") + operand->translate(params) + ", x)";
        }
        else if( instruction.compare("sty") == 0 )
        {
            result += std::string("writeData(") + operand->translate(params) + ", y)";
        }
        else if( instruction.compare("tax") == 0 )
        {
            result += "x = a";
        }
        else if( instruction.compare("tay") == 0 )
        {
            result += "y = a";
        }
        else if( instruction.compare("tsx") == 0 )
        {
            result += "x = s";
        }
        else if( instruction.compare("txa") == 0 )
        {
            result += "a = x";
        }
        else if( instruction.compare("txs") == 0 )
        {
            result += "s = x";
        }
        else if( instruction.compare("tya") == 0 )
        {
            result += "a = y";
        }
        else if( instruction.compare("pha") == 0 || instruction.compare("pla") == 0 )
        {
            result += instruction + "()";
        }
        else if( instruction.compare("and") == 0 )
        {
            result += "a &= " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("eor") == 0 )
        {
            result += "a ^= " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("ora") == 0 )
        {
            result += "a |= " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("bit") == 0 )
        {
            result += "bit(" + operand->translateAsOperand(params) + ")";
        }
        else if( instruction.compare("adc") == 0)
        {
            result += "a += " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("sbc") == 0 )
        {
            result += "a -= " + operand->translateAsOperand(params);
        }
        else if( instruction.compare("cmp") == 0 )
        {
            result += "compare(a, " + operand->translateAsOperand(params) + ")";
        }
        else if( instruction.compare("cpx") == 0 )
        {
            result += "compare(x, " + operand->translateAsOperand(params) + ")";
        }
        else if( instruction.compare("cpy") == 0 )
        {
            result += "compare(y, " + operand->translateAsOperand(params) + ")";
        }
        else if( instruction.compare("inc") == 0 )
        {
            result += std::string("++") + operand->translateAsOperand(params);
        }
        else if( instruction.compare("inx") == 0 )
        {
            result += "++x";
        }
        else if( instruction.compare("iny") == 0 )
        {
            result += "++y";
        }
        else if( instruction.compare("dec") == 0 )
        {
            result += std::string("--") + operand->translateAsOperand(params);
        }
        else if( instruction.compare("dex") == 0 )
        {
            result += "--x";
        }
        else if( instruction.compare("dey") == 0 )
        {
            result += "--y";
        }
        else if( instruction.compare("asl") == 0 )
        {
            if( operand )
            {
                result += operand->translateAsOperand(params) + " <<= 1";
            }
            else
            {
                result += "a <<= 1";
            }
        }
        else if( instruction.compare("lsr") == 0 )
        {
            if( operand )
            {
                result += operand->translateAsOperand(params) + " >>= 1";
            }
            else
            {
                result += "a >>= 1";
            }
        }
        else if( instruction.compare("rol") == 0 )
        {
            if( operand )
            {
                result += operand->translateAsOperand(params) + ".rol()";
            }
            else
            {
                result += "a.rol()";
            }
        }
        else if( instruction.compare("ror") == 0 )
        {
            if( operand )
            {
                result += operand->translateAsOperand(params) + ".ror()";
            }
            else
            {
                result += "a.ror()";
            }
        }
        else if( instruction.compare("bcc") == 0 )
        {
            result += std::string("if( !c )\n\t\tgoto ") + static_cast<AstNameNode*>(operand)->text;
        }
        else if( instruction.compare("bcs") == 0 )
        {
            result += std::string("if( c )\n\t\tgoto ") + static_cast<AstNameNode*>(operand)->text;
        }
        else if( instruction.compare("bpl") == 0 )
        {
            result += std::string("if( !n )\n\t\tgoto ") + static_cast<AstNameNode*>(operand)->text;
        }
        else if( instruction.compare("bmi") == 0 )
        {
            result += std::string("if( n )\n\t\tgoto ") + static_cast<AstNameNode*>(operand)->text;
        }
        else if( instruction.compare("beq") == 0 )
        {
            result += std::string("if( z )\n\t\tgoto ") + static_cast<AstNameNode*>(operand)->text;
        }
        else if( instruction.compare("bne") == 0 )
        {
            result += std::string("if( !z )\n\t\tgoto ") + static_cast<AstNameNode*>(operand)->text;
        }
        else if( instruction.compare("sec") == 0 )
        {
            result += "c = 1";
        }
        else if( instruction.compare("clc") == 0 )
        {
            result += "c = 0";
        }
        else if( instruction.compare("jmp") == 0 )
        {
            if( operand->expressionType == EXPR_NAME )
            {
                AstNameNode* name = static_cast<AstNameNode*>(operand);
                if( name->text.compare("EndlessLoop") == 0 )
                {
                    // Special case: power-on initialization is over
                    result += "return; // Initialization complete\n\n//---------------------------------------------------------------------\n\n";
                    return result;
                }
                else
                {
                    result += "goto " + operand->translate(params);
                }
            }
            else
            {
                // TODO: indirect jump!
                std::cout << "Warning: indirect jump detected" << std::endl;
            }
        }
        else if( instruction.compare("jsr") == 0 )
        {
            AstNameNode* name = static_cast<AstNameNode*>(operand);
            if( name->text.compare("JumpEngine") == 0 )
            {
                // Special case. Create a jump table
                result += "switch(a)\n\t{\n";

                AstLabelNode* parentLabel = static_cast<AstLabelNode*>(parent);
                bool foundSelf = false;
                int index = 0;
                for( auto& c : parentLabel->children )
                {
                    if( c == this )
                    {
                        foundSelf = true;
                        continue;
                    }
                    if( foundSelf )
                    {
                        AstDataNode* d = static_cast<AstDataNode*>(c);
                        AstNameNode* dataName = static_cast<AstNameNode*>(d->data.front());
                        char indexStr[4];
                        sprintf(indexStr, "%d", index++);
                        result += std::string("\tcase ") + indexStr + ":\n\t\tgoto " + dataName->text + ";\n";
                    }
                }
                result += "\t}\n";
                return result;
            }
            else
            {
                char returnLabelIndexStr[8];
                sprintf(returnLabelIndexStr, "%d", returnLabelIndex++);
                result += "JSR(" + operand->translate(params) + ", " + returnLabelIndexStr + ")\n";
                return result;
            }
        }
        else if( instruction.compare("rts") == 0 )
        {
            result += "goto Return;\n\n//---------------------------------------------------------------------\n\n";
            return result;
        }
        else if( instruction.compare("rti") == 0 )
        {
            result += "return; // RTI\n\n//---------------------------------------------------------------------\n\n";
            return result;
        }
        else if( instruction.compare("sei") == 0 || instruction.compare("cld") == 0 )
        {
            // These instructions don't do anything useful, so we'll ignore them
            return "";
        }
        else
        {
            std::cout << "Unhandled instruction: " << instruction << std::endl;
        }
        result += ";\n";
        return result;
    }

    std::string translate(TranslationParams* params) const
    {
        std::string translation = translateHelper(params);

        // Add a skip label after this instruction if we need to
        if( skipNextInstruction )
        {
            char indexStr[8];
            sprintf(indexStr, "%d", skipNextInstructionIndex++);
            translation += std::string("Skip_") + indexStr + ":\n";
            skipNextInstruction = false;
        }

        return translation;
    }
};

AstCommentNode* generateAstComment(const std::vector<Token>& tokens, size_t& i);
AstExpressionNode* generateAstExpression(const std::vector<Token>& tokens, size_t& i, bool stopOnComma = false, bool singleExpression = false);
AstConstantNode* generateAstConstant(const std::vector<Token>& tokens, size_t& i);
AstCodeNode* generateAstCode(const std::vector<Token>& tokens, size_t& i);
AstDataNode* generateAstData(const std::vector<Token>& tokens, size_t& i);
AstLabelNode* generateAstLabel(const std::vector<Token>& tokens, size_t& i);
AstRootNode* generateAst(const std::vector<Token>& tokens);

#endif // AST_HPP
