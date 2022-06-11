#include "SymbolTable.h"
#include <vector>

using namespace std;


void SymbolTable::newScope(){
    map<string, Details> newLevel;

    sTable.push(newLevel);
}

void SymbolTable::deleteScope(){
    sTable.pop();
}

void SymbolTable::insert(string name, string details){
    map<string, Details> currentLevel = sTable.top();

    Details dets = {details, {}};

    currentLevel.insert(pair<string, Details>(name, dets));
    sTable.pop();
    sTable.push(currentLevel);
}

Details SymbolTable::lookup(string name){

    map<string, Details> currentLevel = sTable.top();
    map<string, Details>::iterator it;
    vector<map<string, Details>> levelList;

    while(currentLevel.count(name) == 0){
        if(sTable.size() == 1){
            while(!levelList.empty()){
                sTable.push(levelList.back());
                levelList.pop_back();
            }
            return {"0", {}};
        } 

        levelList.push_back(currentLevel);
        sTable.pop();
        currentLevel = sTable.top(); 
    }

    it = currentLevel.find(name);

    while(!levelList.empty()){
        sTable.push(levelList.back());
        levelList.pop_back();
    }

    return it->second;

}

void insert(std::string name, std::string type, std::vector<std::string> params){

}

void SymbolTable::modify(string name, Details details){
    map<string, Details> currentLevel = sTable.top();
    map<string, Details>::iterator it;
    vector<map<string, Details>> levelList;

    while(currentLevel.count(name) == 0){
        if(sTable.size() == 1){
            while(!levelList.empty()){
                sTable.push(levelList.back());
                levelList.pop_back();
            }
            break;
        } 

        levelList.push_back(currentLevel);
        sTable.pop();
        currentLevel = sTable.top(); 
    }

    it = currentLevel.find(name);
    currentLevel.erase(it);

    currentLevel.insert(pair<string, Details>(name, details));
    sTable.pop();
    sTable.push(currentLevel);

    // it->second = details;

    while(!levelList.empty()){
        sTable.push(levelList.back());
        levelList.pop_back();
    }


}

bool SymbolTable::existsCurrScope(string name){
    map<string, Details> currentLevel = sTable.top();

    if(currentLevel.count(name) > 0)
        return true;
    else return false;
}