#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "AST/ASTNode.h"
#include "AST/ASTExpression.h"
#include "AST/ASTActualParams.h"
#include "AST/ASTAssign.h"
#include "AST/ASTBinOp.h"
#include "AST/ASTBlock.h"
#include "AST/ASTFormalParam.h"
#include "AST/ASTFormalParams.h"
#include "AST/ASTForStmt.h"
#include "AST/ASTFuncCall.h"
#include "AST/ASTFuncDecl.h"
#include "AST/ASTIdentifier.h"
#include "AST/ASTIfStmt.h"
#include "AST/ASTLiteral.h"
#include "AST/ASTPrint.h"
#include "AST/ASTProgram.h"
#include "AST/ASTReturn.h"
#include "AST/ASTVarDecl.h"
#include "AST/ASTWhile.h"
#include "AST/ASTUnary.h"

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

    ASTNode* Fail(std::string error);

    ASTProgram* program();

    ASTNode* statement();

    ASTVarDecl* variableDecl();
    ASTAssign* assignment();
    ASTPrint* printStatement();
    ASTIfStmt* ifStatement();
    ASTForStmt* forStatement();
    ASTWhile* whileStatement();
    ASTReturn* returnStatement();
    ASTFuncDecl* functionDecl();
    ASTBlock* block();

    // bool identifier();
    ASTFormalParams* formalParams();
    bool type();
    
    ASTFormalParam* formalParam();

    ASTExpression* expression();

    ASTExpression* simpleExpr();
    // bool relationalOp();
    
    ASTExpression* term();
    // bool additiveOp();

    ASTExpression* factor();
    // bool multiplicativeOp();

    ASTLiteral* literal();
    ASTFuncCall* functionCall();
    ASTExpression* subExpression();
    ASTUnary* unary();

    ASTActualParams* actualParams();

    // bool booleanLiteral();
    // bool integerLiteral();
    // bool floatLiteral();
    // bool charLiteral();

    

};

#endif