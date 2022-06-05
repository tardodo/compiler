#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

class Parser
{
private:
    bool usedNextNext;
    Token nextToken;
    Token nextNextToken;
    bool reportedFail;
    bool checkedOptional;
public:
    Parser(/* args */);
    ~Parser();

    Token getNextToken();

    bool Fail();

    bool program();

    bool statement();

    bool variableDecl();
    // bool assignment();
    // bool printStatement();
    // bool ifStatement();
    // bool forStatement();
    // bool whileStatement();
    // bool returnStatement();
    // bool functionDecl();
    // bool block();

    // // bool identifier();
    // bool formalParams();
    // bool type();
    
    // bool formalParam();

    bool expression();

    bool simpleExpr();
    // bool relationalOp();
    
    bool term();
    // bool additiveOp();

    bool factor();
    // bool multiplicativeOp();

    bool literal();
    bool functionCall();
    bool subExpression();
    bool unary();

    bool actualParams();

    // bool booleanLiteral();
    // bool integerLiteral();
    // bool floatLiteral();
    // bool charLiteral();

    

};

#endif