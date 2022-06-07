
#include "ASTNode.h"
#include <vector>

class ASTBlock : public ASTNode
{
private:
    /* data */
public:
    std::vector<ASTNode*> childNodes;

    ASTBlock(std::vector<ASTNode*> statements);
    ~ASTBlock();
};

ASTBlock::ASTBlock(std::vector<ASTNode*> statements)
{
    childNodes = statements;
}

ASTBlock::~ASTBlock()
{
}
