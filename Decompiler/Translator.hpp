#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <string>

#include "Ast.hpp"

void translateAst(AstRootNode* ast, const std::string& outputFilename);

#endif // TRANSLATOR_HPP
