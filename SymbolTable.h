#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stack>
#include <map>
#include <vector>
#include "AST/ASTBlock.h"

enum{Variable, Function};

// Struct for attributes for identifier
typedef struct{
    std::string type;
    std::vector<std::string> parameters;
    int symbolType;
    std::string value;
    ASTBlock* funcBody;
}Details;

class SymbolTable
{
public:

    // Symbol table structure
    std::stack<std::map<std::string, Details>> sTable;

    SymbolTable(){};
    ~SymbolTable(){};

    void newScope();
    void deleteScope();
    void insert(std::string name, std::string type, int symbolType);
    void insert(std::string name, Details details);
    Details lookup(std::string name);
    bool existsCurrScope(std::string name);
    void modify(std::string name, Details details);
};

#endif