
#ifndef ASTUNARY_H
#define ASTUNARY_H

#include "ASTExpression.h"
#include <string>
#include "../Visitors/visitor.h"

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

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTUnary::ASTUnary(/* args */)
// {
// }

// ASTUnary::~ASTUnary()
// {
// }

#endif
