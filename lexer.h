#include <fstream>
#include <string>

typedef struct tokenData{
    int tok;
    std::string data;
} Token;

// classifiers
enum{letter, underscore, digit, printable, invertComma, space, period, exclamation, equals, asterisk, forwardSlash, plusClassifier, minusClassifier, greaterThan, lessThan, openBracket, closeBracket, openCurly, closeCurly, newLine, endFile, comma, colon, semicolon};
//    g,  _,              5,      x20-x75,  ' ,             ,   .       !            =      *         /               

// states
enum states{S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, S27, S28, S29, Se};

// tokens
enum tokens{identifier, intReserve, floatReserve, boolReserve, charReserve, boolLit, fnReserve, trueReserve, falseReserve, ifReserve, elseReserve, whileReserve, forReserve, returnReserve, printReserve, letReserve,  intLit, floatLit, charLit, multOp, addOp, relOp, unaryOp, tokCurlyOpen, tokCurlyClose, tokBracketOpen, tokBracketClose, tokColon, tokSemicolon, tokComma, andReserve, orReserve, tokEquals, arrow, other, endOfFile, invalid};



int catTable(char c);
int openFile();
Token nextWord();
void closeFile();