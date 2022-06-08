#ifndef ASTNODE_H
#define ASTNODE_H

#include "../Visitors/visitor.h"

class ASTNode{

public:

    ASTNode(){};
    virtual void accept(visitor* v) = 0;
    ~ASTNode(){};
};

// ASTNode::ASTNode()
// {
// }

// ASTNode::~ASTNode()
// {
// }

#endif