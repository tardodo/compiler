#include <fstream>
#include <string>

typedef struct tokenData{
    int tok;
    std::string data;
} Token;

// classifiers
enum{letter, digit, newLine, endFile};

// states
enum states{S0, S4, S18, S19, Se};

// tokens
enum tokens{identifier, intLit, floatLit, charLit, endOfFile, invalid};

int catTable(char c);
int openFile();
Token nextWord();
void closeFile();