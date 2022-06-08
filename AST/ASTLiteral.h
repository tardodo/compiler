#ifndef ASTLITERAL_H
#define ASTLITERAL_H

#include "ASTExpression.h"
#include <string>
#include "../Visitors/visitor.h"

class ASTLiteral : public ASTExpression
{
private:
    /* data */
public:
    std::string type;
    std::string value;

    ASTLiteral(int type, std::string val){
        this->type = toType(type);
        value = val;
    }
    
    std::string toType(int dataType){
        switch (dataType)
        {
        case 7:
            return "bool";
            break;
        
        case 8:
            return "bool";
            break;

        case 16:
            return "int";
            break;

        case 17:
            return "float";
            break;

        case 18:
            return "char";
            break;
        
        default:
            break;
        }
    }

    ~ASTLiteral(){};

    virtual void accept(visitor* v) override{
        v->visit(this);
    }
};

// ASTLiteral::ASTLiteral(std::string type, std::string val)
// {
//     this->type = type;
//     value = val;
// }

// ASTLiteral::~ASTLiteral()
// {
// }

#endif