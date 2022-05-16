#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"
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

    Token val;
    // Token endFile;
    // endFile.tok = 4;
    // endFile.data = -1;

    // val = nextWord();
    // cout << val << endl;

    do{
        val = nextWord();
        cout<< val.tok << "," << val.data << endl;

    }while(val.tok != endOfFile);

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