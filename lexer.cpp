#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "lexer.h"
using namespace std;

// classifiers
// enum{letter, digit, newLine, endFile};

// // states
// enum states{S0, S4, S18, S19, Se};

// // tokens
// enum tokens{identifier, intLit, floatLit, charLit, endOfFile, invalid};


                    //   let  dig   nline    eof
int transTable[6][6] = 
                        {{S4, Se,     S18 ,   S19},     // S0 
                        {S4,  S4,       Se,   Se  },    // S4
                        {Se,  Se,      S18,   Se},     //S18
                        {Se,  Se,      Se,    Se},      //S19
                        {Se, Se,       Se,    Se}};     //Se

int state = 0;
// bool finalStates[7] = {false, true, true, true, false };
int finalStateList[3] = {S4, S18, S19};
int tokenTable[7] = {invalid, identifier, invalid, endOfFile, invalid};
string lexeme = "";
FILE* input_file;

// struct {
//     int tok;
//     string data;

// }typedef Token;

stack<int> stateStack;

int openFile(){
    string filename("test.txt");

    input_file = fopen(filename.c_str(), "r");
    if (input_file == nullptr) {
       return EXIT_FAILURE;
    }
    return 0;
}

void closeFile(){
    fclose(input_file);
}

bool isFinalState(int checkState){
    for(int finalState: finalStateList){
        if(checkState == finalState)
            return true;
    }
    return false;
}

char nextChar(){
    char c;
    c = fgetc(input_file);
    if(c != EOF)
        return c;
    return EOF;     
}

int catTable(char c){

    if(c == -1)
        return endFile;
    else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return letter;
    else if(c >= 48 && c <= 57)
        return digit;
    else if(c == '\n')
        return newLine;

    return -1;
}


void emptyStack(){
    while(!stateStack.empty()){
        stateStack.pop();
    }

}

Token nextWord(){
    state = S0;
    lexeme = "";
    emptyStack();
    stateStack.push(-1);
    char newChar;
    int cat;

    // if(openFile() != 0)
    //     return -1;

    while(state != Se){
        newChar = nextChar();
        // if(newChar == EOF)
        //     return -1;
        lexeme += newChar;

        if(isFinalState(state)){
            emptyStack();
        }
        stateStack.push(state);
        cat = catTable(newChar);
        state = transTable[state][cat];
    }

    while(!isFinalState(state) && state != -1){
        char temp;
        state = stateStack.top();
        stateStack.pop();
        temp = lexeme.back();
        lexeme.pop_back();
        ungetc(temp, input_file);
        //fseek(input_file, 0, SEEK_CUR-1);
        
    }

    Token result;
    result.data = lexeme;
    result.tok = tokenTable[state];

    return result;

}