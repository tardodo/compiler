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

// Check if operator is a relational operator
bool SemanticVisitor::isRelOp(string relOp){
    if(relOp == ">" || relOp == ">=" || relOp == "<" || relOp == "<=" || relOp == "==" || relOp == "!=" )
        return true;
    else return false;
}


void SemanticVisitor::visit(ASTProgram* node){
    // Create global scope
    st.newScope();

    for(ASTNode* child: node->childNodes){
        
        child->accept(this);
    }

    st.deleteScope();
}

void SemanticVisitor::visit(ASTVarDecl* node){
    
    // Same variable name must not exist in the current scope
    if(st.existsCurrScope(node->identifier->name)){
        throw runtime_error("Variable with identifier " + node->identifier->name + " already exists in scope.");
    }

    // Insert into ST
    st.insert(node->identifier->name, node->type, Variable);

    node->identifier->accept(this);
    
    node->expression->accept(this);

    // Check type of var and expression
    if(node->type != lastType)
        throw runtime_error("Invalid assignment type for identifier " + node->identifier->name);

}

void SemanticVisitor::visit(ASTIdentifier* node){
   
    // make sure identifier exists
    Details details = st.lookup(node->name);
    if(details.type == "0")
        throw runtime_error("Identifier: " + node->name + " \ndoes not exist in scope.");

    lastType = details.type;
}

void SemanticVisitor::visit(ASTBinOp* node){
   
    node->leftChild->accept(this);
    string leftType = lastType;
 
    node->rightChild->accept(this);

    // Left and right must match type
    if(leftType != lastType)
        throw runtime_error("Invalid Binary Operation: Type mismatch between types " +leftType+ " and " +lastType);
    
    // Multiplicative and Additive incompatible with bool and char
    if(node->op == "*" || node->op == "/" || node->op == "+" || node->op == "-"){
        if(leftType == "bool" || leftType == "char"){
            throw runtime_error("Cannot perform "+ node->op + " Operation on " + leftType + " types");
        }
    // Most relational operators incompatible with bool
    }else if(isRelOp(node->op) && (node->op != "==" && node->op != "!=")){
        if(leftType == "bool"){
            throw runtime_error("Cannot perform "+ node->op + " Operation on " + leftType + " types");
        }
    }

    // convert last type to bool if relational
    if(isRelOp(node->op)){
        lastType = "bool";
    }
}

void SemanticVisitor::visit(ASTActualParams* node){
    
    // Look up function
    Details dets = st.lookup(lastFuncName);
    // store function name in case of other functions as parameters
    string currFuncName = lastFuncName;

    // same number of parameters as declaration
    if(node->params.size() != dets.parameters.size())
        throw runtime_error("Invalid amount of parameters for function "+ lastFuncName);

    int i = 0;
    for(ASTExpression* child: node->params){
        
        child->accept(this);
        // Check parameter types
        if(dets.parameters.at(i) != lastType)
            throw runtime_error("Invalid parameter type for function "+ currFuncName);

        i++;
    }
}

void SemanticVisitor::visit(ASTAssign* node){
    
    node->identifier->accept(this);
    string leftType = lastType;

    node->expression->accept(this);

    // match types
    if(leftType != lastType)
        throw runtime_error("Invalid Assignment of variable "+ node->identifier->name);


}

void SemanticVisitor::visit(ASTBlock* node){
   
   // Don't create new scope if For or function declaration preceeds block
    if(genNewScope)
        st.newScope();
    else genNewScope = true;

    for(ASTNode* child: node->childNodes){
       
        child->accept(this);
    }

    st.deleteScope();
   
}

void SemanticVisitor::visit(ASTFormalParam* node){

    // parameter names must be unique within function scope
    if(st.existsCurrScope(node->identifier->name)){
        throw runtime_error("Variable with identifier " + node->identifier->name + " already exists in scope.");
    }

    // insert parameter 
    st.insert(node->identifier->name, node->type, Variable);

    paramTypes.push_back(node->type);

    node->identifier->accept(this);
}

void SemanticVisitor::visit(ASTFormalParams* node){

    for(ASTFormalParam* child: node->params){
      
        child->accept(this);
    }    
}

void SemanticVisitor::visit(ASTForStmt* node){
   
    // create new scope so possible var delcaration is within For scope
    genNewScope = false;
    st.newScope();

    //optional
    if(node->varDecl != nullptr)
        node->varDecl->accept(this);
   
    node->expression->accept(this);

    // expression must be conditional
    if(lastType != "bool"){
        throw runtime_error("Condition of For statement does not resolve to a value of type bool");
    }
    
    //optional
    if(node->assignment != nullptr)
        node->assignment->accept(this);
 
    node->block->accept(this);
}

void SemanticVisitor::visit(ASTFuncCall* node){
    
    node->identifier->accept(this);

    // store name for parameter reference
    lastFuncName = node->identifier->name;
    
    // optional
    if(node->params != nullptr)
        node->params->accept(this);

    // set last type
    Details dets = st.lookup(node->identifier->name);
    lastType = dets.type;
   
}

void SemanticVisitor::visit(ASTFuncDecl* node){
   
    // Identifier must be unique
    if(st.existsCurrScope(node->identifier->name)){
        throw runtime_error("Function with identifier " + node->identifier->name + " already exists in scope.");
    
    }

    // insert into ST
    st.insert(node->identifier->name, node->type, Function);

    // preempt block scope to include parameters
    genNewScope = false;
    st.newScope();

    node->identifier->accept(this);
    
    // optional
    if(node->params != nullptr)
        node->params->accept(this);
    
    // If has params, include in ST
    if(!paramTypes.empty()){
        Details withParams = {node->type, paramTypes, Function};
        st.modify(node->identifier->name, withParams);
    }

    paramTypes.clear();

    // store name for use
    funcDeclName = node->identifier->name;
    hasReturn = false;

    node->block->accept(this);

    // If no reachable return statement detected, error
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

    // Reset var in case if stmt has return (considered limited reachability)
    hasReturn = false;

    if(node->falseBlock != nullptr){
       
        node->falseBlock->accept(this);

    }  
}

void SemanticVisitor::visit(ASTLiteral* node){
    // store type only
    lastType = node->type;
}

void SemanticVisitor::visit(ASTPrint* node){

    node->expression->accept(this);
}

void SemanticVisitor::visit(ASTReturn* node){

    // If return is not attached to a function, error
    if(funcDeclName == "")
        throw runtime_error("Return statement missing function");
   
    node->expression->accept(this);

    Details funcType = st.lookup(funcDeclName);

    // return type must match
    if(funcType.type != lastType)
        throw runtime_error("Return statement value type does not much function return type for Function: "+ funcDeclName);

    hasReturn = true;
}

void SemanticVisitor::visit(ASTUnary* node){
    
    node->expr->accept(this);

    // - only valid for numbers
    if(node->unaryOp == "-"){
        if(lastType != "int" && lastType != "float"){
            throw runtime_error("Unary operator: " + node->unaryOp +" \n\t incompatable with expression type: " + lastType);
        }  
    // not only valid for bool
    }else{
        if(lastType != "bool")
            throw runtime_error("Unary operator: " + node->unaryOp +" \n\t incompatable with expression type: " + lastType);
    }   
}

void SemanticVisitor::visit(ASTWhile* node){

    node->expression->accept(this);

    if(lastType != "bool"){
        throw runtime_error("Condition of While statement does not resolve to a value of type bool");
    }
  
    node->block->accept(this);   
}
