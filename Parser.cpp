#include "Parser.h"
#include <iostream>
#include <vector>

using namespace std;

Parser::Parser()
{
    // Initialize vars
    usedNextNext = false;
    reportedFail = false;
    checkedOptional = false;
}

Parser::~Parser()
{
}

// Method which interacts with Lexer
Token Parser::getNextToken(){
    
    Token temp = {tokOther, "boo"};

    // If k=2 lookahead isn't used, fetch next valid token
    if(!usedNextNext){
        // Filter unnecessary tokens
        while(temp.tok == tokOther){
            temp = nextWord();

            // report error
            if(temp.tok == tokInvalid){
                throw runtime_error("Unable to process string: " + temp.data);
            }
        }
        return temp;

    // Otherwise return the token previously fetched at k=2
    }else{
        usedNextNext = false;
        return nextNextToken;
    }


    
}

// Root node
ASTProgram* Parser::program(){
    nextToken = getNextToken();
    
    vector<ASTNode*> stmts;
    ASTNode* node;

    // Zero or more statements
    while((node = statement()) != nullptr){
        
        // Collect statements
        stmts.push_back(node);
    }

    // If eof reached and no fails reported, return root node with statements
    if(nextToken.tok == tokEndOfFile && !reportedFail)
        return new ASTProgram(stmts);
    else return nullptr;

}

ASTNode* Parser::Fail(string error){
    cout << "Syntax Error: " << error << endl;
    reportedFail = true;
    return nullptr;
}

// Parse statement
ASTNode* Parser::statement(){

    ASTNode* node;

    if((node = variableDecl()) != nullptr){

        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("Missing ';' at Variable Declaration");
    
    }else if((node = assignment()) != nullptr){
        
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("Missing ';' at Assignment");
         
    }else if((node = printStatement()) != nullptr){
     
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("Missing ';' at Print statement");

    }else if((node = ifStatement()) != nullptr){
        return node;

    }else if((node = forStatement()) != nullptr){
        return node;

    }else if((node = whileStatement()) != nullptr){
        return node;

    }else if((node = returnStatement()) != nullptr){
       
        if(nextToken.tok == tokSemicolon){
            nextToken = getNextToken();
            return node;
        }else return Fail("Missing ';' at Return statement");

    }else if((node = functionDecl()) != nullptr){
        return node;

    }else if((node = block()) != nullptr){
        return node;
    }

    return nullptr;
}

// Parse Variable Declaration
ASTVarDecl* Parser::variableDecl(){

    if(nextToken.tok == tokLetReserve){
        nextToken = getNextToken();
        string error = "Identifier";

        if(nextToken.tok == tokIdentifier){
            ASTIdentifier* id = new ASTIdentifier(nextToken.data);
            nextToken = getNextToken();
            error = "':'";

            if(nextToken.tok == tokColon){
                nextToken = getNextToken();
                error = "Type";

                if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                    string type = nextToken.data;
                    nextToken = getNextToken();
                    error = "'='";

                    if(nextToken.tok == tokEquals){
                        nextToken = getNextToken();
                        error = "Expression";
                        
                        ASTExpression* expr;

                        if((expr = expression()) != nullptr){
                            return new ASTVarDecl(id, type, expr);
                        }
                    }
                }
            }
        }

        Fail("Missing " + error+ " at Variable declaration");
        return nullptr;

    }else return nullptr;
}

// Parse Assignment
ASTAssign* Parser::assignment(){

    if(nextToken.tok == tokIdentifier){
        ASTIdentifier* id = new ASTIdentifier(nextToken.data);
        string error = "'=''";

        nextToken = getNextToken();
        if(nextToken.tok == tokEquals){
            nextToken = getNextToken();
            error = "Expression";

            ASTExpression* node;
            if((node = expression()) != nullptr)
                return new ASTAssign(id, node);
        }

        Fail("Missing " + error+ " at Assignment");
        return nullptr;

    }else return nullptr;
}

// Parse print
ASTPrint* Parser::printStatement(){
    if(nextToken.tok == tokPrintReserve){
        nextToken = getNextToken();

        ASTExpression* node;
        if((node = expression()) != nullptr)
            return new ASTPrint(node);
        else {
            Fail("Missing Expression at Print statement");
            return nullptr;
        }

    }else return nullptr;
}

// Parse If
ASTIfStmt* Parser::ifStatement(){

    if(nextToken.tok == tokIfReserve){
        nextToken = getNextToken();
        string error = "'('";

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();
            error = "Condition";

            ASTExpression* condition;
            if((condition = expression()) != nullptr){
                error = "'('";

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();
                    error = "Body";

                    ASTBlock* ifBlock;
                    if((ifBlock = block()) != nullptr){
                        
                        ASTBlock* elseBlock = nullptr;

                        // Optional
                        if(nextToken.tok == tokElseReserve){
                            nextToken = getNextToken();

                            if((elseBlock = block()) == nullptr){
                                Fail("Missing Body at Else statement");
                                return nullptr;                                
                            }
                        }

                        return new ASTIfStmt(condition, ifBlock, elseBlock);
                        
                    }
                }
            }
        }

        Fail("Missing " + error+ " at If statement");
        return nullptr;

    }else return nullptr;
}

// Parse For
ASTForStmt* Parser::forStatement(){

    if(nextToken.tok == tokForReserve){
        nextToken = getNextToken();
        string error = "'('";

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();
            error = "';'";

            // Optional
            ASTVarDecl* varDecl = variableDecl();

            if(nextToken.tok == tokSemicolon){
                nextToken = getNextToken();
                error = "Expression";

                ASTExpression* expr;
                if((expr = expression()) != nullptr){
                    error = "';'";

                    if(nextToken.tok == tokSemicolon){
                        nextToken = getNextToken();
                        error = "')'";

                        // Optional
                        ASTAssign* assign = assignment();

                        if(nextToken.tok == tokBracketClose){
                            nextToken = getNextToken();
                            error = "Body";

                            ASTBlock* body;
                            if((body = block()) != nullptr)
                                return new ASTForStmt(varDecl, expr, assign, body);
                        }
                    }
                }
            }
        }

        Fail("Missing " + error + " at For statement");
        return nullptr;

    }else return nullptr;
}

// Parse While
ASTWhile* Parser::whileStatement(){

    if(nextToken.tok == tokWhileReserve){
        nextToken = getNextToken();
        string error = "'('";

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();
            error = "Condition";

            ASTExpression* expr;
            if((expr = expression()) != nullptr){
                error = "')'";

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();
                    error = "Body";

                    ASTBlock* body;
                    if((body = block()) != nullptr){
                        return new ASTWhile(expr, body);
                    }
                }
            }
        }

        Fail("Missing " + error + " at While statement");
        return nullptr;

    }else return nullptr;
}

// Parse return 
ASTReturn* Parser::returnStatement(){

    if(nextToken.tok == tokReturnReserve){
        nextToken = getNextToken();

        ASTExpression* expr;
        if((expr = expression()) != nullptr)
            return new ASTReturn(expr);
        else{
            Fail("Missing Expression at Return statement");
            return nullptr;
        }

    }else return nullptr;
}

// Parse Function Declaration
ASTFuncDecl* Parser::functionDecl(){

    if(nextToken.tok == tokFnReserve){
        nextToken = getNextToken();
        string error = "Identifier";

        if(nextToken.tok == tokIdentifier){
            ASTIdentifier* id = new ASTIdentifier(nextToken.data);

            nextToken = getNextToken();
            error = "'('";

            if(nextToken.tok == tokBracketOpen){
                nextToken = getNextToken();
                error = "')'";

                // Optional
                ASTFormalParams* params = formalParams();

                if(nextToken.tok == tokBracketClose){
                    nextToken = getNextToken();
                    error = "'->'";

                    if(nextToken.tok == tokArrow){
                        nextToken = getNextToken();
                        error = "Type";

                        if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                            string dataType = nextToken.data;

                            nextToken = getNextToken();
                            error = "Body";

                            ASTBlock* body;
                            if((body = block()) != nullptr)
                                return new ASTFuncDecl(id, params, dataType, body);

                        }
                    }
                }
            }
        }

        Fail("Missing "+error+" at Function Declaration");
        return nullptr;

    }else return nullptr;
}

// Parse Block
ASTBlock* Parser::block(){

    if(nextToken.tok == tokCurlyOpen){
        nextToken = getNextToken();

        vector <ASTNode*> statementList;
        ASTNode* stmt;

        // Zero or more
        while((stmt = statement()) != nullptr){
            statementList.push_back(stmt);
        }

        if(nextToken.tok == tokCurlyClose){
            nextToken = getNextToken();

            return new ASTBlock(statementList);
        }

        Fail("Missing '}' at Code Body/Block");
        return nullptr;

    }else return nullptr;
}

// Parse FormalParams
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
                Fail("Missing Parameter at Function Declaration");
                return nullptr;

            } 

        }

        return new ASTFormalParams(paramsList);

    }else return nullptr;
}

// Parse Formal Param   
ASTFormalParam* Parser::formalParam(){

    if(nextToken.tok == tokIdentifier){
        ASTIdentifier* id = new ASTIdentifier(nextToken.data);

        nextToken = getNextToken();
        string error = "':'";

        if(nextToken.tok == tokColon){
            nextToken = getNextToken();
            error = "Type";

            if(nextToken.tok == tokFloatReserve || nextToken.tok == tokIntReserve || nextToken.tok == tokBoolReserve || nextToken.tok == tokCharReserve){
                string dataType = nextToken.data;
                nextToken = getNextToken();

                return new ASTFormalParam(id, dataType);
            }
        }

        Fail("Missing " +error+ " in Parameter at Function Declaration");
        return nullptr;

    }else return nullptr;
}

// Parse Expression
ASTExpression* Parser::expression(){

    ASTExpression* expr;
    if((expr = simpleExpr()) != nullptr){
      
        ASTExpression* leftExpr;
        ASTExpression* rightExpr;
        string relOp;

        // Zero or more
        while(nextToken.tok == tokRelOp){
            relOp = nextToken.data;
            leftExpr = expr;

            nextToken = getNextToken();

            if((rightExpr = simpleExpr()) != nullptr){
                // Left associative
                expr = new ASTBinOp(leftExpr, relOp, rightExpr);
            }else{
                Fail("Missing Expression in Relational Operation");
                return nullptr;
            }
        }

        return expr;

    }else return nullptr;
}

// Parse Simple Expression
ASTExpression* Parser::simpleExpr(){

    ASTExpression* expr;
    if((expr = term()) != nullptr){
     
        ASTExpression* leftExpr;
        ASTExpression* rightExpr;
        string addOp;

        // Zero or more
        while(nextToken.tok == tokAddOp){
            addOp = nextToken.data;
            leftExpr = expr;
            nextToken = getNextToken();

            if((rightExpr = term()) != nullptr){
                // Left associative
                expr = new ASTBinOp(leftExpr, addOp, rightExpr);
            }else {
                Fail("Missing Expression in Additive Operation");
                return nullptr;
            }
        }

        return expr;

    }else return nullptr;
}

// Parse term    
ASTExpression* Parser::term(){

    ASTExpression* expr;
    if((expr = factor()) != nullptr){

        ASTExpression* leftExpr;
        ASTExpression* rightExpr;
        string multOp;

        // Zero or more
        while(nextToken.tok == tokMultOp){
            multOp = nextToken.data;
            leftExpr = expr;
            nextToken = getNextToken();
         
            if((rightExpr = factor()) != nullptr){
                // Left associative
                expr = new ASTBinOp(leftExpr, multOp, rightExpr);
            }else {
                Fail("Missing Expression in Multiplicative Operation");
                return nullptr;
            }
        }

        return expr;

    }else return nullptr;
}

// Parse factor
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

// Parse literal
ASTLiteral* Parser::literal(){

    if(nextToken.tok == tokTrueReserve || nextToken.tok == tokFalseReserve || nextToken.tok == tokIntLit || nextToken.tok == tokFloatLit || nextToken.tok == tokCharLit){
        ASTLiteral* lit = new ASTLiteral(nextToken.tok, nextToken.data);
        nextToken = getNextToken();
        return lit;
    }else return nullptr;
}

// Parse Function Call
ASTFuncCall* Parser::functionCall(){

    if(nextToken.tok == tokIdentifier){
        ASTIdentifier* id = new ASTIdentifier(nextToken.data);

        nextToken = getNextToken();
        string error = "'('";

        if(nextToken.tok == tokBracketOpen){
            nextToken = getNextToken();
            error = "')'";

            // Optional
            ASTActualParams* params = actualParams();
            
            if(nextToken.tok == tokBracketClose){
                nextToken = getNextToken();
                return new ASTFuncCall(id, params);
            }
        }
        Fail("Missing "+ error+" at Function Call");
        return nullptr;

    }else return nullptr;
}

// Parse SubExpression
ASTExpression* Parser::subExpression(){

    if(nextToken.tok == tokBracketOpen){
        nextToken = getNextToken();
        string error = "Expression";

        ASTExpression* expr;
        if((expr = expression()) != nullptr){
            error = "')'";

            if(nextToken.tok == tokBracketClose){
                nextToken = getNextToken();
                return expr;
            }
        }

        Fail("Missing " +error+" at Sub Expression");
        return nullptr;

    }else return nullptr;
}

// Parse Unary
ASTUnary* Parser::unary(){
    if((nextToken.tok == tokAddOp && nextToken.data == "-") || nextToken.tok == tokNotReserve){
        string unaryOp = nextToken.data;
        nextToken = getNextToken();

        ASTExpression* expr;
        if((expr = expression()) != nullptr)
            return new ASTUnary(expr, unaryOp);
        else{
            Fail("Missing Expression at Unary Operation");
            return nullptr;
        }
    }else return nullptr;
    
}

// Parse Actual Params
ASTActualParams* Parser::actualParams(){

    vector<ASTExpression*> params;
    ASTExpression* expr;
    if((expr = expression()) != nullptr){

        params.push_back(expr);

        // Zero or more
        while(nextToken.tok == tokComma){
            nextToken = getNextToken();

            if((expr = expression()) != nullptr){
                params.push_back(expr);
                // nextToken = getNextToken();
            }else{
                Fail("Missing Parameter at Function Call");
                return nullptr;
            } 
        }

        return new ASTActualParams(params);

    }else return nullptr;
}
