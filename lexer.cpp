#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "lexer.h"
using namespace std;

// enum{letter, digit};

// int catTable(char c);
enum states{S0, S1, S2, S3, S4, Se};

int transTable[2][2] = {{S4, Se}, {S4, S4}};

int state = 0;

int catTable(char c){

    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return letter;
    else if(c >= 48 && c <= 57)
        return digit;

    return -1;
}

void nextWord(){


}