#ifndef ASTFORMALPARAM_H
#define ASTFORMALPARAM_H


#include "ASTNode.h"
#include "ASTIdentifier.h"
#include <string>
#include "../Visitors/visitor.h"

class ASTFormalParam : public ASTNode
{
private:
    /* data */
public:
    ASTIdentifier* identifier;
    std::string type;

    ASTFormalParam(ASTIdentifier* id, std::string type){
        identifier = id;
        this->type = type;
    }
    ~ASTFormalParam(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTFormalParam::ASTFormalParam(ASTIdentifier* id, std::string type)
// {
//     identifier = id;
//     this->type = type;
// }

// ASTFormalParam::~ASTFormalParam()
// {
// }

#endif