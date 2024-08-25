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
            intState = false;
            continue;
        }

        if (c == '\n') {
            intState = false;
            Token t;
            t.tType = "char";
            t.tVal = "newline";
            tokens.push_back(t);
            token = "";
            continue;
        }

        token += c;

        if (token == "+") {
            intState = false;
            Token t;
            t.tType = "math";
            t.tVal = "plus";
            tokens.push_back(t);
            token = "";
            continue;
        }

        else if (token == "-") {
            intState = false;
            Token t;
            t.tType = "math";
            t.tVal = "minus";
            tokens.push_back(t);
            token = "";
            continue;
        }

        else if (token == "*") {
            intState = false;
            Token t;
            t.tType = "math";
            t.tVal = "multi";
            tokens.push_back(t);
            token = "";
            continue;
        }

        else if (token == "/") {
            intState = false;
            Token t;
            t.tType = "math";
            t.tVal = "divi";
            tokens.push_back(t);
            token = "";
            continue;
        }

        if (token == "erm") {
            Token t;
            t.tType = "func";
            t.tVal = "erm";
            tokens.push_back(t);
            token = "";
        }

        else if (token == "yap") {
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

        else if (isdigit(c)) {
            if (intState) {
                num += c;
                if (!isdigit(file.peek())) {
                    intState = false;
                }
            } else {
                num += c;
                if (isdigit(file.peek())) {
                    intState = true;
                }
            }
            
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


        if (num.length() > 0 && intState == false) {
            Token t;
            t.tType = "int";
            t.tVal = num;
            tokens.push_back(t);
            token = "";
            num = "";
        }
    }

    return tokens;
}