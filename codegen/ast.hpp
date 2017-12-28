#ifndef AST_HPP
#define AST_HPP

#include <cstring>
#include <list>

enum AstType
{
    AST_ROOT,
    AST_LIST,
    AST_DATA8,
    AST_DATA16,
    AST_DECL,
    AST_LABEL,
    AST_NAME,
    AST_CONST,
    AST_IMMEDIATE,
    AST_INDIRECT,
    AST_INDEXED_X,
    AST_INDEXED_Y,
    AST_LOBYTE,
    AST_HIBYTE,
    AST_ADD,
    AST_SUBTRACT,
    AST_INSTRUCTION
};

struct AstNode;

union AstValue
{
    const char* s;
    AstNode* node;
    const void* ptr;
};

struct AstNode
{
    AstType type;
    AstValue value;
    AstNode* parent;
    int lineNumber;
    
    AstNode(AstType type);
    AstNode(AstType type, const char* value);
};

struct UnaryNode : public AstNode
{
    AstNode* child;
    
    UnaryNode(AstType type, AstNode* child);
};

struct BinaryNode : public AstNode
{
    AstNode* lhs;
    AstNode* rhs;
    
    BinaryNode(AstType type, AstNode* lhs, AstNode* rhs);
};

struct RootNode : public AstNode
{
    std::list<AstNode*> children;
    
    RootNode();
};

struct ListNode : public AstNode
{
    ListNode* next;
    
    ListNode();
};

struct DeclNode : public AstNode
{
    AstNode* expression;

    DeclNode(const char* name, AstNode* expression);
};

enum LabelType
{
    LABEL_NONE, // An undefined label

    LABEL_ALIAS, // An alias for another label
    LABEL_CODE,  // A label containing strictly code
    LABEL_DATA   // A label containing strictly data
};

struct LabelNode : public AstNode
{
    // The child of a LabelNode can either be a ListNode,
    // or another LabelNode (aliasing another label)
    //
    AstNode* child;
    LabelType labelType;
    
    LabelNode(const char* name, AstNode* child);
};

struct InstructionNode : public AstNode
{
    int code;
    
    InstructionNode(int code);
    InstructionNode(int code, const void* operand);
};

// Cleanup an AST
// e.g. Lists need to be reversed due to how parsing works
//
void cleanupAst(RootNode* root);

// Print an AST node recursively
//
void printNode(AstNode* node, int indent = 0);

#endif // AST_HPP
