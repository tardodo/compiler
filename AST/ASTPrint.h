#ifndef ASTPRINT_H
#define ASTPRINT_H

#include "ASTNode.h"
#include "ASTExpression.h"
#include "../Visitors/visitor.h"

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

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTPrint::ASTPrint(ASTExpression* expr)
// {
//     expression = expr;
// }

// ASTPrint::~ASTPrint()
// {
// }

#endif