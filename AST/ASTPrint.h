#ifndef ASTPRINT_H
#define ASTPRINT_H

#include "ASTNode.h"
#include "ASTExpression.h"

class ASTPrint: public ASTNode
{
private:
    /* data */
public:
    ASTExpression* expression;
    ASTPrint(ASTExpression* expr){
        expression = expr;
    }
    ~ASTPrint(){};
};

// ASTPrint::ASTPrint(ASTExpression* expr)
// {
//     expression = expr;
// }

// ASTPrint::~ASTPrint()
// {
// }

#endif