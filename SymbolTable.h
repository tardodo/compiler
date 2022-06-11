#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stack>
#include <map>
#include <vector>

typedef struct{
    std::string type;
    std::vector<std::string> parameters;
}Details;

class SymbolTable
{
private:
    /* data */
public:

    std::stack<std::map<std::string, Details>> sTable;

    SymbolTable(){};
    ~SymbolTable(){};

    void newScope();
    void deleteScope();
    void insert(std::string name, std::string type);
    void insert(std::string name, std::string type, std::vector<std::string> params);
    Details lookup(std::string name);
    bool existsCurrScope(std::string name);
    void modify(std::string name, Details details);
};

#endif