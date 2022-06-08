#ifndef ASTIFSTMT_H
#define ASTIFSTMT_H

#include "ASTNode.h"
#include "ASTBlock.h"
#include "ASTExpression.h"
#include "../Visitors/visitor.h"

class ASTIfStmt : public ASTNode
{
private:
    /* data */
public:
    ASTExpression* condition;
    ASTBlock* trueBlock;
    ASTBlock* falseBlock;

    ASTIfStmt(ASTExpression* cond, ASTBlock* t, ASTBlock* f){
        condition = cond;
    trueBlock = t;
    falseBlock = f;
    }
    ~ASTIfStmt(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTIfStmt::ASTIfStmt(ASTExpression* cond, ASTBlock* t, ASTBlock* f)
// {
//     condition = cond;
//     trueBlock = t;
//     falseBlock = f;
// }

// ASTIfStmt::~ASTIfStmt()
// {
// }

#endif