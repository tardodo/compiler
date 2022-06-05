#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(/* args */)
{
    usedNextNext = false;
    reportedFail = false;
    checkedOptional = false;
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

    // if(statement()){
    //     if(nextToken.tok == tokEndOfFile)
    //         return true;
    //     else Fail();
    // }else if(nextToken.tok == tokEndOfFile)
    //     return true;
    // else Fail();


    // Zero or more statements
    while(statement()){
        // nextToken = getNextToken();

        // if(nextToken.tok == tokEndOfFile)
        //     return true;
        // cout << "outer loop" << endl;

    }

    if(nextToken.tok == tokEndOfFile && !reportedFail)
        return true;
    else return false;

}

bool Parser::Fail(string error){
    cout << "Syntax Error at " << error << endl;
    reportedFail = true;
    return false;
}

bool Parser::statement(){

    if(variableDecl()){
        // if(!checkedOptional) nextToken = getNextToken();
        // else checkedOptional = false;

        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return true;
        }else return Fail("variable declaration");
    
    }else if(assignment()){
        //nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return true;
        }else return Fail("assignment");
         
    }else if(printStatement()){
        // nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return true;
        }else return Fail("print statement");

    }else if(ifStatement()){
        return true;

    }else if(forStatement()){
        return true;

    }else if(whileStatement()){
        return true;

    }else if(returnStatement()){
        // nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return true;
        }else return Fail("return");

    }else if(functionDecl()){
        return true;

    }else if(block()){
        return true;
    }

    return false;
}

bool Parser::variableDecl(){

    if(nextToken.tok == tokLetReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokIdentifier){
            nextToken = getNextToken();

            if(nextToken.tok == tokColon){
                nextToken = getNextToken();

                if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                    nextToken = getNextToken();

                    if(nextToken.tok == tokEquals){
                        // return expression();
                        nextToken = getNextToken();

                        if(expression()){
                            return true;
                        }
                    }
                }
            }
        }

        return Fail("inside variable declaration");

    }else return false;

    // return Fail();
}

bool Parser::assignment(){

    if(nextToken.tok == tokIdentifier){
        nextToken = getNextToken();
        if(nextToken.tok == tokEquals){
            nextToken = getNextToken();
            if(expression())
                return true;
        }

        return Fail("inside assignment");

    }else return false;
}

bool Parser::printStatement(){
    if(nextToken.tok == tokPrintReserve){
        nextToken = getNextToken();

        if(expression())
            return true;
        else return Fail("inside print");

    }else return false;
}

bool Parser::ifStatement(){

    if(nextToken.tok == tokIfReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            if(expression()){

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();

                    if(block()){

                        if(nextToken.tok == tokElseReserve){
                            nextToken = getNextToken();

                            if(block()){

                            }else return Fail("else if statement");
                        }

                        return true;
                        
                    }
                }
            }
        }

        return Fail("inside if statement");

    }else return false;
}

bool Parser::forStatement(){

    if(nextToken.tok == tokForReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            if(variableDecl()){
                
            }

            if(nextToken.tok == tokSemicolon){
                nextToken = getNextToken();

                if(expression()){

                    if(nextToken.tok == tokSemicolon){
                        nextToken = getNextToken();

                        if(assignment()){

                        }

                        if(nextToken.tok == tokBracketClose){
                            nextToken = getNextToken();

                            if(block())
                                return true;
                        }
                    }
                }
            }
        }

        return Fail("inside for");

    }else return false;
}

bool Parser::whileStatement(){

    if(nextToken.tok == tokWhileReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            if(expression()){

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();

                    if(block()){
                        return true;
                    }
                }
            }
        }

        return Fail("inside while");

    }else return false;
}

bool Parser::returnStatement(){

    if(nextToken.tok == tokReturnReserve){
        nextToken = getNextToken();

        if(expression())
            return true;
        else return Fail("inside return");

    }else return false;
}

bool Parser::functionDecl(){

    if(nextToken.tok == tokFnReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokIdentifier){
            nextToken = getNextToken();

            if(nextToken.tok == tokBracketOpen){
                nextToken = getNextToken();

                if(formalParams()){

                }

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();

                    if(nextToken.tok == tokArrow){
                        nextToken = getNextToken();

                        if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                            nextToken = getNextToken();

                            if(block())
                                return true;

                        }
                    }
                }
            }
        }

        return Fail("inside function decl");

    }else return false;
}

bool Parser::block(){

    if(nextToken.tok == tokCurlyOpen){
        nextToken = getNextToken();

        while(statement()){

        }

        if(nextToken.tok == tokCurlyClose){
            nextToken = getNextToken();

            return true;
        }

        return Fail("inside block");

    }else return false;
}

// bool Parser::identifier(){

// }

bool Parser::formalParams(){

    if(formalParam()){

        // Zero or more

        while(nextToken.tok == tokComma){
            nextToken = getNextToken();

            if(formalParam()){

            }else return Fail("inside formal paramS");

        }

        return true;

    }else return false;
}
// bool type();
    
bool Parser::formalParam(){

    if(nextToken.tok == tokIdentifier){
        nextToken = getNextToken();

        if(nextToken.tok == tokColon){
            nextToken = getNextToken();

            if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                nextToken = getNextToken();

                return true;
            }
        }

        return Fail("inside formal param");

    }else return false;
}

bool Parser::expression(){
    if(simpleExpr()){
        // nextToken = getNextToken();
        // if(!checkedOptional) {
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }

        while(nextToken.tok == tokRelOp){
            //if(nextToken.tok == tokRelOp){
                
            nextToken = getNextToken();
            // checkedOptional = false;
            if(simpleExpr()){

                // nextToken = getNextToken();
            }else return Fail("inside expression");

            //}
        }

        // Zero or more repetitions
        return true;

    }else return false;
}

bool Parser::simpleExpr(){
    if(term()){
        // nextToken = getNextToken();
        // if(!checkedOptional){
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }

        while(nextToken.tok == tokAddOp){
            //if(nextToken.tok == tokRelOp){
                
            nextToken = getNextToken();
            // checkedOptional = false;
            if(term()){

                // nextToken = getNextToken();
            }else return Fail("inside simple expr");

            //}
        }

        // Zero or more repetitions
        return true;

    }else return false;
}
// bool relationalOp();
    
bool Parser::term(){
    if(factor()){
        // if(!checkedOptional) {
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }
        // nextToken = getNextToken();

        while(nextToken.tok == tokMultOp){
            //if(nextToken.tok == tokRelOp){
            
            nextToken = getNextToken();
            // checkedOptional = false;
            if(factor()){

                // nextToken = getNextToken();
            }else return Fail("inside term");

            //}
        }

        // Zero or more repetitions
        return true;

    }else return false;
}
// bool additiveOp();

bool Parser::factor(){

    // use LL(2) for deciding between identifier and function call as both have the same First() set
    nextNextToken = getNextToken();
    usedNextNext = true;

    if(literal()){
        return true;

    }else if(nextToken.tok == tokIdentifier && nextNextToken.tok != tokBracketOpen){
        nextToken = getNextToken();
        return true;

    }else if(functionCall()){
        return true;

    }else if(subExpression()){
        return true;

    }else if(unary()){
       return true;

    }else return false;
}
// bool multiplicativeOp();

bool Parser::literal(){

    if(nextToken.tok == tokTrueReserve || nextToken.tok == tokFalseReserve || nextToken.tok == tokIntLit || nextToken.tok == tokFloatLit || nextToken.tok == tokCharLit){
        nextToken = getNextToken();
        return true;
    }else return false;

}
bool Parser::functionCall(){

    if(nextToken.tok == tokIdentifier){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            if(actualParams()){
                // nextToken = getNextToken();

                // if(nextToken.tok == tokBracketClose){
                //     return true;
                // }
            } 
            
            if(nextToken.tok == tokBracketClose){
                nextToken = getNextToken();
                return true;
            }
        }
        return Fail("inside function call");

    }else return false;
}
bool Parser::subExpression(){

    if(nextToken.tok == tokBracketOpen){
        nextToken = getNextToken();

        if(expression()){
            // nextToken = getNextToken();

            if(nextToken.tok == tokBracketClose){
                nextToken = getNextToken();
                return true;
            }
        }

        return Fail("inside sub expression");
    }else return false;
}

bool Parser::unary(){
    if((nextToken.tok == tokMultOp && nextToken.data == "-") || nextToken.tok == tokNotReserve){
        nextToken = getNextToken();

        if(expression())
            return true;
        else return Fail("inside unary");
    }else return false;
    
}

bool Parser::actualParams(){
    if(expression()){
        //nextToken = getNextToken();
        // if(!checkedOptional) {
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }

        while(nextToken.tok == tokComma){
            nextToken = getNextToken();

            if(expression()){
                // nextToken = getNextToken();
            }else return Fail("inside actual params");
        }

        return true;
    }else return false;
}

// bool booleanLiteral();
// bool integerLiteral();
// bool floatLiteral();
// bool charLiteral();