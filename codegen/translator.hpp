#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <list>
#include <sstream>
#include <string>

#include "ast.hpp"

class Translator
{
public:
    Translator(const std::string& inputFilename, RootNode* astRootNode);

    std::string getConstantHeaderOutput() const;
    std::string getDataOutput() const;
    std::string getDataHeaderOutput() const;
    std::string getSourceOutput() const;

private:
    std::string inputFilename;
    std::stringstream constantHeaderOutput;
    std::stringstream dataOutput;
    std::stringstream dataHeaderOutput;
    std::stringstream sourceOutput;
    RootNode* root;
    int returnLabelIndex;

    void classifyLabels();
    void generateCode();
    void generateConstantDeclarations();
    void generateDataDeclarations();
    void indexEmptyLines();
    void translate();
    std::string translateBranch(const std::string& condition, const std::string& destination);
    std::string translateExpression(AstNode* expr);
    std::string translateInstruction(InstructionNode* inst);
    std::string translateOperand(AstNode* operand);
};

#endif // TRANSLATOR_HPP
