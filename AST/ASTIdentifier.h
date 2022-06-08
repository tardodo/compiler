#ifndef ASTIDENTIFIER_H
#define ASTIDENTIFIER_H

#include "ASTNode.h"
#include "ASTExpression.h"
#include <string>
#include "../Visitors/visitor.h"

class ASTIdentifier : public ASTExpression
{
private:
    /* data */
public:
    std::string name;
    ASTIdentifier(std::string name){
        this->name = name;
    }
    ~ASTIdentifier(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTIdentifier::ASTIdentifier(std::string name)
// {
//     this->name = name;
// }

// ASTIdentifier::~ASTIdentifier()
// {
// }

#endif  