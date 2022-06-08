#ifndef ASTWHILE_H
#define ASTWHILE_H

#include "ASTNode.h"
#include "ASTBlock.h"
#include "ASTExpression.h"

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