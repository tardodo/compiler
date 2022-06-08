#ifndef ASTVARDECL_H
#define ASTVARDECL_H

#include "ASTNode.h"
#include "ASTIdentifier.h"
#include "ASTBinOp.h"
#include "ASTExpression.h"
#include <string>
#include "../Visitors/visitor.h"

class ASTVarDecl : public ASTNode
{
private:
    /* data */
public:
    std::string type;
    ASTIdentifier* identifier;
    ASTExpression* expression;
     
    ASTVarDecl(ASTIdentifier* id, std::string type, ASTExpression* expr){
        this->type = type;
    identifier = id;
    expression = expr;
    }
    ~ASTVarDecl();

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTVarDecl::ASTVarDecl(ASTIdentifier* id, std::string type, ASTExpression* expr)
// {
//     this->type = type;
//     identifier = id;
//     expression = expr;
// }

// ASTVarDecl::~ASTVarDecl()
// {
// }

#endif