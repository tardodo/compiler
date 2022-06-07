
#include "ASTNode.h"
#include "ASTExpression.h"
#include "ASTIdentifier.h"
#include <string>

class ASTBinOp : public ASTExpression
{
private:
    /* data */
public:
    std::string op;
    ASTExpression* leftChild;
    ASTExpression* rightChild;

    ASTBinOp(ASTExpression* left, std::string oper, ASTExpression* right);
    ~ASTBinOp();
};

ASTBinOp::ASTBinOp(ASTExpression* left, std::string oper, ASTExpression* right)
{
    leftChild = left;
    op = oper;
    rightChild = right;
}

ASTBinOp::~ASTBinOp()
{
}
