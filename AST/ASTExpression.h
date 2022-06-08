#ifndef ASTEXPRESSION_H
#define ASTEXPRESSION_H


#include "ASTNode.h"
#include "../Visitors/visitor.h"

class ASTExpression : public ASTNode
{
public:
    ASTExpression(/* args */){};
    ~ASTExpression(){};
};

// ASTExpression::ASTExpression(/* args */)
// {
// }

// ASTExpression::~ASTExpression()
// {
// }

#endif