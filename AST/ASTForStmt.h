#ifndef ASTFORSTMT_H
#define ASTFORSTMT_H

#include "ASTNode.h"
#include "ASTVarDecl.h"
#include "ASTAssign.h"
#include "ASTBlock.h"
#include "../Visitors/visitor.h"

class ASTForStmt : public ASTNode
{
private:
    /* data */
public:
    ASTVarDecl* varDecl;
    ASTExpression* expression;
    ASTAssign* assignment;
    ASTBlock* block;

    ASTForStmt(ASTVarDecl* decl, ASTExpression* expr, ASTAssign* assign, ASTBlock* bl){
        varDecl = decl;
    expression = expr;
    assignment = assign;
    block = bl;
    }
    ~ASTForStmt(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTForStmt::ASTForStmt(ASTVarDecl* decl, ASTExpression* expr, ASTAssign* assign, ASTBlock* bl)
// {
//     varDecl = decl;
//     expression = expr;
//     assignment = assign;
//     block = bl;
// }

// ASTForStmt::~ASTForStmt()
// {
// }

#endif