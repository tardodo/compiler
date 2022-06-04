#include "Parser.h"
#include <iostream>
using namespace std;

Parser::Parser(/* args */)
{
    usedNextNext = false;
}

Parser::~Parser()
{
}

Token Parser::getNextToken(){
    
    Token temp = {tokOther, "boo"};

    if(!usedNextNext){
        while(temp.tok == tokOther){
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
        if(nextToken.tok == tokEndOfFile)
            return true;
        else Fail();
    }else if(nextToken.tok == tokEndOfFile)
        return true;
    else Fail();

}

bool Parser::Fail(){
    cout << "Syntax Error" << endl;
    return false;
}

bool Parser::statement(){

    if(variableDecl()){
        nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            return true;
        }else Fail();

    }else if(assignment()){
        nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            return true;
        }else Fail();
         
    }else if(printStatement()){
        nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            return true;
        }else Fail();

    }else if(ifStatement()){
        return true;

    }else if(forStatement()){
        return true;

    }else if(whileStatement()){
        return true;

    }else if(returnStatement()){
        nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            return true;
        }else Fail();

    }else if(functionDecl()){
        return true;

    }else if(block()){
        return true;
    }
}

bool Parser::variableDecl(){

    if(nextToken.tok == tokLetReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokIdentifier){
            nextToken = getNextToken();

            if(nextToken.tok == tokColon){
                nextToken = getNextToken();

                if(type()){
                    nextToken = getNextToken();

                    if(nextToken.tok == tokEquals){
                        return expression();
                    }
                }
            }
        }
    }

    return Fail();
}

// bool assignment();
// bool printStatement();
// bool ifStatement();
// bool forStatement();
// bool whileStatement();
// bool returnStatement();
// bool functionDecl();
// bool block();

// bool Parser::identifier(){

// }
// bool formalParams();
// bool type();
    
// bool formalParam();

bool Parser::expression(){
    if(simpleExpr()){
        nextToken = getNextToken();

        while(nextToken.tok == tokRelOp){
            //if(nextToken.tok == tokRelOp){
                
            nextToken = getNextToken();

            if(simpleExpr()){

                nextToken = getNextToken();
            }else return Fail();

            //}
        }

        // Zero or more repetitions
        return true;

    }else return Fail();
}

bool Parser::simpleExpr(){
    if(term()){
        nextToken = getNextToken();

        while(nextToken.tok == tokAddOp){
            //if(nextToken.tok == tokRelOp){
                
            nextToken = getNextToken();

            if(term()){

                nextToken = getNextToken();
            }else return Fail();

            //}
        }

        // Zero or more repetitions
        return true;

    }else return Fail();
}
// bool relationalOp();
    
bool Parser::term(){
    if(factor()){
        nextToken = getNextToken();

        while(nextToken.tok == tokMultOp){
            //if(nextToken.tok == tokRelOp){
                
            nextToken = getNextToken();

            if(factor()){

                nextToken = getNextToken();
            }else return Fail();

            //}
        }

        // Zero or more repetitions
        return true;

    }else return Fail();
}
// bool additiveOp();

bool Parser::factor(){

    // use LL(2) for deciding between identifier and function call as both have the same First() set
    nextNextToken = getNextToken();
    usedNextNext = true;

    if(literal()){
        return true;

    }else if(nextToken.tok == tokIdentifier && nextNextToken.tok != tokBracketOpen){
        return true;

    }else if(functionCall()){
        return true;

    }else if(subExpression()){
        return true;

    }else if(unary()){
       return true;

    }else return Fail();
}
// bool multiplicativeOp();

bool Parser::literal(){

    if(nextToken.tok == tokBoolLit || nextToken.tok == tokIntLit || nextToken.tok == tokFloatLit || nextToken.tok == tokCharLit){
        return true;
    }else return false;

}
bool Parser::functionCall(){

    if(nextToken.tok == tokIdentifier){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            if(actualParams()){
                nextToken = getNextToken();

                // if(nextToken.tok == tokBracketClose){
                //     return true;
                // }
            } 
            
            if(nextToken.tok == tokBracketClose){
                return true;
            }
        }
        return Fail();

    }else return false;
}
bool Parser::subExpression(){

    if(nextToken.tok == tokBracketOpen){
        nextToken = getNextToken();

        if(expression()){
            nextToken = getNextToken();

            if(nextToken.tok == tokBracketClose){
                return true;
            }
        }

        return Fail();
    }else return false;
}

bool Parser::unary(){

    
}

// bool actualParams();

// bool booleanLiteral();
// bool integerLiteral();
// bool floatLiteral();
// bool charLiteral();