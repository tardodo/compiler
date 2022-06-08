#ifndef ASTBLOCK_H
#define ASTBLOCK_H

#include "ASTNode.h"
#include <vector>

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
};

// ASTBlock::ASTBlock(std::vector<ASTNode*> statements)
// {
//     childNodes = statements;
// }

// ASTBlock::~ASTBlock()
// {
// }

#endif