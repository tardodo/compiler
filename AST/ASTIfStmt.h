
#include "ASTNode.h"
#include "ASTBlock.h"
#include "ASTExpression.h"

class ASTIfStmt : public ASTNode
{
private:
    /* data */
public:
    ASTExpression* condition;
    ASTBlock* trueBlock;
    ASTBlock* falseBlock;

    ASTIfStmt(ASTExpression* cond, ASTBlock* t, ASTBlock* f);
    ~ASTIfStmt();
};

ASTIfStmt::ASTIfStmt(ASTExpression* cond, ASTBlock* t, ASTBlock* f)
{
    condition = cond;
    trueBlock = t;
    falseBlock = f;
}

ASTIfStmt::~ASTIfStmt()
{
}
