#include <iostream>                 // preprocessor directive
#include <string>                   // preprocessor directive
using namespace std;                // declaration statement
int main(int argc, char ** argv) {  // declaration statement (begin)
   if (argc != 2)                   // control-flow statement
   {                                // compound statement (begin)
      cout << "enter name" << endl; // expression statement
      return 1;                     // control-flow statement
   }                                // compound statement (end)
   std::string greeting = "Hail, "; // declaration statement
   greeting += argv[1];             // expression statement
   cout << greeting << endl;        // expression statement
   return 0;                        // control-flow statement
}                                   // declaration statement (end)
