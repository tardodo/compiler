
#include "ASTNode.h"
#include "ASTIdentifier.h"
#include "ASTFormalParam.h"
#include "ASTBlock.h"
#include <vector>

class ASTFuncDecl : public ASTNode
{
private:
    /* data */
public:
    ASTIdentifier* identifier;
    std::vector<ASTFormalParam*> params;
    std::string type;
    ASTBlock* block;

    ASTFuncDecl(ASTIdentifier* id, std::vector<ASTFormalParam*> params, std::string type, ASTBlock* bl);
    ~ASTFuncDecl();
};

ASTFuncDecl::ASTFuncDecl(ASTIdentifier* id, std::vector<ASTFormalParam*> params, std::string type, ASTBlock* bl)
{
    identifier = id;
    this->params = params;
    this->type = type;
    block = bl;
}

ASTFuncDecl::~ASTFuncDecl()
{
}
