#include <iostream>
#include <string>
#include <vector>
#include "header.hpp"

using namespace std;

void outputTokens(vector<Token> tokens) {
    for (Token t: tokens) {
        cout << t.tType << ' ' << t.tVal << ' ';
    }

    cout << endl << endl;
}

int main(int argc, char* argv[]) {
    string fileName;
    string fileOut;
    
    string arg1 = argv[1];

    if (arg1 == "-h" || arg1 == "-help") {
        cout << "To compile using Z--, please specify the file & the output.\n\nUsage:\nzmm -f <file.zmm> -o <outputName>\n\nYou may also replace -f with -file, -o with -out & -h with -help" << endl;
        exit(0);
    } else if (argc > 3) {
        string arg3 = argv[3];

        if (arg1 == "-f" || arg1 == "-file") {
            fileName = argv[2];
        } else if (arg1 == "-o" || arg1 == "-out") {
            fileOut = argv[2];
        } else {
            cout << "holup [6] - error on startup: that argument doesn't exist man... use zmm -help / -h for possible commands" << endl;
            exit(6);
        }

        if (arg3 == "-f" || arg3 == "-file") {
            fileName = argv[4];
        } else if (arg3 == "-o" || arg3 == "-out") {
            fileOut = argv[4];
        } else {
            cout << "holup [6] - error on startup: that argument doesn't exist man... use zmm -help / -h for possible commands" << endl;
            exit(6);
        }
    } else {
        cout << "holup [7] - error on startup: file or output?" << endl;
        exit(7);
    }

    vector<Token> tokens = lex(fileName);
    // outputTokens(tokens);
    compile(tokens, fileOut);

    return 0;
}