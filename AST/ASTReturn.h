
#include "ASTNode.h"
#include "ASTExpression.h"

class ASTReturn: public ASTNode
{
private:
    /* data */
public:
    ASTExpression* expression;
    ASTReturn(ASTExpression* expr);
    ~ASTReturn();
};

ASTReturn::ASTReturn(ASTExpression* expr)
{
    expression = expr;
}

ASTReturn::~ASTReturn()
{
}
