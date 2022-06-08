#include "XMLVisitor.h"

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

using namespace std;

// void XMLVisitor::visit(ASTNode* node){

// }

XMLVisitor::XMLVisitor(){
    openFile();
    tagIndentation = 0;
}

void XMLVisitor::openFile(){
    xmlFile.open("ASTXML.txt");
}

void XMLVisitor::closeFile(){
    xmlFile.close();
}

void XMLVisitor::indent(){
    for(int i = 0; i < tagIndentation; i++){
        xmlFile << "\t";
    }
}

void XMLVisitor::visit(ASTProgram* node){
    xmlFile << "<Prog>" << endl;
    tagIndentation++;
    // indent();

    for(ASTNode* child: node->childNodes){
        indent();
        child->accept(this);
    }

    tagIndentation--;
    indent();
    xmlFile << "</Prog>" << endl;

    closeFile();
    
}

void XMLVisitor::visit(ASTVarDecl* node){
    xmlFile << "<VarDecl Type=\"" << node->type << "\">" << endl;
    tagIndentation++;
    indent();

    node->identifier->accept(this);
    indent();
    node->expression->accept(this);

    tagIndentation--;
    indent();
    xmlFile << "</VarDecl>" << endl;

}

void XMLVisitor::visit(ASTIdentifier* node){
    xmlFile << "<Id>";

    xmlFile << node->name;

    xmlFile << "</Id>" << endl;

}

void XMLVisitor::visit(ASTBinOp* node){
    xmlFile << "<BinaryOp Op=\"" << node->op << "\">" << endl;
    tagIndentation++;
    indent();

    node->leftChild->accept(this);
    indent();
    node->rightChild->accept(this);

    tagIndentation--;
    indent();
    xmlFile << "</BinaryOp>" << endl;

}

void XMLVisitor::visit(ASTActualParams* node){
    xmlFile << "<ActualParams>" << endl;
    tagIndentation++;
    

    for(ASTExpression* child: node->params){
        indent();
        child->accept(this);
    }

    tagIndentation--;
    indent();    

    xmlFile << "</ActualParams>" << endl;
}
void XMLVisitor::visit(ASTAssign* node){
    xmlFile << "<Assign>" << endl;
    tagIndentation++;
    indent();

    node->identifier->accept(this);
    indent();
    node->expression->accept(this);

    tagIndentation--;
    indent();
    xmlFile << "</Assign>" << endl;
}

void XMLVisitor::visit(ASTBlock* node){
    xmlFile << "<Block>" << endl;
    tagIndentation++;
    // indent();

    for(ASTNode* child: node->childNodes){
        indent();
        child->accept(this);
    }
    tagIndentation--;
    indent();    

    xmlFile << "</Block>" << endl;
}

// void XMLVisitor::visit(ASTExpression* node){

// }

void XMLVisitor::visit(ASTFormalParam* node){
    xmlFile << "<FormalParam Type=\"" << node->type << "\">" << endl;
    tagIndentation++;
    indent();

    node->identifier->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</FormalParam>" << endl;
}

void XMLVisitor::visit(ASTFormalParams* node){
    xmlFile << "<FormalParams>" << endl;
    tagIndentation++;
    // indent();

    for(ASTFormalParam* child: node->params){
        indent();
        child->accept(this);
    }    

    tagIndentation--;
    indent();

    xmlFile << "</FormalParams>" << endl;
}

void XMLVisitor::visit(ASTForStmt* node){
    xmlFile << "<For>" << endl;
    tagIndentation++;
    indent();

    node->varDecl->accept(this);
    indent();
    node->expression->accept(this);
    indent();
    node->assignment->accept(this);
    indent();
    node->block->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</For>" << endl;
}

void XMLVisitor::visit(ASTFuncCall* node){
    xmlFile << "<FuncCall>" << endl;
    tagIndentation++;
    indent();

    node->identifier->accept(this);
    indent();
    node->params->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</FuncCall>" << endl;
}

void XMLVisitor::visit(ASTFuncDecl* node){
    xmlFile << "<FuncDecl ReturnType=\"" << node->type << "\">" << endl;
    tagIndentation++;
    indent();

    node->identifier->accept(this);
    indent();
    node->params->accept(this);
    indent();
    node->block->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</FuncDecl>" << endl;
}

void XMLVisitor::visit(ASTIfStmt* node){
    xmlFile << "<If>" << endl;
    tagIndentation++;
    indent();

    node->condition->accept(this);
    indent();
    node->trueBlock->accept(this);
    if(node->falseBlock != nullptr){
        indent();
        node->falseBlock->accept(this);
    }

    tagIndentation--;
    indent();

    xmlFile << "</If>" << endl;
}

void XMLVisitor::visit(ASTLiteral* node){
    xmlFile << "<Literal Type=\"" << node->type << "\">";

    xmlFile << node->value;

    xmlFile << "</Literal>" << endl;
}

void XMLVisitor::visit(ASTPrint* node){
    xmlFile << "<Print>" << endl;
    tagIndentation++;
    indent();

    node->expression->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</Print>" << endl;
}

void XMLVisitor::visit(ASTReturn* node){
    xmlFile << "<Return>" << endl;
    tagIndentation++;
    indent();

    node->expression->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</Return>" << endl;
}

void XMLVisitor::visit(ASTUnary* node){
    xmlFile << "<Unary>" << endl;
    tagIndentation++;
    indent();

    node->expr->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</Unary>" << endl;
}

void XMLVisitor::visit(ASTWhile* node){
    xmlFile << "<While>" << endl;
    tagIndentation++;
    indent();

    node->expression->accept(this);
    indent();
    node->block->accept(this);

    tagIndentation--;
    indent();

    xmlFile << "</While>" << endl;
}
