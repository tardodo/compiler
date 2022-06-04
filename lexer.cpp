#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "lexer.h"
using namespace std;

// classifiers
// enum{letter, digit, newLine, endFile};

// // states
// enum states{S0, S4, S18, S19, Se};

// // tokens
// enum tokens{identifier, intLit, floatLit, charLit, endOfFile, invalid};


                    //    underSc   let  dig   nline    eof
// int transTable[6][6] = 
//                         {{  S4, Se,     S18 ,   S19},     // S0 
//                         {   S4,  S4,    Se,   Se  },    // S4
//                         {Se,  Se,      S18,   Se},     //S18
//                         {Se,  Se,      Se,    Se},      //S19
//                         {Se, Se,       Se,    Se}};     //Se



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
                        


int state = 0;
// bool finalStates[7] = {false, true, true, true, false };
int finalStateList[28] = {S1, S3, S4, S7, S8, S9, S10, S11, S12, S13, S14, S15, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, S27, S28, S29, S30, S33, S35};
                //    S0,              S1,       S2,        S3,             S4,          S5,        S6,           S7,       S8,          S9,     S10,         S11,        S12,     S13,        S14,       S15,    S16,         S17,        S18,     S19,           S20,         S21,           S22,             S23,        S24,           S25,         S26,        S27,     S28,     S29,      S30,       S31,        S32,         S33,        S34,     S35,        Se
int tokenTable[37] = {tokInvalid, tokIntLit, tokInvalid,  tokFloatLit, tokIdentifier, tokInvalid, tokInvalid, tokCharLit, tokMultOp, tokAddOp, tokRelOp,    tokRelOp,  tokRelOp, tokRelOp,  tokEquals, tokRelOp, tokInvalid, tokRelOp,  tokOther, tokEndOfFile, tokOther, tokBracketOpen, tokBracketClose, tokCurlyOpen, tokCurlyClose, tokSemicolon, tokComma, tokColon, tokAddOp, tokArrow, tokMultOp, tokInvalid, tokInvalid, tokOther,  tokInvalid, tokOther, tokInvalid };
string lexeme = "";
FILE* input_file;

string keywords[17] = {"char", "int", "float", "bool", "fn", "true", "false", "if", "else", "while", "for", "return", "print", "let", "and", "or", "not"};
int keywordTokens[17] = {tokCharReserve, tokIntReserve, tokFloatReserve, tokBoolReserve, tokFnReserve, tokTrueReserve, tokFalseReserve, tokIfReserve, tokElseReserve, tokWhileReserve, tokForReserve, tokReturnReserve, tokPrintReserve, tokLetReserve, tokAndReserve, tokOrReserve, tokNotReserve};
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

//    printable,

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

    return -1;
}


void emptyStack(){
    while(!stateStack.empty()){
        stateStack.pop();
    }

}

bool isKeyword(string lex){
    for(string _keyword: keywords){
        if(lex== _keyword)
            return true;
    }
    return false;
}

int matchKeyword(string lex){
    int pos = distance(keywords, find(keywords, keywords+16, lex));
    return keywordTokens[pos];
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
        if(lexeme != ""){
            temp = lexeme.back();
            lexeme.pop_back();
            ungetc(temp, input_file);
        }
        
        //fseek(input_file, 0, SEEK_CUR-1);
        
    }

    Token result;
    result.data = lexeme;

    if(state == -1){
        result.tok = -1;
    }else if(tokenTable[state] == tokIdentifier && isKeyword(lexeme)){
        result.tok = matchKeyword(lexeme);
    }else
        result.tok = tokenTable[state];

    return result;

}