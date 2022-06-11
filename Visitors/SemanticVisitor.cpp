#include "SemanticVisitor.h"

#include "../AST/ASTNode.h"
#include "../AST/ASTExpression.h"
#include "../AST/ASTActualParams.h"
#include "../AST/ASTAssign.h"
#include "../AST/ASTBinOp.h"
#include "../AST/ASTBlock.h"
#include "../AST/ASTFormalParam.h"
#include "../AST/ASTFormalParams.h"
#include "../AST/ASTForStmt.h"
#include "../AST/ASTFuncCall.h"
#include "../AST/ASTFuncDecl.h"
#include "../AST/ASTIdentifier.h"
#include "../AST/ASTIfStmt.h"
#include "../AST/ASTLiteral.h"
#include "../AST/ASTPrint.h"
#include "../AST/ASTProgram.h"
#include "../AST/ASTReturn.h"
#include "../AST/ASTVarDecl.h"
#include "../AST/ASTWhile.h"
#include "../AST/ASTUnary.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

bool SemanticVisitor::isRelOp(string relOp){
    if(relOp == ">" || relOp == ">=" || relOp == "<" || relOp == "<=" || relOp == "==" || relOp == "!=" )
        return true;
    else return false;
}

void SemanticVisitor::visit(ASTProgram* node){
    
    st.newScope();

    for(ASTNode* child: node->childNodes){
        
        child->accept(this);
    }

    st.deleteScope();
    
}

void SemanticVisitor::visit(ASTVarDecl* node){
    
    // string details = st.lookup(node->identifier->name);
    if(st.existsCurrScope(node->identifier->name)){
        throw runtime_error("Variable with identifier " + node->identifier->name + " already exists in scope.");
    }

    st.insert(node->identifier->name, node->type);

    node->identifier->accept(this);
    

    node->expression->accept(this);

    if(node->type != lastType)
        throw runtime_error("Invalid assignment type for identifier " + node->identifier->name);

}

void SemanticVisitor::visit(ASTIdentifier* node){
   
    // if(st.existsCurrScope(node->name)){
    //     throw runtime_error("Variable with identifier " + node->name + " already exists in scope.");
    // }

    Details details = st.lookup(node->name);
    if(details.type == "0")
        throw runtime_error("Identifier: " + node->name + " \ndoes not exist in scope.");

    lastType = details.type;
}

void SemanticVisitor::visit(ASTBinOp* node){
   

    node->leftChild->accept(this);
    string leftType = lastType;
 
    node->rightChild->accept(this);

    if(node->op == "*" || node->op == "/" || node->op == "+" || node->op == "-"){
        if(leftType == "bool" || leftType == "char"){
            throw runtime_error("Cannot perform "+ node->op + " Operation on " + leftType + " types");
        }else if(lastType == "bool" || lastType == "char"){
            throw runtime_error("Cannot perform "+ node->op + " Operation on " + leftType + " types");
        }
    }

    if(leftType != lastType)
        throw runtime_error("Invalid Binary Operation");



    if(isRelOp(node->op)){
        lastType = "bool";
    }

}

void SemanticVisitor::visit(ASTActualParams* node){
  
    Details dets = st.lookup(lastFuncName);
    string currFuncName = lastFuncName;

    if(node->params.size() != dets.parameters.size())
        throw runtime_error("Invalid amount of parameters for function "+ lastFuncName);

    int i = 0;
    for(ASTExpression* child: node->params){
        
        child->accept(this);
        if(dets.parameters.at(i) != lastType)
            throw runtime_error("Invalid parameter type for function "+ currFuncName);

        i++;
    }

}
void SemanticVisitor::visit(ASTAssign* node){
  
    
    node->identifier->accept(this);
    string leftType = lastType;

    node->expression->accept(this);

    if(leftType != lastType)
        throw runtime_error("Invalid Assignment of variable "+ node->identifier->name);


}

void SemanticVisitor::visit(ASTBlock* node){
   
    if(genNewScope)
        st.newScope();
    else genNewScope = true;

    for(ASTNode* child: node->childNodes){
       
        child->accept(this);
    }

    st.deleteScope();
   
}

// void XMLVisitor::visit(ASTExpression* node){

// }

void SemanticVisitor::visit(ASTFormalParam* node){

    if(st.existsCurrScope(node->identifier->name)){
        throw runtime_error("Variable with identifier " + node->identifier->name + " already exists in scope.");
    }

    st.insert(node->identifier->name, node->type);
    // node->type;
    paramTypes.push_back(node->type);

    node->identifier->accept(this);

}

void SemanticVisitor::visit(ASTFormalParams* node){
   

    for(ASTFormalParam* child: node->params){
      
        child->accept(this);
    }    


}

void SemanticVisitor::visit(ASTForStmt* node){
   
    genNewScope = false;
    st.newScope();

    node->varDecl->accept(this);
   
    node->expression->accept(this);

    if(lastType != "bool"){
        throw runtime_error("Condition of For statement does not resolve to a value of type bool");
    }
  
    node->assignment->accept(this);
 
    node->block->accept(this);

   
}

void SemanticVisitor::visit(ASTFuncCall* node){
    
    
    node->identifier->accept(this);

    lastFuncName = node->identifier->name;
  
    node->params->accept(this);

    Details dets = st.lookup(node->identifier->name);
    lastType = dets.type;
   
}

void SemanticVisitor::visit(ASTFuncDecl* node){
   
    if(st.existsCurrScope(node->identifier->name)){
        throw runtime_error("Function with identifier " + node->identifier->name + " already exists in scope.");
    
    }
    st.insert(node->identifier->name, node->type);

    genNewScope = false;
    st.newScope();

    node->identifier->accept(this);
    
    node->params->accept(this);
    
    if(!paramTypes.empty()){
        Details withParams = {node->type, paramTypes};
        st.modify(node->identifier->name, withParams);
    }

    paramTypes.clear();

    //temporary insert in func scope to check for If else statements scoping
    // st.insert(node->identifier->name, node->type);

    funcDeclName = node->identifier->name;
    hasReturn = false;

    node->block->accept(this);

    if(!hasReturn)
        throw runtime_error("No Return statement for function "+ funcDeclName);

    funcDeclName = "";
    hasReturn = false;
}

void SemanticVisitor::visit(ASTIfStmt* node){
   

    node->condition->accept(this);

    if(lastType != "bool"){
        throw runtime_error("Condition of If statement does not resolve to a value of type bool");
    }
    
    node->trueBlock->accept(this);

    // Reset var in case if stmt has return
    hasReturn = false;

    if(node->falseBlock != nullptr){
       
        node->falseBlock->accept(this);

    }
    // }else if(funcDeclName != ""){
    //     if(st.existsCurrScope(funcDeclName)){

    //     }
    // }

   
}

void SemanticVisitor::visit(ASTLiteral* node){

    lastType = node->type;

    // node->value;

    
}

void SemanticVisitor::visit(ASTPrint* node){
   

    node->expression->accept(this);

   
}

void SemanticVisitor::visit(ASTReturn* node){

    if(funcDeclName == "")
        throw runtime_error("Return statement missing function");
   
    node->expression->accept(this);

    Details funcType = st.lookup(funcDeclName);

    if(funcType.type != lastType)
        throw runtime_error("Return statement value type does not much function return type for Function: "+ funcDeclName);

    hasReturn = true;
}

void SemanticVisitor::visit(ASTUnary* node){
  
    node->expr->accept(this);

   
}

void SemanticVisitor::visit(ASTWhile* node){
   

    node->expression->accept(this);

    if(lastType != "bool"){
        throw runtime_error("Condition of While statement does not resolve to a value of type bool");
    }
  
    node->block->accept(this);

   
}
