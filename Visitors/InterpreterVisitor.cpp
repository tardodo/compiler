#include "InterpreterVisitor.h"

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

// check if is a relational operator
bool InterpreterVisitor::isRelOp(string relOp){
    if(relOp == ">" || relOp == ">=" || relOp == "<" || relOp == "<=" || relOp == "==" || relOp == "!=" )
        return true;
    else return false;
}

// Compute binary operations for int
string InterpreterVisitor::computeBinOp(int lVal, int rVal, string operand){
    int tempRes;
    if(isRelOp(operand)){
        lastType = "bool";

        if(operand == ">"){
            if(lVal > rVal) return "true";
            else return "false";
        }else if(operand == ">="){
            if(lVal >= rVal) return "true";
            else return "false";
        }else if(operand == "<"){
            if(lVal < rVal) return "true";
            else return "false";
        }else if(operand == "<="){
            if(lVal <= rVal) return "true";
            else return "false";
        }else if(operand == "=="){
            if(lVal == rVal) return "true";
            else return"false";
        }else if(operand == "!="){
            if(lVal != rVal) return "true";
            else return "false";
        }

    }else if(operand == "*"){
        tempRes = lVal * rVal;

    }else if(operand == "/"){
        tempRes = lVal / rVal;

    }else if(operand == "+"){
        tempRes = lVal + rVal;

    }else if(operand == "-"){
        tempRes = lVal - rVal;

    }

    return to_string(tempRes);

}

// Compute binary operations for floats
string InterpreterVisitor::computeBinOp(float lVal, float rVal, string operand){
    float tempRes;
    if(isRelOp(operand)){
        lastType = "bool";

        if(operand == ">"){
            if(lVal > rVal) return "true";
            else return "false";
        }else if(operand == ">="){
            if(lVal >= rVal) return "true";
            else return "false";
        }else if(operand == "<"){
            if(lVal < rVal) return "true";
            else return "false";
        }else if(operand == "<="){
            if(lVal <= rVal) return "true";
            else return "false";
        }else if(operand == "=="){
            if(lVal == rVal) return "true";
            else return"false";
        }else if(operand == "!="){
            if(lVal != rVal) return "true";
            else return "false";
        }

    }else if(operand == "*"){
        tempRes = lVal * rVal;

    }else if(operand == "/"){
        tempRes = lVal / rVal;

    }else if(operand == "+"){
        tempRes = lVal + rVal;

    }else if(operand == "-"){
        tempRes = lVal - rVal;

    }

    return to_string(tempRes);
}

// Compute relational operations for char
string InterpreterVisitor::computeBinOp(char lVal, char rVal, string operand){

    lastType = "bool";

    if(operand == ">"){
        if(lVal > rVal) return "true";
        else return "false";
    }else if(operand == ">="){
        if(lVal >= rVal) return "true";
        else return "false";
    }else if(operand == "<"){
        if(lVal < rVal) return "true";
        else return "false";
    }else if(operand == "<="){
        if(lVal <= rVal) return "true";
        else return "false";
    }else if(operand == "=="){
        if(lVal == rVal) return "true";
        else return"false";
    }else{
        if(lVal != rVal) return "true";
        else return "false";
    }
    
}

// Begin visiting nodes and create base program scope
void InterpreterVisitor::visit(ASTProgram* node){
    
    st.newScope();

    for(ASTNode* child: node->childNodes){
        
        child->accept(this);
    }

    st.deleteScope();
    
}

// Variable Declaration node
// Insert variable with type into current active scope and later add in value after it has been computed
void InterpreterVisitor::visit(ASTVarDecl* node){

    // Insert into ST first so that identifier node functions properly
    st.insert(node->identifier->name, node->type, Variable);

    node->identifier->accept(this);
    
    node->expression->accept(this);

    // Once expression has been evaluated, assign it to variable in ST
    Details dets = st.lookup(node->identifier->name);
    dets.value = lastValue;
    st.modify(node->identifier->name, dets);
}

// Identifier Node
// Look up variable from ST and assign values to member variables
void InterpreterVisitor::visit(ASTIdentifier* node){

    Details details = st.lookup(node->name);

    // To carry forward type of variable
    lastType = details.type;

    // To carry forward value of variable
    if(details.symbolType == Variable && !details.value.empty()){
        lastValue = details.value;
    }

}

// Binary Operation Node
// Evaluate left, then right and compute value
// Binary operations are only valid for float and int
void InterpreterVisitor::visit(ASTBinOp* node){
   

    node->leftChild->accept(this);
    // Store attributes of left child
    string leftType = lastType;
    string leftValue = lastValue;
 
    node->rightChild->accept(this);

    // Determine if int or float and compute value
    if(leftType == "int"){
        int lVal = stoi(leftValue);
        int rVal = stoi(lastValue);
        lastValue = computeBinOp(lVal, rVal, node->op);
    }else if(leftType == "float"){
        float lVal = stof(leftValue);
        float rVal = stof(lastValue);
        lastValue = computeBinOp(lVal, rVal, node->op);
    }else if(leftType == "char"){
        char lVal = leftValue[1];
        char rVal = lastValue[1];
        lastValue = computeBinOp(lVal, rVal, node->op);
    }else{
        if(node->op == "=="){
            if(leftValue == lastValue) lastValue = "true";
            else lastValue = "false";
        }else{
            if(leftValue != lastValue) lastValue = "true";
            else lastValue = "false";
        }
        lastType = "bool";
    }
    
}

// Actual Parameters Node
// Look up function from ST and create parameterized variables
void InterpreterVisitor::visit(ASTActualParams* node){
    
    // lookup to obtain parameter identifiers for func
    Details dets = st.lookup(lastFuncName);

    int i = 0;
    for(ASTExpression* child: node->params){
        
        child->accept(this);
        
        // Set details for variable based on child node data
        Details paramDets = {lastType, {}, Variable, lastValue};

        // Insert into ST within function scope 
        st.insert(dets.parameters.at(i), paramDets);
        

        i++;
    }
}

// Assignment Node
// Lookup variable from ST and assign new value
void InterpreterVisitor::visit(ASTAssign* node){
  
    
    node->identifier->accept(this);

    node->expression->accept(this);

    // get variable info from ST
    Details dets = st.lookup(node->identifier->name);

    // Assign new value obtained from evaluated expression
    dets.value = lastValue;

    // Insert into ST
    st.modify(node->identifier->name, dets);
}

// Block Node
// Generate new scopes
void InterpreterVisitor::visit(ASTBlock* node){
    
    // if a scope hasn't already been created from a For, While, Func, then create new scope
    if(genNewScope)
        st.newScope();
    else genNewScope = true;

    for(ASTNode* child: node->childNodes){
       
        child->accept(this);
    }

    // Delete scope of block or of For, While, Func
    st.deleteScope();
}

// Formal Parameter Node
// Simply obtain the identifier names to be carried over. Type attribute will be set by the value itself in Actual Params
void InterpreterVisitor::visit(ASTFormalParam* node){
   
    paramNames.push_back(node->identifier->name);

}

// Formal Parameters Node
// Visit each formal param
void InterpreterVisitor::visit(ASTFormalParams* node){
   
    for(ASTFormalParam* child: node->params){
      
        child->accept(this);
    }    
}

// For Statement Node
// Generate new scope for possible var decl and loop until expression evaluates to false 
void InterpreterVisitor::visit(ASTForStmt* node){
   
    // New scope for possible var decl
    st.newScope();

    if(node->varDecl != nullptr)
        node->varDecl->accept(this); 

    node->expression->accept(this);

    // Loop until value returned from expression is not "true"
    while(lastValue == "true"){
        
        // execute block
        node->block->accept(this);

        // update possible assignment
        if(node->assignment != nullptr)
            node->assignment->accept(this);

        // Re-evaluate condition
        node->expression->accept(this);
    }

    st.deleteScope();
}

// Function Call Node
// Generate new scope, execute function body
void InterpreterVisitor::visit(ASTFuncCall* node){
    
    node->identifier->accept(this);

    // Keep track of name for parameters
    lastFuncName = node->identifier->name;
    
    // New scope, so not needed in block
    genNewScope = false;
    st.newScope();

    // Insert optional parameter variables into ST
    if(node->params != nullptr)
        node->params->accept(this);

    // lookup function for function body and return type
    Details dets = st.lookup(node->identifier->name);

    // Set variables in case parameters are functions
    hasReturned = false;
    genNewScope = false;
    
    // Execute function body
    dets.funcBody->accept(this);

    // Assign last variables with return value and type
    lastType = dets.type;
    lastValue = returnValue;

    // Reset var
    hasReturned = false;
   
}

// Function Declaration Node
// Insert function into ST
// If has params, then modify entry in ST and insert them
void InterpreterVisitor::visit(ASTFuncDecl* node){

    //Insert function with block into ST
    Details funcDets = {node->type, {}, Function, "", node->block};
    st.insert(node->identifier->name, funcDets);

    node->identifier->accept(this);
    
    // Get params
    if(node->params != nullptr)
        node->params->accept(this);
    
    // If has params, assign param names to entry in ST
    if(!paramNames.empty()){
        Details withParams = st.lookup(node->identifier->name);
        withParams.parameters = paramNames;
        st.modify(node->identifier->name, withParams);
    }

    paramNames.clear();
}

// If Statement Node
void InterpreterVisitor::visit(ASTIfStmt* node){
   

    node->condition->accept(this);

    // If condition is true, go in first block, otherwise else block if any
    if(lastValue == "true"){
        node->trueBlock->accept(this);

    }else if(node->falseBlock != nullptr){
        node->falseBlock->accept(this);
    }
}

// Literal Node
void InterpreterVisitor::visit(ASTLiteral* node){
    // store type and value
    lastType = node->type;
    lastValue = node->value;
}

// Print Node
void InterpreterVisitor::visit(ASTPrint* node){
    // print value
    node->expression->accept(this);
    cout<< lastValue << endl;
}

// Return Node
void InterpreterVisitor::visit(ASTReturn* node){
    
    // If the function has not returned, access statement
    if(!hasReturned){
        node->expression->accept(this);

        returnValue = lastValue;

        hasReturned = true;
    }
}

// Unary Node
void InterpreterVisitor::visit(ASTUnary* node){
  
    node->expr->accept(this);

    // Compute unary operation
    if(lastType == "int"){
        int temp = stoi(lastValue);
        temp = -temp;
        lastValue = to_string(temp);
    }else if(lastType == "float"){
        float temp = stof(lastValue);
        temp = -temp;
        lastValue = to_string(temp);
    }else{
        if(lastValue == "true") lastValue = "false";
        else lastValue = "true";
    }
}

// While Node
void InterpreterVisitor::visit(ASTWhile* node){
   
    node->expression->accept(this);

    // While condition is true, keep looping
    while(lastValue == "true"){
        node->block->accept(this);

        // re-evaluate
        node->expression->accept(this);
    }
}
