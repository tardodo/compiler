#ifndef ASTASSIGN_H
#define ASTASSIGN_H

#include "ASTNode.h"
#include "ASTExpression.h"
#include "ASTIdentifier.h"
#include <string>
#include "../Visitors/visitor.h"

class ASTAssign : public ASTNode
{
private:
    /* data */
public:
    ASTIdentifier* identifier;
    ASTExpression* expression;

    ASTAssign(ASTIdentifier* id, ASTExpression* expr){
        identifier = id;
        expression = expr;  
    }
    ~ASTAssign();

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTAssign::ASTAssign(ASTIdentifier* id, ASTExpression* expr)
// {
//     identifier = id;
//     expression = expr;
// }

// ASTAssign::~ASTAssign()
// {
// }

#endif
