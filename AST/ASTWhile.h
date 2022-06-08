#ifndef ASTWHILE_H
#define ASTWHILE_H

#include "ASTNode.h"
#include "ASTBlock.h"
#include "ASTExpression.h"
#include "../Visitors/visitor.h"

class ASTWhile: public ASTNode
{
private:
    /* data */
public:
    ASTExpression* expression;
    ASTBlock* block;

    ASTWhile(ASTExpression* expr, ASTBlock* bl){
        expression = expr;
        block = bl;
    }
    ~ASTWhile(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTWhile::ASTWhile(ASTExpression* expr, ASTBlock* bl)
// {
//     expression = expr;
//     block = bl;
// }

// ASTWhile::~ASTWhile()
// {
// }

#endif