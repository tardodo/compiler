#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "lexer.h"
using namespace std;

// Transition Table

                    //    letter, underscore, digit, printable, invertComma, space, period, exclamation, equals, asterisk, forwardSlash, plus, minus, greaterThan, lessThan, openBracket, closeBracket, openCurly, closeCurly, newLine, endFile, comma, colon, semicolon
int transTable[37][24] = 
                
            /* S0 */   {{  S4,      S4,         S1,     Se,        S5,        S20,   Se,      S16,        S14,      S8,       S30,          S9,   S28,     S12,        S10,        S21,       S22,          S23,        S24,       S18,     S19,      S26,  S27,    S25},
            /* S1 */    {   Se,     Se,         S1,     Se,        Se,        Se,    S2,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se},
            /* S2 */    {  Se,     Se,         S3,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S3 */    {  Se,     Se,         S3,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S4 */    {  S4,     S4,         S4,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S5 */    {  S6,     S6,         S6,     S6,        S6,        S6,    S6,      S6,        S6,        S6,     S6,           S6,    S6,     S6,          S6,        S6,         S6,           S6,        S6,        Se,       Se,     S6,    S6,     S6   },
            /* S6 */    {  Se,     Se,         Se,     Se,        S7,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S7 */    {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S8 */    {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S9 */    {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S10 */   { Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        S11,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S11 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S12 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        S13,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S13 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S14 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        S15,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S15 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S16 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        S17,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S17 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S18 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        S18,       Se,     Se,    Se,     Se   },
            /* S19 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se   },
            /* S20 */   {  Se,     Se,         Se,     Se,        Se,        S20,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S21 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S22 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S23 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S24 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S25 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S26 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S27 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S28 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     S29,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S29 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S30 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        S31,     S34,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S31 */   {  S31,    S31,        S31,    S31,       S31,       S31,   S31,     S31,       S31,       S32,    S31,          S31,    S31,   S31,         S31,       S31,        S31,          S31,       S31,       S31,      Se,     S31,    S31,    S31    },
            /* S32 */   {  S31,    S31,        S31,    S31,       S31,       S31,   S31,     S31,       S31,       S31,    S33,          S31,   S31,    S31,         S31,       S31,        S31,          S31,       S31,       S31,      Se,     S31,   S31,    S31    },
            /* S33 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* S34 */   {  S34,    S34,        S34,    S34,       S34,       S34,   S34,     S34,       S34,       S34,    S34,          S34,   S34,    S34,         S34,       S34,        S34,          S34,       S34,       S35,      Se,     S34,   S34,    S34    },
            /* S35 */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    },
            /* Se */   {  Se,     Se,         Se,     Se,        Se,        Se,    Se,      Se,        Se,        Se,     Se,           Se,    Se,     Se,          Se,        Se,         Se,           Se,        Se,        Se,       Se,     Se,    Se,     Se    }};
                        

// Keeps track of state
int state = 0;
// Keep track of lexemes
string lexeme = "";
// File stream
FILE* input_file;
// Stack for states
stack<int> stateStack;

// Array of final states
int finalStateList[28] = {S1, S3, S4, S7, S8, S9, S10, S11, S12, S13, S14, S15, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, S27, S28, S29, S30, S33, S35};

// Tokens returned for each state                
                //    S0,              S1,       S2,        S3,             S4,          S5,        S6,           S7,       S8,          S9,     S10,         S11,        S12,     S13,        S14,       S15,    S16,         S17,        S18,     S19,           S20,         S21,           S22,             S23,        S24,           S25,         S26,        S27,     S28,     S29,      S30,       S31,        S32,         S33,        S34,     S35,        Se
int tokenTable[37] = {tokInvalid, tokIntLit, tokInvalid,  tokFloatLit, tokIdentifier, tokInvalid, tokInvalid, tokCharLit, tokMultOp, tokAddOp, tokRelOp,    tokRelOp,  tokRelOp, tokRelOp,  tokEquals, tokRelOp, tokInvalid, tokRelOp,  tokOther, tokEndOfFile, tokOther, tokBracketOpen, tokBracketClose, tokCurlyOpen, tokCurlyClose, tokSemicolon, tokComma, tokColon, tokAddOp, tokArrow, tokMultOp, tokInvalid, tokInvalid, tokOther,  tokInvalid, tokOther, tokInvalid };

// Keywords/Reserved words
string keywords[17] = {"char", "int", "float", "bool", "fn", "true", "false", "if", "else", "while", "for", "return", "print", "let", "and", "or", "not"};
int keywordTokens[17] = {tokCharReserve, tokIntReserve, tokFloatReserve, tokBoolReserve, tokFnReserve, tokTrueReserve, tokFalseReserve, tokIfReserve, tokElseReserve, tokWhileReserve, tokForReserve, tokReturnReserve, tokPrintReserve, tokLetReserve, tokAndReserve, tokOrReserve, tokNotReserve};

// Opens file for reading
int openFile(string name){

    input_file = fopen(name.c_str(), "r");
    if (input_file == nullptr) {
       return EXIT_FAILURE;
    }
    return 0;
}

// Closes file
void closeFile(){
    fclose(input_file);
}

// Checks if the state is a final state
bool isFinalState(int checkState){
    for(int finalState: finalStateList){
        if(checkState == finalState)
            return true;
    }
    return false;
}

// Gets the next character in the file stream
char nextChar(){
    char c;
    c = fgetc(input_file);
    if(c != EOF)
        return c;
    return EOF;     
}

// Returns classifiers
int catTable(char c){

    if(c == -1)
        return endFile;
    else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return letter;
    else if(c >= 48 && c <= 57)
        return digit;
    else if(c == '\n')
        return newLine;
    else if(c == '_')
        return underscore;
    else if(c == '\'')
        return invertComma;
    else if(c == ' ')
        return space;
    else if(c == '.')
        return period;
    else if(c == '!')
        return exclamation;
    else if(c == '=')
        return equals;
    else if(c == '*')
        return asterisk;
    else if(c == '/')
        return forwardSlash;
    else if(c == '+')
        return plusClassifier;
    else if(c == '-')
        return minusClassifier;
    else if(c == '>')
        return greaterThan;
    else if(c == '<')
        return lessThan;
    else if(c == '(')
        return openBracket;
    else if(c == ')')
        return closeBracket;
    else if(c == '{')
        return openCurly;
    else if(c == '}')
        return closeCurly;
    else if(c == ';')
        return semicolon;
    else if(c == ':')
        return colon;
    else if(c == ',')
        return comma;    
    else if(c >= 32 && c <= 126)
        return printable;

    // If no match, return error
    return -1;
}

// Empty the state stack
void emptyStack(){
    while(!stateStack.empty()){
        stateStack.pop();
    }

}

// Check if the lexeme is a keyword
bool isKeyword(string lex){
    for(string _keyword: keywords){
        if(lex== _keyword)
            return true;
    }
    return false;
}

// Match the lexeme with a keyword
int matchKeyword(string lex){
    int pos = distance(keywords, find(keywords, keywords+16, lex));
    return keywordTokens[pos];
}

// Get the next token
Token nextWord(){
    // Variables
    state = S0;
    lexeme = "";
    emptyStack();
    stateStack.push(-1);
    char newChar;
    int cat;
    string errorLex;

    // Loop until error state is encountered
    while(state != Se){
        newChar = nextChar();
        lexeme += newChar;

        if(isFinalState(state)){
            emptyStack();
        }
        stateStack.push(state);
        cat = catTable(newChar);
        // If no classifier is returned, throw error
        if(cat == -1) throw runtime_error("Unable to process string: " + lexeme);
        state = transTable[state][cat];
    }

    // Store lexeme in case of invalid lexeme
    errorLex = lexeme;

    // Rollback until final state is found or bad state
    while(!isFinalState(state) && state != -1){
        char temp;
        state = stateStack.top();
        stateStack.pop();
        if(lexeme != ""){
            temp = lexeme.back();
            lexeme.pop_back();
            ungetc(temp, input_file);
        }
    }

    Token result;
    result.data = lexeme;

    // Invalid lexeme
    if(state == -1){
        result.tok = tokInvalid;
        result.data = errorLex;

        // Keyword
    }else if(tokenTable[state] == tokIdentifier && isKeyword(lexeme)){
        result.tok = matchKeyword(lexeme);

        // Normal token
    }else
        result.tok = tokenTable[state];

    return result;

}