
#include "ASTExpression.h"
#include <vector>

class ASTActualParams: public ASTNode
{
private:
    /* data */
public:
    std::vector<ASTExpression*> params;

    ASTActualParams(std::vector<ASTExpression*> paramList);
    ~ASTActualParams();
};

ASTActualParams::ASTActualParams(std::vector<ASTExpression*> paramList)
{
    params = paramList;
}

ASTActualParams::~ASTActualParams()
{
}
