#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>

enum TokenType
{
	TOKEN_ERROR,

	TOKEN_WHITESPACE,
	TOKEN_COMMENT,

	TOKEN_DIRECTIVE,
	TOKEN_LABEL,

	TOKEN_X,
	TOKEN_Y,

	TOKEN_LDA,
	TOKEN_LDX,
	TOKEN_LDY,
	TOKEN_STA,
	TOKEN_STX,
	TOKEN_STY,

	TOKEN_TAX,
	TOKEN_TAY,
	TOKEN_TXA,
	TOKEN_TYA,

	TOKEN_TSX,
	TOKEN_TXS,
	TOKEN_PHA,
	TOKEN_PHP,
	TOKEN_PLA,
	TOKEN_PLP,

	TOKEN_AND,
	TOKEN_EOR,
	TOKEN_ORA,
	TOKEN_BIT,

	TOKEN_ADC,
	TOKEN_SBC,
	TOKEN_CMP,
	TOKEN_CPX,
	TOKEN_CPY,

	TOKEN_INC,
	TOKEN_INX,
	TOKEN_INY,
	TOKEN_DEC,
	TOKEN_DEX,
	TOKEN_DEY,

	TOKEN_ASL,
	TOKEN_LSR,
	TOKEN_ROL,
	TOKEN_ROR,

	TOKEN_JMP,
	TOKEN_JSR,
	TOKEN_RTS,

	TOKEN_BCC,
	TOKEN_BCS,
	TOKEN_BEQ,
	TOKEN_BMI,
	TOKEN_BNE,
	TOKEN_BPL,
	TOKEN_BVC,
	TOKEN_BVS,

	TOKEN_CLC,
	TOKEN_CLD,
	TOKEN_CLI,
	TOKEN_CLV,
	TOKEN_SEC,
	TOKEN_SED,
	TOKEN_SEI,

	TOKEN_BRK,
	TOKEN_NOP,
	TOKEN_RTI,

	TOKEN_NAME,

	TOKEN_HEX_CONSTANT,
	TOKEN_BIN_CONSTANT,
	TOKEN_DEC_CONSTANT,

	TOKEN_EQUALS,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_LESS,
	TOKEN_GREATER,
	TOKEN_POUND,
	TOKEN_COMMA,
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,

	NUM_TOKEN_TYPES
};

struct Token
{
	TokenType type;
	std::string str;
};

/**
 * Program for aiding decompilation from the 6502 disassembly to C/C++.
 */
int main()
{
	std::ifstream inputFile("../docs/smbdis.asm");

	// Read in the file
	/*
	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	std::string bufferString = buffer.str();
	const char* text = bufferString.c_str();
	std::cout << bufferString.length() << std::endl;
	//std::cout << text << std::endl;
	*/
	inputFile.seekg(0, std::ios::end);
	std::streamsize size = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);
	std::vector<char> buffer(size);
	inputFile.read(buffer.data(), size);
	const char* text = &buffer[0];
	std::cout << strlen(text) << std::endl;

	// Create regex expressions for token matching
	std::regex* regularExpressions[NUM_TOKEN_TYPES];
	try
	{
		regularExpressions[TOKEN_ERROR] = nullptr;
		regularExpressions[TOKEN_WHITESPACE] = new std::regex("^[\n\t\r ]+");
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
	std::vector<Token> tokens;
	while( *text != '\0' )
	{
		std::string textString(text, 128);
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

		// Consume matched characters
		std::string str(text, maximumMatchedChars);
		text = text + maximumMatchedChars;

		if( matchType != TOKEN_WHITESPACE )
		{
			Token t;
			t.str = str;
			t.type = matchType;
			tokens.push_back(t);
		}
	}

	// Print tokens
	std::ofstream outputFile("decomp.cpp");
	for( size_t i = 0; i < tokens.size(); i++ )
	{
		auto& t = tokens[i];
		outputFile << (int)t.type << "\t" << t.str << std::endl;
	}

	// Cleanup
	for( int i = 0; i < NUM_TOKEN_TYPES; i++ )
	{
		delete regularExpressions[i];
	}

	return 0;
}
