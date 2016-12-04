#include "Ast.hpp"

int AstCodeNode::returnLabelIndex = 0;

/**
 * Hash set for data label names. Used by the AST during translation.
 */
std::set<unsigned> dataLabelNameHashes;

/**
 * djb2 hash function.
 */
unsigned int hash(const std::string& str)
{
    unsigned int hash = 5381;
    int c;
    const char* s = str.c_str();

    while (c = *s++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void printTabs(int depth)
{
    for( int i = 0; i < depth; i++ )
    {
        std::cout << "\t";
    }
}

AstCommentNode* generateAstComment(const std::vector<Token>& tokens, size_t& i)
{
    AstCommentNode* node = new AstCommentNode();

    Token t = tokens[i];
    node->text = t.text;

    return node;
}

AstExpressionNode* generateAstExpression(const std::vector<Token>& tokens, size_t& i, bool stopOnComma, bool singleExpression)
{
    Token t = tokens[i];

    AstExpressionNode* node = nullptr;

    while(true)
    {
        switch(t.type)
        {
        case TOKEN_POUND:
            // Immediate value
            {
                AstAddressingModeNode* n = new AstAddressingModeNode(EXPR_IMMEDIATE);
                n->child = generateAstExpression(tokens, ++i);
                return n;
            }
            break;
        case TOKEN_BIN_CONSTANT:
            {
                AstNumericConstantNode* n = new AstNumericConstantNode(EXPR_BIN_CONSTANT);
                n->value = t.text.substr(1);
                node = n;
            }
            break;
        case TOKEN_DEC_CONSTANT:
            {
                AstNumericConstantNode* n = new AstNumericConstantNode(EXPR_DEC_CONSTANT);
                n->value = t.text;
                node = n;
            }
            break;
        case TOKEN_HEX_CONSTANT:
            {
                AstNumericConstantNode* n = new AstNumericConstantNode(EXPR_HEX_CONSTANT);
                n->value = t.text.substr(1);
                node = n;
            }
            break;
        case TOKEN_NAME:
            {
                AstNameNode* n = new AstNameNode();
                n->text = t.text;
                node = n;
            }
            break;
        case TOKEN_LESS:
            {
                AstByteNode* n = new AstByteNode(EXPR_LOBYTE);
                n->name = new AstNameNode();
                n->name->text = tokens[++i].text;
                node = n;
            }
            break;
        case TOKEN_GREATER:
            {
                AstByteNode* n = new AstByteNode(EXPR_HIBYTE);
                n->name = new AstNameNode();
                n->name->text = tokens[++i].text;
                node = n;
            }
            break;
        case TOKEN_PLUS:
            {
                AstBinaryOperatorNode* n = new AstBinaryOperatorNode(EXPR_PLUS);
                n->lhs = node;
                n->rhs = generateAstExpression(tokens, ++i, stopOnComma, true);
                node = n;
            }
            break;
        case TOKEN_MINUS:
            {
                AstBinaryOperatorNode* n = new AstBinaryOperatorNode(EXPR_MINUS);
                n->lhs = node;
                n->rhs = generateAstExpression(tokens, ++i, stopOnComma, true);
                node = n;
            }
            break;
        case TOKEN_COMMA:
            {
                if( stopOnComma )
                {
                    return node;
                }
                else
                {
                    Token u = tokens[++i];
                    AstIndexNode* n;

                    if( u.type == TOKEN_X )
                    {
                        n = new AstIndexNode(EXPR_INDEX_X);
                    }
                    else
                    {
                        n = new AstIndexNode(EXPR_INDEX_Y);
                    }
                    n->child = node;

                    node = n;
                }
            }
            break;
        case TOKEN_RIGHT_PAREN:
            {
                AstAddressingModeNode* n = new AstAddressingModeNode(EXPR_INDIRECT);
                n->child = node;
                node = n;
            }
            break;
        case TOKEN_LEFT_PAREN:
            break;
        default:
            return node;
        }

        if( singleExpression )
        {
            return node;
        }


        if( ++i >= tokens.size() )
            return node;
        t = tokens[i];
    }
}

AstConstantNode* generateAstConstant(const std::vector<Token>& tokens, size_t& i)
{
    AstConstantNode* node = new AstConstantNode();

    Token t = tokens[i];   // name
    Token u = tokens[++i]; // =

    if( u.type != TOKEN_EQUALS )
    {
        // todo error
    }

    node->name = t.text;

    // Parse the rhs expression
    node->value = generateAstExpression(tokens, ++i);

    return node;
}

AstCodeNode* generateAstCode(const std::vector<Token>& tokens, size_t& i)
{
    Token t = tokens[i];

    AstCodeNode* node = new AstCodeNode();
    node->instruction = t.text;
    node->operand = generateAstExpression(tokens, ++i);

    return node;
}

AstDataNode* generateAstData(const std::vector<Token>& tokens, size_t& i)
{
    Token t = tokens[i];

    AstDataNode* node = new AstDataNode();
    if( t.text.compare(".db") == 0 )
    {
        node->bits = 8;
    }
    else
    {
        node->bits = 16;
    }

    // generate children
    while(i < tokens.size() - 1)
    {
        AstExpressionNode* expr = generateAstExpression(tokens, ++i, true);
        if( expr == nullptr  )
        {
            if( tokens[i].type == TOKEN_COMMA )
                continue;
            break;
        }
        node->data.push_back(expr);
    }
    i--;
    if( i == tokens.size() - 1 )
        i++;
    return node;
}

AstLabelNode* generateAstLabel(const std::vector<Token>& tokens, size_t& i)
{
    AstLabelNode* node = new AstLabelNode();

    Token t = tokens[i];
    node->name = t.text.substr(0, t.text.length() - 1);

    // generate children
    AstNode* child;
    while(i + 1 < tokens.size())
    {
        t = tokens[++i];
        switch(t.type)
        {
            case TOKEN_LDA:
            case TOKEN_LDX:
            case TOKEN_LDY:
            case TOKEN_STA:
            case TOKEN_STX:
            case TOKEN_STY:
            case TOKEN_TAX:
            case TOKEN_TAY:
            case TOKEN_TXA:
            case TOKEN_TYA:
            case TOKEN_TSX:
            case TOKEN_TXS:
            case TOKEN_PHA:
            case TOKEN_PHP:
            case TOKEN_PLA:
            case TOKEN_PLP:
            case TOKEN_AND:
            case TOKEN_EOR:
            case TOKEN_ORA:
            case TOKEN_BIT:
            case TOKEN_ADC:
            case TOKEN_SBC:
            case TOKEN_CMP:
            case TOKEN_CPX:
            case TOKEN_CPY:
            case TOKEN_INC:
            case TOKEN_INX:
            case TOKEN_INY:
            case TOKEN_DEC:
            case TOKEN_DEX:
            case TOKEN_DEY:
            case TOKEN_ASL:
            case TOKEN_LSR:
            case TOKEN_ROL:
            case TOKEN_ROR:
            case TOKEN_JMP:
            case TOKEN_JSR:
            case TOKEN_RTS:
            case TOKEN_BCC:
            case TOKEN_BCS:
            case TOKEN_BEQ:
            case TOKEN_BMI:
            case TOKEN_BNE:
            case TOKEN_BPL:
            case TOKEN_BVC:
            case TOKEN_BVS:
            case TOKEN_CLC:
            case TOKEN_CLD:
            case TOKEN_CLI:
            case TOKEN_CLV:
            case TOKEN_SEC:
            case TOKEN_SED:
            case TOKEN_SEI:
            case TOKEN_BRK:
            case TOKEN_NOP:
            case TOKEN_RTI:
                // Instruction
                child = generateAstCode(tokens, i);
                child->parent = node;
                node->children.push_back(child);
                break;
            case TOKEN_DIRECTIVE:
                // Data
                child = generateAstData(tokens, i);
                child->parent = node;
                node->children.push_back(child);
                break;
            case TOKEN_NEWLINE:
                // ignore
                break;
            case TOKEN_LABEL:
                i--;
                return node;
            default:
                return node;
        }
    }

    return node;
}

AstRootNode* generateAst(const std::vector<Token>& tokens)
{
    AstRootNode* node = new AstRootNode();

    for( size_t i = 0; i < tokens.size(); i++ )
    {
        Token t = tokens[i];
        switch(t.type)
        {
        case TOKEN_COMMENT:
            //node->children.push_back(generateAstComment(tokens, i));
            break;
        case TOKEN_NAME:
            if( tokens[i + 1].type == TOKEN_EQUALS )
            {
                AstNode* n = generateAstConstant(tokens, i);
                node->children.push_back(n);
            }
            break;
        case TOKEN_LABEL:
            {
                AstNode* n = generateAstLabel(tokens, i);
                node->children.push_back(n);
            }
            break;

        default:
            break;
        }
    }

    return node;
}
