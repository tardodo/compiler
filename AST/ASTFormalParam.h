
#include "ASTNode.h"
#include "ASTIdentifier.h"
#include <string>

class ASTFormalParam : public ASTNode
{
private:
    /* data */
public:
    ASTIdentifier* identifier;
    std::string type;

    ASTFormalParam(ASTIdentifier* id, std::string type);
    ~ASTFormalParam();
};

ASTFormalParam::ASTFormalParam(ASTIdentifier* id, std::string type)
{
    identifier = id;
    this->type = type;
}

ASTFormalParam::~ASTFormalParam()
{
}
