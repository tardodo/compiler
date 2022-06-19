#!/bin/bash

g++ -Wall -ggdb main.cpp lexer.cpp Parser.cpp ./Visitors/XMLVisitor.cpp ./Visitors/SemanticVisitor.cpp ./Visitors/InterpreterVisitor.cpp SymbolTable.cpp -o main