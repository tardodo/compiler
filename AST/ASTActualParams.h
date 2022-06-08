#ifndef ASTACTUALPARAMS_H
#define ASTACTUALPARAMS_H


#include "ASTExpression.h"
#include <vector>
#include "../Visitors/visitor.h"

class ASTActualParams: public ASTNode
{
private:
    /* data */
public:
    std::vector<ASTExpression*> params;

    ASTActualParams(std::vector<ASTExpression*> paramList){
        params = paramList;
    }
    ~ASTActualParams();

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTActualParams::ASTActualParams(std::vector<ASTExpression*> paramList)
// {
//     params = paramList;
// }

// ASTActualParams::~ASTActualParams()
// {
// }

#endif