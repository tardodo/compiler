#ifndef ASTFUNCCALL_H
#define ASTFUNCCALL_H

#include "ASTNode.h"
#include "ASTExpression.h"
#include "ASTIdentifier.h"
#include "ASTActualParams.h"
#include "../Visitors/visitor.h"

class ASTFuncCall : public ASTExpression
{
private:
    /* data */
public:
    ASTIdentifier* identifier;
    ASTActualParams* params;
    ASTFuncCall(ASTIdentifier* id,ASTActualParams* paramList){
        identifier = id;
    params = paramList;
    }
    ~ASTFuncCall(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTFuncCall::ASTFuncCall(ASTIdentifier* id,ASTActualParams* paramList)
// {
//     identifier = id;
//     params = paramList;
// }

// ASTFuncCall::~ASTFuncCall()
// {
// }

#endif