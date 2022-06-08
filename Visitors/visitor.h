#ifndef VISITOR_H
#define VISITOR_H

class ASTNode;
class ASTActualParams;
class ASTAssign;
class ASTBinOp;
class ASTBlock;
class ASTExpression;
class ASTFormalParam;
class ASTFormalParams;
class ASTForStmt;
class ASTFuncCall;
class ASTFuncDecl;
class ASTIdentifier;
class ASTIfStmt;
class ASTLiteral;
class ASTPrint;
class ASTProgram;
class ASTReturn;
class ASTUnary;
class ASTVarDecl;
class ASTWhile;

class visitor
{
  public:
    // virtual void visit(ASTNode* node) = 0;
    virtual void visit(ASTActualParams* node) = 0;
    virtual void visit(ASTAssign* node) = 0;
    virtual void visit(ASTBinOp* node) = 0;
    virtual void visit(ASTBlock* node) = 0;
    // virtual void visit(ASTExpression* node) = 0;
    virtual void visit(ASTFormalParam* node) = 0;
    virtual void visit(ASTFormalParams* node) = 0;
    virtual void visit(ASTForStmt* node) = 0;
    virtual void visit(ASTFuncCall* node) = 0;
    virtual void visit(ASTFuncDecl* node) = 0;
    virtual void visit(ASTIdentifier* node) = 0;
    virtual void visit(ASTIfStmt* node) = 0;
    virtual void visit(ASTLiteral* node) = 0;
    virtual void visit(ASTPrint* node) = 0;
    virtual void visit(ASTProgram* node) = 0;
    virtual void visit(ASTReturn* node) = 0;
    virtual void visit(ASTUnary* node) = 0;
    virtual void visit(ASTVarDecl* node) = 0;
    virtual void visit(ASTWhile* node) = 0;
};

#endif