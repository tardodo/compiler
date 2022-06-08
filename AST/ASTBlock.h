#ifndef ASTBLOCK_H
#define ASTBLOCK_H

#include "ASTNode.h"
#include <vector>
#include "../Visitors/visitor.h"

class ASTBlock : public ASTNode
{
private:
    /* data */
public:
    std::vector<ASTNode*> childNodes;

    ASTBlock(std::vector<ASTNode*> statements){
        childNodes = statements;
    }
    ~ASTBlock(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTBlock::ASTBlock(std::vector<ASTNode*> statements)
// {
//     childNodes = statements;
// }

// ASTBlock::~ASTBlock()
// {
// }

#endif