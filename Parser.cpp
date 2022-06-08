#include "Parser.h"
// #include "AST/ASTNode.h"
// #include "AST/ASTExpression.h"
// #include "AST/ASTActualParams.h"
// #include "AST/ASTAssign.h"
// #include "AST/ASTBinOp.h"
// #include "AST/ASTBlock.h"
// #include "AST/ASTFormalParam.h"
// #include "AST/ASTFormalParams.h"
// #include "AST/ASTForStmt.h"
// #include "AST/ASTFuncCall.h"
// #include "AST/ASTFuncDecl.h"
// #include "AST/ASTIdentifier.h"
// #include "AST/ASTIfStmt.h"
// #include "AST/ASTLiteral.h"
// #include "AST/ASTPrint.h"
// #include "AST/ASTProgram.h"
// #include "AST/ASTReturn.h"
// #include "AST/ASTVarDecl.h"
// #include "AST/ASTWhile.h"
#include <iostream>
#include <vector>

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

ASTProgram* Parser::program(){
    nextToken = getNextToken();

    // if(statement()){
    //     if(nextToken.tok == tokEndOfFile)
    //         return true;
    //     else Fail();
    // }else if(nextToken.tok == tokEndOfFile)
    //     return true;
    // else Fail();
    ASTProgram* prog;
    vector<ASTNode*> stmts;
    ASTNode* node;

    // Zero or more statements
    while((node = statement()) != nullptr){
        // nextToken = getNextToken();
        stmts.push_back(node);
        //node = statement();
        // if(nextToken.tok == tokEndOfFile)
        //     return true;
        // cout << "outer loop" << endl;

    }

    if(nextToken.tok == tokEndOfFile && !reportedFail)
        return new ASTProgram(stmts);
    else return nullptr;

}

ASTNode* Parser::Fail(string error){
    cout << "Syntax Error at " << error << endl;
    reportedFail = true;
    return nullptr;
}

ASTNode* Parser::statement(){

    ASTNode* node;
    // node = variableDecl();

    if((node = variableDecl()) != nullptr){
        // if(!checkedOptional) nextToken = getNextToken();
        // else checkedOptional = false;

        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("variable declaration");
    
    }else if((node = assignment()) != nullptr){
        //nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("assignment");
         
    }else if((node = printStatement()) != nullptr){
        // nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("print statement");

    }else if((node = ifStatement()) != nullptr){
        return node;

    }else if((node = forStatement()) != nullptr){
        return node;

    }else if((node = whileStatement()) != nullptr){
        return node;

    }else if((node = returnStatement()) != nullptr){
        // nextToken = getNextToken();
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("return");

    }else if((node = functionDecl()) != nullptr){
        return node;

    }else if((node = block()) != nullptr){
        return node;
    }

    return nullptr;
}

ASTVarDecl* Parser::variableDecl(){

    if(nextToken.tok == tokLetReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokIdentifier){
            ASTIdentifier* id = new ASTIdentifier(nextToken.data);
            nextToken = getNextToken();

            if(nextToken.tok == tokColon){
                nextToken = getNextToken();

                if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                    string type = nextToken.data;
                    nextToken = getNextToken();

                    if(nextToken.tok == tokEquals){
                        // return expression();
                        nextToken = getNextToken();
                        
                        ASTExpression* expr;

                        if((expr = expression()) != nullptr){
                            return new ASTVarDecl(id, type, expr);
                        }
                    }
                }
            }
        }

        Fail("inside variable declaration");
        return nullptr;

    }else return nullptr;

    // return Fail();
}

ASTAssign* Parser::assignment(){

    if(nextToken.tok == tokIdentifier){
        ASTIdentifier* id = new ASTIdentifier(nextToken.data);
        
        nextToken = getNextToken();
        if(nextToken.tok == tokEquals){
            nextToken = getNextToken();

            ASTExpression* node;
            if((node = expression()) != nullptr)
                return new ASTAssign(id, node);
        }

        Fail("inside assignment");
        return nullptr;

    }else return nullptr;
}

ASTPrint* Parser::printStatement(){
    if(nextToken.tok == tokPrintReserve){
        nextToken = getNextToken();

        ASTExpression* node;
        if((node = expression()) != nullptr)
            return new ASTPrint(node);
        else {
            Fail("inside print");
            return nullptr;
        }

    }else return nullptr;
}

ASTIfStmt* Parser::ifStatement(){

    if(nextToken.tok == tokIfReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            ASTExpression* condition;
            if((condition = expression()) != nullptr){

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();

                    ASTBlock* ifBlock;
                    if((ifBlock = block()) != nullptr){
                        
                        ASTBlock* elseBlock = nullptr;

                        if(nextToken.tok == tokElseReserve){
                            nextToken = getNextToken();

                            if((elseBlock = block()) == nullptr){
                                Fail("else if statement");
                                return nullptr;                                
                            }
                        }

                        return new ASTIfStmt(condition, ifBlock, elseBlock);
                        
                    }
                }
            }
        }

        Fail("inside if statement");
        return nullptr;

    }else return nullptr;
}

ASTForStmt* Parser::forStatement(){

    if(nextToken.tok == tokForReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            ASTVarDecl* varDecl = variableDecl();
            // if(variableDecl()){
                
            // }

            if(nextToken.tok == tokSemicolon){
                nextToken = getNextToken();

                ASTExpression* expr;
                if((expr = expression()) != nullptr){

                    if(nextToken.tok == tokSemicolon){
                        nextToken = getNextToken();

                        ASTAssign* assign = assignment();
                        // if(assignment()){

                        // }

                        if(nextToken.tok == tokBracketClose){
                            nextToken = getNextToken();

                            ASTBlock* body;
                            if((body = block()) != nullptr)
                                return new ASTForStmt(varDecl, expr, assign, body);
                        }
                    }
                }
            }
        }

        Fail("inside for");
        return nullptr;

    }else return nullptr;
}

ASTWhile* Parser::whileStatement(){

    if(nextToken.tok == tokWhileReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            ASTExpression* expr;
            if((expr = expression()) != nullptr){

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();

                    ASTBlock* body;
                    if((body = block()) != nullptr){
                        return new ASTWhile(expr, body);
                    }
                }
            }
        }

        Fail("inside while");
        return nullptr;

    }else return nullptr;
}

ASTReturn* Parser::returnStatement(){

    if(nextToken.tok == tokReturnReserve){
        nextToken = getNextToken();

        ASTExpression* expr;
        if((expr = expression()) != nullptr)
            return new ASTReturn(expr);
        else{
            Fail("inside return");
            return nullptr;
        }

    }else return nullptr;
}

ASTFuncDecl* Parser::functionDecl(){

    if(nextToken.tok == tokFnReserve){
        nextToken = getNextToken();

        if(nextToken.tok == tokIdentifier){
            ASTIdentifier* id = new ASTIdentifier(nextToken.data);

            nextToken = getNextToken();

            if(nextToken.tok == tokBracketOpen){
                nextToken = getNextToken();

                ASTFormalParams* params = formalParams();
                // if(formalParams()){

                // }

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();

                    if(nextToken.tok == tokArrow){
                        nextToken = getNextToken();

                        if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                            string dataType = nextToken.data;

                            nextToken = getNextToken();

                            ASTBlock* body;
                            if((body = block()) != nullptr)
                                return new ASTFuncDecl(id, params, dataType, body);

                        }
                    }
                }
            }
        }

        Fail("inside function decl");
        return nullptr;

    }else return nullptr;
}

ASTBlock* Parser::block(){

    if(nextToken.tok == tokCurlyOpen){
        nextToken = getNextToken();

        vector <ASTNode*> statementList;
        ASTNode* stmt;
        while((stmt = statement()) != nullptr){
            statementList.push_back(stmt);
        }

        if(nextToken.tok == tokCurlyClose){
            nextToken = getNextToken();

            return new ASTBlock(statementList);
        }

        Fail("inside block");
        return nullptr;

    }else return nullptr;
}

// bool Parser::identifier(){

// }

ASTFormalParams* Parser::formalParams(){

    vector<ASTFormalParam*> paramsList;
    ASTFormalParam* param;
    if((param = formalParam()) != nullptr){

        paramsList.push_back(param);

        // Zero or more

        while(nextToken.tok == tokComma){
            nextToken = getNextToken();

            if((param = formalParam()) != nullptr){
                paramsList.push_back(param);

            }else{
                Fail("inside formal paramS");
                return nullptr;

            } 

        }

        return new ASTFormalParams(paramsList);

    }else return nullptr;
}
// bool type();
    
ASTFormalParam* Parser::formalParam(){

    if(nextToken.tok == tokIdentifier){
        ASTIdentifier* id = new ASTIdentifier(nextToken.data);

        nextToken = getNextToken();

        if(nextToken.tok == tokColon){
            nextToken = getNextToken();

            if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                string dataType = nextToken.data;
                nextToken = getNextToken();

                return new ASTFormalParam(id, dataType);
            }
        }

        Fail("inside formal param");
        return nullptr;

    }else return nullptr;
}

ASTExpression* Parser::expression(){

    ASTExpression* expr;
    if((expr = simpleExpr()) != nullptr){
        // nextToken = getNextToken();
        // if(!checkedOptional) {
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }

        // ASTBinOp* binOpNode = nullptr;
        ASTExpression* leftExpr;
        ASTExpression* rightExpr;
        string relOp;

        while(nextToken.tok == tokRelOp){
            //if(nextToken.tok == tokRelOp){
            relOp = nextToken.data;
            leftExpr = expr;

            nextToken = getNextToken();

            
            // checkedOptional = false;
            if((rightExpr = simpleExpr()) != nullptr){
                expr = new ASTBinOp(leftExpr, relOp, rightExpr);
                // nextToken = getNextToken();
            }else{
                Fail("inside expression");
                return nullptr;
            }

            //}
        }

        // Zero or more repetitions
        return expr;

    }else return nullptr;
}

ASTExpression* Parser::simpleExpr(){

    ASTExpression* expr;
    if((expr = term()) != nullptr){
        // nextToken = getNextToken();
        // if(!checkedOptional){
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }

        ASTExpression* leftExpr;
        ASTExpression* rightExpr;
        string addOp;

        while(nextToken.tok == tokAddOp){
            //if(nextToken.tok == tokRelOp){
            addOp = nextToken.data;
            leftExpr = expr;

            nextToken = getNextToken();
            // checkedOptional = false;
            if((rightExpr = term()) != nullptr){
                expr = new ASTBinOp(leftExpr, addOp, rightExpr);

                // nextToken = getNextToken();
            }else {
                Fail("inside simple expr");
                return nullptr;
            }

            //}
        }

        // Zero or more repetitions
        return expr;

    }else return nullptr;
}
// bool relationalOp();
    
ASTExpression* Parser::term(){

    ASTExpression* expr;
    if((expr = factor()) != nullptr){
        // if(!checkedOptional) {
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }
        // nextToken = getNextToken();

        ASTExpression* leftExpr;
        ASTExpression* rightExpr;
        string multOp;

        while(nextToken.tok == tokMultOp){
            //if(nextToken.tok == tokRelOp){
            multOp = nextToken.data;
            leftExpr = expr;

            nextToken = getNextToken();
            // checkedOptional = false;
            if((rightExpr = factor()) != nullptr){
                expr = new ASTBinOp(leftExpr, multOp, rightExpr);

                // nextToken = getNextToken();
            }else {
                Fail("inside term");
                return nullptr;
            }

            //}
        }

        // Zero or more repetitions
        return expr;

    }else return nullptr;
}
// bool additiveOp();

ASTExpression* Parser::factor(){

    // use LL(2) for deciding between identifier and function call as both have the same First() set
    nextNextToken = getNextToken();
    usedNextNext = true;

    ASTExpression* node;

    if((node = literal()) != nullptr){
        return node;

    }else if(nextToken.tok == tokIdentifier && nextNextToken.tok != tokBracketOpen){
        node = new ASTIdentifier(nextToken.data);
        nextToken = getNextToken();
        return node;

    }else if((node = functionCall()) != nullptr){
        return node;

    }else if((node = subExpression()) != nullptr){
        return node;

    }else if((node = unary()) != nullptr){
       return node;

    }else return nullptr;
}
// bool multiplicativeOp();

ASTLiteral* Parser::literal(){

    if(nextToken.tok == tokTrueReserve || nextToken.tok == tokFalseReserve || nextToken.tok == tokIntLit || nextToken.tok == tokFloatLit || nextToken.tok == tokCharLit){
        ASTLiteral* lit = new ASTLiteral(nextToken.tok, nextToken.data);
        nextToken = getNextToken();
        return lit;
    }else return nullptr;

}
ASTFuncCall* Parser::functionCall(){

    if(nextToken.tok == tokIdentifier){
        ASTIdentifier* id = new ASTIdentifier(nextToken.data);

        nextToken = getNextToken();

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();

            ASTActualParams* params = actualParams();
            // if(actualParams()){
            //     // nextToken = getNextToken();

            //     // if(nextToken.tok == tokBracketClose){
            //     //     return true;
            //     // }
            // } 
            
            if(nextToken.tok == tokBracketClose){
                nextToken = getNextToken();
                return new ASTFuncCall(id, params);
            }
        }
        Fail("inside function call");
        return nullptr;

    }else return nullptr;
}
ASTExpression* Parser::subExpression(){

    if(nextToken.tok == tokBracketOpen){
        nextToken = getNextToken();

        ASTExpression* expr;
        if((expr = expression()) != nullptr){
            // nextToken = getNextToken();

            if(nextToken.tok == tokBracketClose){
                nextToken = getNextToken();
                return expr;
            }
        }

        Fail("inside sub expression");
        return nullptr;

    }else return nullptr;
}

ASTUnary* Parser::unary(){
    if((nextToken.tok == tokMultOp && nextToken.data == "-") || nextToken.tok == tokNotReserve){
        nextToken = getNextToken();

        ASTExpression* expr;
        if((expr = expression()) != nullptr)
            return new ASTUnary(expr);
        else{
            Fail("inside unary");
            return nullptr;
        }
    }else return nullptr;
    
}

ASTActualParams* Parser::actualParams(){

    vector<ASTExpression*> params;
    ASTExpression* expr;
    if((expr = expression()) != nullptr){
        //nextToken = getNextToken();
        // if(!checkedOptional) {
        //     nextToken = getNextToken();
        //     checkedOptional = true;
        // }

        params.push_back(expr);

        while(nextToken.tok == tokComma){
            nextToken = getNextToken();

            if((expr = expression()) != nullptr){
                params.push_back(expr);
                // nextToken = getNextToken();
            }else{
                Fail("inside actual params");
                return nullptr;
            } 
        }

        return new ASTActualParams(params);

    }else return nullptr;
}

// bool booleanLiteral();
// bool integerLiteral();
// bool floatLiteral();
// bool charLiteral();