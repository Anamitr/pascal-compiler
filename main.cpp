#include "global.h"

using namespace std;

int main(int argc, char** argv) {
    FILE *input = fopen(argv[1], "r");
    if(!input) {
        cout << "Provide valid input!";
        return -1;
    }
    yyin = input;
    yyparse();
    exit (0);
}