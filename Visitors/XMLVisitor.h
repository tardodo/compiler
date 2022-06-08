#ifndef XMLVISITOR_H
#define XMLVISITOR_H

#include "visitor.h"
#include <fstream>
#include <iostream>

class XMLVisitor: public visitor
{
public:
    std::ofstream xmlFile;
    int tagIndentation;

    XMLVisitor();
    ~XMLVisitor(){};
    void openFile();
    void closeFile();
    void indent();
    // virtual void visit(ASTNode* node) override;
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

#endif  