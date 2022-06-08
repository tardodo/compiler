#ifndef ASTRETURN_H
#define ASTRETURN_H

#include "ASTNode.h"
#include "ASTExpression.h"

class ASTReturn: public ASTNode
{
private:
    /* data */
public:
    ASTExpression* expression;
    ASTReturn(ASTExpression* expr){
        expression = expr;
    }
    ~ASTReturn(){};
};

// ASTReturn::ASTReturn(ASTExpression* expr)
// {
//     expression = expr;
// }

// ASTReturn::~ASTReturn()
// {
// }

#endif