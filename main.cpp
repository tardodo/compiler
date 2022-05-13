#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lexer.h"
using namespace std;

int main() {
    string filename("test.txt");

    FILE* input_file = fopen(filename.c_str(), "r");
    if (input_file == nullptr) {
       return EXIT_FAILURE;
    }

    char c;
    while ((c = fgetc(input_file)) != EOF) {
       //putchar(c);
       cout << c;
    }
    cout << endl;
    fclose(input_file);

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