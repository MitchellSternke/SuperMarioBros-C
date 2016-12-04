#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <regex>
#include <vector>

#include "Token.hpp"
#include "Ast.hpp"
#include "Translator.hpp"

static int nameCounter = 0;

static std::string getNameCounter()
{
    return std::to_string(nameCounter++);
}

// Translate a branch expression
static std::string translateBranch(std::vector<Token>& tokens, size_t& index, const std::string& branchFunction)
{
    Token t = tokens[++index];

    std::string result = "\tif(" + branchFunction + "())\n\t\tgoto ";
    switch(t.type)
    {
    case TOKEN_NAME:
        result += t.text;
        break;
    default:
        break;
    }
    result += ";";

    return result;
}

// Translate the data in a .db or .dw directive
static std::string translateData(std::vector<Token>& tokens, size_t& index)
{   Token t = tokens[++index];

    std::string result;
    while(true)
    {
        switch(t.type)
        {
        case TOKEN_BIN_CONSTANT:
            result += "BOOST_BINARY(" + t.text.substr(1) + ")";
            break;
        case TOKEN_DEC_CONSTANT:
            result += t.text;
            break;
        case TOKEN_HEX_CONSTANT:
            result += "0x" + t.text.substr(1);
            break;
        case TOKEN_PLUS:
            result += " + ";
            break;
        case TOKEN_MINUS:
            result += " - ";
            break;
        case TOKEN_NAME:
            result += t.text;
            break;
        case TOKEN_COMMA:
            result += ", ";
            break;
        case TOKEN_LESS:
            {
                Token u = tokens[++index];
                result += "LOBYTE(" + u.text + ")";
            }
            break;
        case TOKEN_GREATER:
            {
                Token u = tokens[++index];
                result += "HIBYTE(" + u.text + ")";
            }
            break;
        default:
            goto break_loop;
        }

        t = tokens[++index];
    }

break_loop:
    index--;
    return result;
}

// Translate a constant/variable expression
static std::string translateExpression(std::vector<Token>& tokens, size_t& index)
{
    Token t = tokens[++index];

    std::string result;
    while(true)
    {
        switch(t.type)
        {
        case TOKEN_BIN_CONSTANT:
            result += "BOOST_BINARY(" + t.text.substr(1) + ")";
            break;
        case TOKEN_DEC_CONSTANT:
            result += t.text;
            break;
        case TOKEN_HEX_CONSTANT:
            result += "0x" + t.text.substr(1);
            break;
        case TOKEN_PLUS:
        case TOKEN_COMMA:
            result += " + ";
            break;
        case TOKEN_MINUS:
            result += " - ";
            break;
        case TOKEN_X:
            result += "x";
            break;
        case TOKEN_Y:
            result += "y";
            break;
        case TOKEN_NAME:
            result += t.text;
            break;
        case TOKEN_LEFT_PAREN:
            result += "M("; // Indirect addressing
            break;
        case TOKEN_RIGHT_PAREN:
            result += ")";
            break;
        case TOKEN_LESS:
            {
                Token u = tokens[++index];
                result += "LOBYTE(" + u.text + ")";
            }
            break;
        case TOKEN_GREATER:
            {
                Token u = tokens[++index];
                result += "HIBYTE(" + u.text + ")";
            }
            break;
        default:
            goto break_loop;
        }

        t = tokens[++index];
    }

break_loop:
    index--;
    return result;
}

// Translate the operand of an instruction
static std::string translateOperand(std::vector<Token>& tokens, size_t& index)
{
    Token& t = tokens[++index];

    switch(t.type)
    {
    case TOKEN_POUND:
        // Immediate value, translate expression following
        return translateExpression(tokens, index);
    default:
        // Expression, translate as memory address
        return "M(" + translateExpression(tokens, --index) + ")";
    }
}

/**
 * Program for aiding decompilation from the 6502 disassembly to C/C++.
 */
int main()
{
    std::vector<Token> tokens;

#if 0
    std::ifstream inputFile("../docs/smbdis.asm");

    // Read in the disassembly
    inputFile.seekg(0, std::ios::end);
    std::streamsize size = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    inputFile.read(buffer.data(), size);
    const char* text = &buffer[0];
    std::cout << size << std::endl;

    // Create regex expressions for token matching
    std::regex* regularExpressions[NUM_TOKEN_TYPES];
    try
    {
        regularExpressions[TOKEN_ERROR] = nullptr;
        regularExpressions[TOKEN_WHITESPACE] = new std::regex("^[\t\r ]+");
        regularExpressions[TOKEN_NEWLINE] = new std::regex("^\n");
        regularExpressions[TOKEN_COMMENT] = new std::regex("^;[^\n]*($|\n)");
        regularExpressions[TOKEN_DIRECTIVE] = new std::regex("^\\.[a-z]+");
        regularExpressions[TOKEN_LABEL] = new std::regex("^[a-zA-Z]+[a-zA-Z0-9_]*:");

        regularExpressions[TOKEN_X] = new std::regex("^x");
        regularExpressions[TOKEN_Y] = new std::regex("^y");

        regularExpressions[TOKEN_LDA] = new std::regex("^lda");
        regularExpressions[TOKEN_LDX] = new std::regex("^ldx");
        regularExpressions[TOKEN_LDY] = new std::regex("^ldy");
        regularExpressions[TOKEN_STA] = new std::regex("^sta");
        regularExpressions[TOKEN_STX] = new std::regex("^stx");
        regularExpressions[TOKEN_STY] = new std::regex("^sty");

        regularExpressions[TOKEN_TAX] = new std::regex("^tax");
        regularExpressions[TOKEN_TAY] = new std::regex("^tay");
        regularExpressions[TOKEN_TXA] = new std::regex("^txa");
        regularExpressions[TOKEN_TYA] = new std::regex("^tya");

        regularExpressions[TOKEN_TSX] = new std::regex("^tsx");
        regularExpressions[TOKEN_TXS] = new std::regex("^txs");
        regularExpressions[TOKEN_PHA] = new std::regex("^pha");
        regularExpressions[TOKEN_PHP] = new std::regex("^php");
        regularExpressions[TOKEN_PLA] = new std::regex("^pla");
        regularExpressions[TOKEN_PLP] = new std::regex("^plp");

        regularExpressions[TOKEN_AND] = new std::regex("^and");
        regularExpressions[TOKEN_EOR] = new std::regex("^eor");
        regularExpressions[TOKEN_ORA] = new std::regex("^ora");
        regularExpressions[TOKEN_BIT] = new std::regex("^bit");

        regularExpressions[TOKEN_ADC] = new std::regex("^adc");
        regularExpressions[TOKEN_SBC] = new std::regex("^sbc");
        regularExpressions[TOKEN_CMP] = new std::regex("^cmp");
        regularExpressions[TOKEN_CPX] = new std::regex("^cpx");
        regularExpressions[TOKEN_CPY] = new std::regex("^cpy");

        regularExpressions[TOKEN_INC] = new std::regex("^inc");
        regularExpressions[TOKEN_INX] = new std::regex("^inx");
        regularExpressions[TOKEN_INY] = new std::regex("^iny");
        regularExpressions[TOKEN_DEC] = new std::regex("^dec");
        regularExpressions[TOKEN_DEX] = new std::regex("^dex");
        regularExpressions[TOKEN_DEY] = new std::regex("^dey");

        regularExpressions[TOKEN_ASL] = new std::regex("^asl");
        regularExpressions[TOKEN_LSR] = new std::regex("^lsr");
        regularExpressions[TOKEN_ROL] = new std::regex("^rol");
        regularExpressions[TOKEN_ROR] = new std::regex("^ror");

        regularExpressions[TOKEN_JMP] = new std::regex("^jmp");
        regularExpressions[TOKEN_JSR] = new std::regex("^jsr");
        regularExpressions[TOKEN_RTS] = new std::regex("^rts");

        regularExpressions[TOKEN_BCC] = new std::regex("^bcc");
        regularExpressions[TOKEN_BCS] = new std::regex("^bcs");
        regularExpressions[TOKEN_BEQ] = new std::regex("^beq");
        regularExpressions[TOKEN_BMI] = new std::regex("^bmi");
        regularExpressions[TOKEN_BNE] = new std::regex("^bne");
        regularExpressions[TOKEN_BPL] = new std::regex("^bpl");
        regularExpressions[TOKEN_BVC] = new std::regex("^bvc");
        regularExpressions[TOKEN_BVS] = new std::regex("^bvs");

        regularExpressions[TOKEN_CLC] = new std::regex("^clc");
        regularExpressions[TOKEN_CLD] = new std::regex("^cld");
        regularExpressions[TOKEN_CLI] = new std::regex("^cli");
        regularExpressions[TOKEN_CLV] = new std::regex("^clv");
        regularExpressions[TOKEN_SEC] = new std::regex("^sec");
        regularExpressions[TOKEN_SED] = new std::regex("^sed");
        regularExpressions[TOKEN_SEI] = new std::regex("^sei");

        regularExpressions[TOKEN_BRK] = new std::regex("^brk");
        regularExpressions[TOKEN_NOP] = new std::regex("^nop");
        regularExpressions[TOKEN_RTI] = new std::regex("^rti");

        regularExpressions[TOKEN_NAME] = new std::regex("^[a-zA-Z]+[a-zA-Z0-9_]*");
        regularExpressions[TOKEN_HEX_CONSTANT] = new std::regex("^\\$[0-9A-Fa-f]+");
        regularExpressions[TOKEN_BIN_CONSTANT] = new std::regex("^%[0|1]+");
        regularExpressions[TOKEN_DEC_CONSTANT] = new std::regex("^[0-9]+");
        regularExpressions[TOKEN_EQUALS] = new std::regex("^=");
        regularExpressions[TOKEN_PLUS] = new std::regex("^\\+");
        regularExpressions[TOKEN_MINUS] = new std::regex("^\\-");
        regularExpressions[TOKEN_LESS] = new std::regex("^<");
        regularExpressions[TOKEN_GREATER] = new std::regex("^>");
        regularExpressions[TOKEN_POUND] = new std::regex("^#");
        regularExpressions[TOKEN_COMMA] = new std::regex("^,");
        regularExpressions[TOKEN_LEFT_PAREN] = new std::regex("^\\(");
        regularExpressions[TOKEN_RIGHT_PAREN] = new std::regex("^\\)");
    }
    catch( std::exception& e )
    {
        const char* what = e.what();
        std::cout << what << std::endl;
        return 0;
    }

    // Tokenize the input assembly text
    while( *text != '\0' )
    {
        size_t searchLength = 128;
        if( text + 128 >= &(buffer[0]) + size )
        {
            searchLength = &(buffer[0]) + size - text;
        }
        if( searchLength == 0 )
        {
            break;
        }

        std::string textString(text, searchLength);
        TokenType matchType = TOKEN_ERROR;
        int maximumMatchedChars = 0;

        for( int i = 1; i < NUM_TOKEN_TYPES; i++ )
        {
            std::smatch result;
            bool success = std::regex_search( textString, result, *regularExpressions[i] );
            if( success && result.size() > 0 )
            {
                const std::string& match = result[0];
                if( match.length() > (size_t)maximumMatchedChars )
                {
                    maximumMatchedChars = match.length();
                    matchType = (TokenType)i;
                }
            }
        }

        if( matchType == TOKEN_ERROR )
        {
            maximumMatchedChars = 1;
            std::cout << "Error: unrecognized:\n" << textString;
            return 0;
        }

        if( matchType == TOKEN_COMMENT )
        {
            // Ignore end of line
            maximumMatchedChars--;
        }

        // Consume matched characters
        std::string str(text, maximumMatchedChars);
        text = text + maximumMatchedChars;

        if( matchType != TOKEN_WHITESPACE )
        {
            Token t;
            t.text = str;
            t.type = matchType;
            tokens.push_back(t);
        }
    }
    std::cout << "Tokenization complete.\n";

    // Dump the tokens to a file
    std::ofstream tokenFile("tokens.bin", std::ios::binary);
    for( size_t i = 0; i < tokens.size(); i++ )
    {
        auto& t = tokens[i];
        int type = (int)t.type;
        tokenFile.write((char*)(&type), sizeof(int));
        size_t textLength = t.text.length();
        tokenFile.write((char*)(&textLength), sizeof(size_t));
        tokenFile.write((char*)t.text.c_str(), textLength * sizeof(char));
    }
    return 0;
#else
    // Read tokens from the file
    std::ifstream tokenInputFile("tokens.bin", std::ios::binary);
    while( tokenInputFile.good() )
    {
        Token t;
        int type;
        tokenInputFile.read((char*)&type, sizeof(int));
        t.type = (TokenType)type;
        size_t textLength;
        tokenInputFile.read((char*)&textLength, sizeof(size_t));
        char tokenText[128];
        tokenInputFile.read((char*)tokenText, textLength);
        tokenText[textLength] = '\0';
        t.text = tokenText;
        if( t.text.compare("$fff0") == 0 ) // Last token!
        {
            tokens.push_back(t);
            break;
        }
        if( t.type == TOKEN_COMMENT )
            continue;
        tokens.push_back(t);
    }
#endif

    // Print tokens
#if 0
    std::ofstream tokenOutputFile("tokenization.txt");
    for( size_t i = 0; i < tokens.size(); i++ )
    {
        auto& t = tokens[i];
        tokenOutputFile << (int)t.type << "\t" << t.text << std::endl;
    }
#endif

    // Parse tokens into an AST
    AstRootNode* root = generateAst(tokens);
    //root->print(0);
    translateAst(root, "../Decompiled.cpp");

    // Analyze AST structure and create optimized output tree
    return 0;

    // Convert tokens to C/C++ code
    std::ofstream outputFile("decomp.cpp");
    for( size_t i = 0; i < tokens.size(); i++ )
    {
        auto& t = tokens[i];
        switch(t.type)
        {
        case TOKEN_NEWLINE:
            outputFile << std::endl;
            break;
        case TOKEN_COMMENT:
            outputFile << "//" << t.text.substr(1);
            break;

        case TOKEN_DIRECTIVE:
            if(t.text.compare(".db") == 0)
            {
                outputFile << "const uint8_t data" << getNameCounter() << " = [" << translateData(tokens, i) << "];";
            }
            else if(t.text.compare(".dw") == 0)
            {
                outputFile << "const uint16_t data" << getNameCounter() << " = [" << translateData(tokens, i) << "];";
            }
            break;

        case TOKEN_LABEL:
            // Check if there is data after the label. If so, convert the label into a constant.
            {
                // Get the next token that is not a newline
                size_t j = i + 1;
                bool isConstantData = false;
                bool doneSearching = false;
                while(!doneSearching)
                {
                    Token u = tokens[j++];
                    switch(u.type)
                    {
                    case TOKEN_NEWLINE:
                        break;
                    case TOKEN_DIRECTIVE:
                        // We're good, consume the directive and convert the label to a constant
                        isConstantData = true;
                    default:
                        // This is a regular label
                        doneSearching = true;
                        break;
                    }
                }
                if(isConstantData)
                {
                    // Continue reading until we hit something that isn't a valid data item
                    outputFile << "const uint8_t " << t.text.substr(0, t.text.length() - 1) << " = [";
                    doneSearching = false;
                    bool firstDirective = true;
                    while(!doneSearching)
                    {
                        Token u = tokens[++i];
                        switch(u.type)
                        {
                        case TOKEN_NEWLINE:
                            outputFile << std::endl;
                            break;
                        case TOKEN_COMMENT:
                            outputFile << "//" << u.text.substr(1);
                            break;
                        case TOKEN_DIRECTIVE:
                            outputFile << "\t";
                            if(!firstDirective)
                            {
                                outputFile << ",";
                            }
                            outputFile << translateData(tokens, i);
                            firstDirective = false;
                            break;
                        default:
                            doneSearching = true;
                            outputFile << "];\n";
                            i--;
                            break;
                        }
                    }
                }
                else
                {
                    outputFile << t.text;
                }
            }
            break;

        case TOKEN_LDA:
            outputFile << "\ta = " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_LDX:
            outputFile << "\tx = " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_LDY:
            outputFile << "\ty = " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_STA:
            outputFile << "\t" << translateOperand(tokens, i) << " = a;";
            break;
        case TOKEN_STX:
            outputFile << "\t" << translateOperand(tokens, i) << " = x;";
            break;
        case TOKEN_STY:
            outputFile << "\t" << translateOperand(tokens, i) << " = y;";
            break;

        case TOKEN_TAX:
            outputFile << "\tx = a;";
            break;
        case TOKEN_TAY:
            outputFile << "\ty = a;";
            break;
        case TOKEN_TSX:
            outputFile << "\tx = s;";
            break;
        case TOKEN_TXA:
            outputFile << "\ta = x;";
            break;
        case TOKEN_TXS:
            outputFile << "\ts = x;";
            break;
        case TOKEN_TYA:
            outputFile << "\ta = y;";
            break;


        case TOKEN_PHA:
            outputFile << "\tpha();";
            break;
        case TOKEN_PHP:
            outputFile << "\tphp();";
            break;
        case TOKEN_PLA:
            outputFile << "\tpla();";
            break;
        case TOKEN_PLP:
            outputFile << "\tplp();";
            break;

        case TOKEN_AND:
            outputFile << "\ta &= " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_EOR:
            outputFile << "\ta ^= " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_ORA:
            outputFile << "\ta |= " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_BIT:
            outputFile << "\tbit(" << translateOperand(tokens, i) << ");";
            break;

        case TOKEN_ADC:
            outputFile << "\ta += " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_SBC:
            outputFile << "\ta -= " << translateOperand(tokens, i) << ";";
            break;
        case TOKEN_CMP:
            outputFile << "\tcmp(" << translateOperand(tokens, i) << ");";
            break;
        case TOKEN_CPX:
            outputFile << "\tcpx(" << translateOperand(tokens, i) << ");";
            break;
        case TOKEN_CPY:
            outputFile << "\tcpy(" << translateOperand(tokens, i) << ");";
            break;

        case TOKEN_INC:
            outputFile << "\t" << translateOperand(tokens, i) << "++;";
            break;
        case TOKEN_INX:
            outputFile << "\tx++;";
            break;
        case TOKEN_INY:
            outputFile << "\ty++;";
            break;
        case TOKEN_DEC:
            outputFile << "\t" << translateOperand(tokens, i) << "--;";
            break;
        case TOKEN_DEX:
            outputFile << "\tx--;";
            break;
        case TOKEN_DEY:
            outputFile << "\ty--;";
            break;

        case TOKEN_ASL:
            {
                std::string operand = translateExpression(tokens, i);
                if( operand.empty() )
                {
                    outputFile << "\ta <<= 1;";
                }
                else
                {
                    outputFile << "\tM(" << operand << ") <<= 1;";
                }
            }
            break;
        case TOKEN_LSR:
            {
                std::string operand = translateExpression(tokens, i);
                if( operand.empty() )
                {
                    outputFile << "\ta >>= 1;";
                }
                else
                {
                    outputFile << "\tM(" << operand << ") >>= 1;";
                }
            }
            break;
        case TOKEN_ROL:
            outputFile << "\trol(" << translateExpression(tokens, i) << ");";
            break;
        case TOKEN_ROR:
            outputFile << "\tror(" << translateExpression(tokens, i) << ");";
            break;

        case TOKEN_JMP:
            {
                Token v = tokens[++i];
                if( v.type == TOKEN_NAME )
                {
                    outputFile << "\tgoto " + v.text + ";";
                }
                else
                {
                    outputFile << "\t/*INDIRECT JUMP*/";
                }
            }
            break;
        case TOKEN_JSR:
            {
                Token u = tokens[i + 1];
                if( u.text.compare("JumpEngine") == 0 )
                {
                    // Special case for "jsr JumpEngine" -> convert into a switch statement
                    i++;

                    // Continue reading until we hit something that isn't a valid data item
                    outputFile << "\tswitch(a) /*JSR JumpEngine*/\n\t{\n";
                    bool doneSearching = false;
                    int jumpIndex = 0;
                    while(!doneSearching)
                    {
                        Token u = tokens[++i];
                        switch(u.type)
                        {
                        case TOKEN_NEWLINE:
                            outputFile << std::endl;
                            break;
                        case TOKEN_COMMENT:
                            outputFile << "//" << u.text.substr(1);
                            break;
                        case TOKEN_DIRECTIVE:
                            outputFile << "\tcase " << std::to_string(jumpIndex++) << ":\n\t\t" << translateData(tokens, i) << "();\n\t\treturn;";
                            break;
                        default:
                            doneSearching = true;
                            outputFile << "\n\t}\n";
                            i--;
                            break;
                        }
                    }
                }
                else
                {
                    outputFile << "\t" << tokens[++i].text << "();";
                }
            }
            break;
        case TOKEN_RTS:
            outputFile << "\treturn;";
            break;

        case TOKEN_BCC:
            outputFile << translateBranch(tokens, i, "bcc");
            break;
        case TOKEN_BCS:
            outputFile << translateBranch(tokens, i, "bcs");
            break;
        case TOKEN_BEQ:
            outputFile << translateBranch(tokens, i, "beq");
            break;
        case TOKEN_BMI:
            outputFile << translateBranch(tokens, i, "bmi");
            break;
        case TOKEN_BNE:
            outputFile << translateBranch(tokens, i, "bne");
            break;
        case TOKEN_BPL:
            outputFile << translateBranch(tokens, i, "bpl");
            break;
        case TOKEN_BVC:
            outputFile << translateBranch(tokens, i, "bvc");
            break;
        case TOKEN_BVS:
            outputFile << translateBranch(tokens, i, "bvs");
            break;

        case TOKEN_CLC:
            outputFile << "\tclc();";
            break;
        case TOKEN_CLD:
            outputFile << "\tcld();";
            break;
        case TOKEN_CLI:
            outputFile << "\tcli();";
            break;
        case TOKEN_CLV:
            outputFile << "\tclv();";
            break;
        case TOKEN_SEC:
            outputFile << "\tsec();";
            break;
        case TOKEN_SED:
            outputFile << "\tsed();";
            break;
        case TOKEN_SEI:
            outputFile << "\tsei();";
            break;

        case TOKEN_RTI:
            outputFile << "\t/*RTI*/";
            break;

        case TOKEN_NAME:
            {
                auto& u = tokens[++i];
                switch(u.type)
                {
                case TOKEN_EQUALS:
                    // Constant/macro definition
                    outputFile << "#define " << t.text << " " << translateExpression(tokens, i);
                    break;
                default:
                    break;
                }
            }
            break;


        default:
            break;
        }
    }

#if 0
    // Cleanup
    for( int i = 0; i < NUM_TOKEN_TYPES; i++ )
    {
        delete regularExpressions[i];
    }
#endif

    return 0;
}
