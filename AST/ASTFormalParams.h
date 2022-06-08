#ifndef ASTFORMALPARAMS_H
#define ASTFORMALPARAMS_H

#include "ASTFormalParam.h"
#include <vector>
#include "../Visitors/visitor.h"

class ASTFormalParams : public ASTNode
{
private:
    /* data */
public:
    std::vector<ASTFormalParam*> params;

    ASTFormalParams(std::vector<ASTFormalParam*> paramList){
        params = paramList;
    }
    ~ASTFormalParams();

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTFormalParams::ASTFormalParams(std::vector<ASTFormalParam*> paramList)
// {
//     params = paramList;
// }

// ASTFormalParams::~ASTFormalParams()
// {
// }

#endif