#ifndef ASTPROGRAM_H
#define ASTPROGRAM_H

#include "ASTNode.h"
#include <vector>
#include "../Visitors/visitor.h"

class ASTProgram : public ASTNode
{    
public:
    std::vector<ASTNode*> childNodes;
    ASTProgram(std::vector<ASTNode*> statements){
        childNodes = statements;
    }
    ~ASTProgram(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTProgram::ASTProgram(std::vector<ASTNode*> statements){
//     childNodes = statements;
// }

// ASTProgram::~ASTProgram()
// {
// }

#endif  