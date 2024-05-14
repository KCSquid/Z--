#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "header.hpp"

using namespace std;

bool canAdv(int i, int s) {
    if (i+1 == s) {
        return false;
    } else return true;
}

int main(int argc, char* argv[]) {
    string fileName;
    string fileOut;
    if (argc > 3) {
        string arg1 = argv[1];
        if (arg1 == "-f") {
            fileName = argv[2];
        } else if (arg1 == "-o") {
            fileOut = argv[2];
        }

        string arg3 = argv[3];
        if (arg3 == "-f") {
            fileName = argv[4];
        } else if (arg3 == "-o") {
            fileOut = argv[4];
        }
    } else {
        exit(1);
    }

    
    vector<Token> tokens = lex(fileName);

    string start = "section .text\nglobal _start\n";
    string data = "section .data\n";
    string text = "section .text\n_start:\n";
    string end = "mov ebx,0\nmov eax,1\nint 0x80";

    int strIdx = 0;

    // for (Token t: tokens) {
    //     cout << t.tType << ' ' << t.tVal << ' ';
    // }
    // cout << endl;

    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].tType == "func") {
            if (tokens[i].tVal == "yap") {
                if (canAdv(i, tokens.size())) {
                    i++;
                    if (tokens[i].tType == "string") {
                        text += "mov edx, len" + to_string(strIdx)+ "\nmov ecx, jklZmmVariableIndex" + to_string(strIdx) + "\nmov ebx, 1\nmov eax, 4\nint 0x80\n";
                        data += "jklZmmVariableIndex" + to_string(strIdx) + " db '" + tokens[i].tVal + "', 0xa\nlen" + to_string(strIdx) + " equ $ - jklZmmVariableIndex" + to_string(strIdx) + "\n";
                        strIdx++;
                        continue;
                    }
                } else {
                    cout << "holup [1] - error while compiling: can't yap allat" << endl;
                    exit(1);
                }
            }
        }
    }

    ofstream zmmOut("zmmOut.asm");
    zmmOut << start + data + text + end;
    zmmOut.close();
    system("nasm -felf32 -g -Fdwarf zmmOut.asm -o zmmOut.o");
    system(("ld -m elf_i386 -s -o " + fileOut + " zmmOut.o").c_str());

    remove("zmmOut.asm");
    remove("zmmOut.o");

    return 0;
}