#include <iostream>
#include <string>
#include <vector>
// #include "lexer.h"
#include "Parser.h"
using namespace std;

int main() {
    // string filename("test.txt");

    // FILE* input_file = fopen(filename.c_str(), "r");
    // if (input_file == nullptr) {
    //    return EXIT_FAILURE;
    // }

    if(openFile() == 1){
        cout << "FAILED TO OPEN" << endl;
        return 0;
    }

    string tokenNames[37] = {"identifier", "intReserve", "floatReserve", "boolReserve", "charReserve", "boolLit", "fnReserve", "trueReserve", "falseReserve", "ifReserve", "elseReserve", "whileReserve", "forReserve", "returnReserve", "printReserve", "letReserve",  "intLit", "floatLit", "charLit", "multOp", "addOp", "relOp", "notReserve", "tokCurlyOpen", "tokCurlyClose", "tokBracketOpen", "tokBracketClose", "tokColon", "tokSemicolon", "tokComma", "andReserve", "orReserve", "tokEquals", "arrow", "other", "endOfFile", "invalid"};

    

    Token val;
    // Token endFile;
    // endFile.tok = 4;
    // endFile.data = -1;

    // val = nextWord();
    // cout << val << endl;
    
    Parser parse;

    bool result = parse.program();

    cout << result << endl;

    // do{
    //     val = parse.getNextToken();
    //     if(val.tok == -1){
    //         cout << "encountered error, invalid lexeme" << endl;
    //         return -1;
    //     }
    //     cout<< tokenNames[val.tok] << "," << val.data << endl;
        
    // }while(val.tok != tokEndOfFile);
    
    // do{
    //     val = nextWord();
    //     if(val.tok == -1){
    //         cout << "encountered error, invalid lexeme" << endl;
    //         return -1;
    //     }
    //     cout<< tokenNames[val.tok] << "," << val.data << endl;
        
    // }while(val.tok != tokEndOfFile);

    // while((val = nextWord()) != endFile){
    //     cout<< val.tok << "," << val.data << endl;
    // }

    // char c;
    // while ((c = fgetc(input_file)) != EOF) {
    //    //putchar(c);
    //    cout << c;
    // }
    // cout << endl;
    closeFile();

//   string line;
//   ifstream myfile ("test.txt");
//   if (myfile.is_open())
//   {
//     while ( getline (myfile,line) )
//     {
//       cout << line << '\n';
//     }
//     myfile.close();
//   }

//   else cout << "Unable to open file"; 

  return 0;
}