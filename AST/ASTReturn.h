#ifndef ASTRETURN_H
#define ASTRETURN_H

#include "ASTNode.h"
#include "ASTExpression.h"
#include "../Visitors/visitor.h"

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

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTReturn::ASTReturn(ASTExpression* expr)
// {
//     expression = expr;
// }

// ASTReturn::~ASTReturn()
// {
// }

#endif