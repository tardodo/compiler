#include "SymbolTable.h"
#include <vector>

using namespace std;

// Make new scope
void SymbolTable::newScope(){
    map<string, Details> newLevel;

    sTable.push(newLevel);
}

// Remove scope
void SymbolTable::deleteScope(){
    sTable.pop();
}

// Insert
void SymbolTable::insert(string name, string details, int symbolType){
    map<string, Details> currentLevel = sTable.top();

    Details dets = {details, {}, symbolType, ""};

    currentLevel.insert(pair<string, Details>(name, dets));
    sTable.pop();
    sTable.push(currentLevel);
}

// Insert
void SymbolTable::insert(std::string name, Details details){
    map<string, Details> currentLevel = sTable.top();

    currentLevel.insert(pair<string, Details>(name, details));
    sTable.pop();
    sTable.push(currentLevel);
}

// Lookup across all scopes till a match is found
Details SymbolTable::lookup(string name){

    map<string, Details> currentLevel = sTable.top();
    map<string, Details>::iterator it;
    vector<map<string, Details>> levelList;

    // loop till match is found
    while(currentLevel.count(name) == 0){
        // If no match found
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

    // Get iterator of record
    it = currentLevel.find(name);

    // Repopulate stack
    while(!levelList.empty()){
        sTable.push(levelList.back());
        levelList.pop_back();
    }

    return it->second;

}

// Modify existing entry
void SymbolTable::modify(string name, Details details){
    map<string, Details> currentLevel = sTable.top();
    map<string, Details>::iterator it;
    vector<map<string, Details>> levelList;

    // Loop till match is found
    while(currentLevel.count(name) == 0){
        // If no match found
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

    // Find and remove record
    it = currentLevel.find(name);
    currentLevel.erase(it);

    // Insert modified 
    currentLevel.insert(pair<string, Details>(name, details));
    sTable.pop();
    sTable.push(currentLevel);

    // Repopulate
    while(!levelList.empty()){
        sTable.push(levelList.back());
        levelList.pop_back();
    }


}

// Check if exists in current scope
bool SymbolTable::existsCurrScope(string name){
    map<string, Details> currentLevel = sTable.top();

    if(currentLevel.count(name) > 0)
        return true;
    else return false;
}