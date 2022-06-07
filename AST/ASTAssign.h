
#include "ASTNode.h"
#include "ASTExpression.h"
#include "ASTIdentifier.h"
#include <string>

class ASTAssign : public ASTNode
{
private:
    /* data */
public:
    ASTIdentifier* identifier;
    ASTExpression* expression;

    ASTAssign(ASTIdentifier* id, ASTExpression* expr);
    ~ASTAssign();
};

ASTAssign::ASTAssign(ASTIdentifier* id, ASTExpression* expr)
{
    identifier = id;
    expression = expr;
}

ASTAssign::~ASTAssign()
{
}
