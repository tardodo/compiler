#ifndef ASTFORMALPARAMS_H
#define ASTFORMALPARAMS_H

#include "ASTFormalParam.h"
#include <vector>

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
};

// ASTFormalParams::ASTFormalParams(std::vector<ASTFormalParam*> paramList)
// {
//     params = paramList;
// }

// ASTFormalParams::~ASTFormalParams()
// {
// }

#endif