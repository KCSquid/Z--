#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Token {
    string tType;
    string tVal;
};

vector<Token> lex(string fileName) {
    string token;
    vector<Token> tokens;

    bool strState, intState;
    string str, num;

    char c;
    fstream file(fileName, fstream::in);
    while (file.get(c)) {
        if (c == ' ' && !strState) {
            continue;
        }

        if (c == '\n') {
            Token t;
            t.tType = "char";
            t.tVal = "newline";
            tokens.push_back(t);
            token = "";
            continue;
        }

        token += c;

        if (token == "yap") {
            Token t;
            t.tType = "func";
            t.tVal = "yap";
            tokens.push_back(t);
            token = "";
        }

        if (c == '"') {
            if (strState == true) {
                strState = false;
            } else {
                strState = true;
            }
            token = "";
        }

        else if (strState == true) {
            str += c;
            token = "";
        }

        if (str.length() > 0 && strState == false) {
            Token t;
            t.tType = "string";
            t.tVal = str;
            tokens.push_back(t);
            token = "";
            str = "";
        }
    }

    return tokens;
}