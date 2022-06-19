#include <fstream>
#include <string>

// Token data struct
typedef struct tokenData{
    int tok;
    std::string data;
} Token;

// classifiers
enum{letter, underscore, digit, printable, invertComma, space, period, exclamation, equals, asterisk, forwardSlash, plusClassifier, minusClassifier, greaterThan, lessThan, openBracket, closeBracket, openCurly, closeCurly, newLine, endFile, comma, colon, semicolon};

// states
enum states{S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, S27, S28, S29, S30, S31, S32, S33, S34, S35, Se};

// tokens
enum tokens{tokIdentifier, tokIntReserve, tokFloatReserve, tokBoolReserve, tokCharReserve, tokBoolLit, tokFnReserve, tokTrueReserve, tokFalseReserve, tokIfReserve, tokElseReserve, tokWhileReserve, tokForReserve, tokReturnReserve, tokPrintReserve, tokLetReserve,  tokIntLit, tokFloatLit, tokCharLit, tokMultOp, tokAddOp, tokRelOp, tokNotReserve, tokCurlyOpen, tokCurlyClose, tokBracketOpen, tokBracketClose, tokColon, tokSemicolon, tokComma, tokAndReserve, tokOrReserve, tokEquals, tokArrow, tokOther, tokEndOfFile, tokInvalid};

// Functions
int catTable(char c);
int openFile(std::string name = "test.txt");
Token nextWord();
void closeFile();