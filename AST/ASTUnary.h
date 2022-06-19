
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
    std::string unaryOp;
    ASTExpression* expr;
    ASTUnary(ASTExpression* expr, std::string op){
        this->expr = expr;
        unaryOp = op;
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
