#ifndef ASTFUNCDECL_H
#define ASTFUNCDECL_H

#include "ASTNode.h"
#include "ASTIdentifier.h"
#include "ASTFormalParams.h"
#include "ASTBlock.h"
#include <vector>
#include "../Visitors/visitor.h"

class ASTFuncDecl : public ASTNode
{
private:
    /* data */
public:
    ASTIdentifier* identifier;
    // std::vector<ASTFormalParam*> params;
    ASTFormalParams* params;
    std::string type;
    ASTBlock* block;

    ASTFuncDecl(ASTIdentifier* id, ASTFormalParams* params, std::string type, ASTBlock* bl){
        identifier = id;
    this->params = params;
    this->type = type;
    block = bl;
    }
    ~ASTFuncDecl(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTFuncDecl::ASTFuncDecl(ASTIdentifier* id, std::vector<ASTFormalParam*> params, std::string type, ASTBlock* bl)
// {
//     identifier = id;
//     this->params = params;
//     this->type = type;
//     block = bl;
// }

// ASTFuncDecl::~ASTFuncDecl()
// {
// }

#endif
