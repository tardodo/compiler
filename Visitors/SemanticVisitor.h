#ifndef SEMANTICVISITOR_H
#define SEMANTICVISITOR_H

#include "visitor.h"
#include "../SymbolTable.h"

class SemanticVisitor : public visitor
{
public:
    SymbolTable st;
    std::string lastType;
    std::vector<std::string> paramTypes;
    std::string lastFuncName;
    bool genNewScope = true;
    bool ifFlag = false;
    std::string funcDeclName;
    bool hasReturn = false;

    SemanticVisitor(){};
    ~SemanticVisitor(){};
    bool isRelOp(std::string relOp);
    virtual void visit(ASTActualParams* node) override;
    virtual void visit(ASTAssign* node) override;
    virtual void visit(ASTBinOp* node) override;
    virtual void visit(ASTBlock* node) override;
    // virtual void visit(ASTExpression* node) override;
    virtual void visit(ASTFormalParam* node) override;
    virtual void visit(ASTFormalParams* node) override;
    virtual void visit(ASTForStmt* node) override;
    virtual void visit(ASTFuncCall* node) override;
    virtual void visit(ASTFuncDecl* node) override;
    virtual void visit(ASTIdentifier* node) override;
    virtual void visit(ASTIfStmt* node) override;
    virtual void visit(ASTLiteral* node) override;
    virtual void visit(ASTPrint* node) override;
    virtual void visit(ASTProgram* node) override;
    virtual void visit(ASTReturn* node) override;
    virtual void visit(ASTUnary* node) override;
    virtual void visit(ASTVarDecl* node) override;
    virtual void visit(ASTWhile* node) override;
};

// SemanticVisitor::SemanticVisitor(/* args */)
// {
// }

// SemanticVisitor::~SemanticVisitor()
// {
// }

#endif