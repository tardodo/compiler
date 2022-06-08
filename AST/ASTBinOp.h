#ifndef ASTBINOP_H
#define ASTBINOP_H


#include "ASTNode.h"
#include "ASTExpression.h"
#include "ASTIdentifier.h"
#include <string>
#include "../Visitors/visitor.h"

class ASTBinOp : public ASTExpression
{
private:
    /* data */
public:
    std::string op;
    ASTExpression* leftChild;
    ASTExpression* rightChild;

    ASTBinOp(ASTExpression* left, std::string oper, ASTExpression* right){
        leftChild = left;
    op = oper;
    rightChild = right;
    }
    ~ASTBinOp(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTBinOp::ASTBinOp(ASTExpression* left, std::string oper, ASTExpression* right)
// {
//     leftChild = left;
//     op = oper;
//     rightChild = right;
// }

// ASTBinOp::~ASTBinOp()
// {
// }

#endif  
