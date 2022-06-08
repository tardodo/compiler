
#ifndef ASTUNARY_H
#define ASTUNARY_H

#include "ASTExpression.h"
#include <string>

class ASTUnary: public ASTExpression
{
private:
    /* data */
public:
    ASTExpression* expr;
    ASTUnary(ASTExpression* expr){
        this->expr = expr;
    }
    ~ASTUnary(){};
};

// ASTUnary::ASTUnary(/* args */)
// {
// }

// ASTUnary::~ASTUnary()
// {
// }

#endif
