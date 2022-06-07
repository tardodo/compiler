
#include "ASTNode.h"
#include "ASTVarDecl.h"
#include "ASTAssign.h"
#include "ASTBlock.h"

class ASTForStmt : public ASTNode
{
private:
    /* data */
public:
    ASTVarDecl* varDecl;
    ASTExpression* expression;
    ASTAssign* assignment;
    ASTBlock* block;

    ASTForStmt(ASTVarDecl* decl, ASTExpression* expr, ASTAssign* assign, ASTBlock* bl);
    ~ASTForStmt();
};

ASTForStmt::ASTForStmt(ASTVarDecl* decl, ASTExpression* expr, ASTAssign* assign, ASTBlock* bl)
{
    varDecl = decl;
    expression = expr;
    assignment = assign;
    block = bl;
}

ASTForStmt::~ASTForStmt()
{
}
