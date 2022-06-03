#include "Parser.h"

Parser::Parser(/* args */)
{
    usedNextNext = false;
}

Parser::~Parser()
{
}

Token Parser::getNextToken(){
    
    Token temp = {other, "boo"};

    if(!usedNextNext){
        while(temp.tok == other){
            temp = nextWord();
        }
        return temp;
    }else{
        usedNextNext = false;
        return nextNextToken;
    }


    
}

bool Parser::program(){
    nextToken = getNextToken();
    if(statement()){
        
    }

}

// bool statement();

// bool variableDecl();
// bool assignment();
// bool printStatement();
// bool ifStatement();
// bool forStatement();
// bool whileStatement();
// bool returnStatement();
// bool functionDecl();
// bool block();

bool Parser::identifier(){

}
// bool formalParams();
// bool type();
    
// bool formalParam();

// bool expression();

// bool simpleExpr();
// bool relationalOp();
    
// bool term();
// bool additiveOp();

// bool factor();
// bool multiplicativeOp();

// bool literal();
// bool functionCall();
// bool subExpression();
// bool unary();

// bool actualParams();

// bool booleanLiteral();
// bool integerLiteral();
// bool floatLiteral();
// bool charLiteral();