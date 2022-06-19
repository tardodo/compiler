#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"
#include "Visitors/XMLVisitor.h"
#include "Visitors/SemanticVisitor.h"
#include "Visitors/InterpreterVisitor.h"

using namespace std;

int main() {

  // Open file, by default is test.txt
  if(openFile() == 1){
      cout << "FAILED TO OPEN" << endl;
      return 0;
  }
  
  // Create objects and pointers
  Parser parse;
  XMLVisitor* v = new XMLVisitor();
  SemanticVisitor* sv = new SemanticVisitor();
  InterpreterVisitor* iv = new InterpreterVisitor();

  // Begin 
  ASTNode* result = parse.program();

  // Check if returned valid AST
  if(result != nullptr){
    // XML Visitor
    result->accept(v);
    // Semantic Analysis
    result->accept(sv);
    // Interpreter 
    result->accept(iv);
  }

  return 0;
}