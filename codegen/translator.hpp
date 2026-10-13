#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>

#include "ast.hpp"

// The C++ sources generated from the disassembly.
//
struct GeneratedSources
{
    std::string code;          // SMB.cpp
    std::string data;          // SMBData.cpp
    std::string dataAddresses; // SMBDataPointers.hpp
    std::string constants;     // SMBConstants.hpp
};

// Translate a parsed program into C++. Consumes the program's comments.
// Throws std::runtime_error for constructs that cannot be translated.
//
GeneratedSources translate(Program& program);

#endif // TRANSLATOR_HPP
