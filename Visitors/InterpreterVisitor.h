#ifndef INTERPRETERVISITOR_H
#define INTERPRETERVISITOR_H

#include "visitor.h"
#include "../SymbolTable.h"

class InterpreterVisitor : public visitor
{
public:
    SymbolTable st;
    std::string lastType;
    std::string lastValue;
    std::vector<std::string> paramNames;
    std::string lastFuncName;
    bool genNewScope = true;
    bool hasReturned = false;
    std::string returnValue;


    InterpreterVisitor(){};
    ~InterpreterVisitor(){};
    bool isRelOp(std::string relOp);
    std::string computeBinOp(int lVal, int rVal, std::string operand);
    std::string computeBinOp(float lVal, float rVal, std::string operand);
    std::string computeBinOp(char lVal, char rVal, std::string operand);
    virtual void visit(ASTActualParams* node) override;
    virtual void visit(ASTAssign* node) override;
    virtual void visit(ASTBinOp* node) override;
    virtual void visit(ASTBlock* node) override;
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

#endif  