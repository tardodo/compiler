#ifndef ASTPROGRAM_H
#define ASTPROGRAM_H

#include "ASTNode.h"
#include <vector>

class ASTProgram : public ASTNode
{
private:
    std::vector<ASTNode*> childNodes;
    
public:
    ASTProgram(std::vector<ASTNode*> statements){
        childNodes = statements;
    }
    ~ASTProgram(){};
};

// ASTProgram::ASTProgram(std::vector<ASTNode*> statements){
//     childNodes = statements;
// }

// ASTProgram::~ASTProgram()
// {
// }

#endif  