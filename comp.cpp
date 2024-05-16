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

    for (Token t: tokens) {
        cout << t.tType << ' ' << t.tVal << ' ';
    }
    cout << endl << "Output:" << endl << endl;

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
                    } else if (tokens[i].tType == "int") {
                        double sum = stoi(tokens[i].tVal);
                        while (true) {
                            if (canAdv(i, tokens.size())) {
                                i++;
                                if (tokens[i].tType == "math") {
                                    if (tokens[i].tVal == "plus") {
                                        if (canAdv(i, tokens.size())) {
                                            i++;
                                            if (tokens[i].tType == "int") {
                                                sum += stoi(tokens[i].tVal);
                                            } else {
                                                cout << "holup [4] - error while compiling: erm wtf cant put those two together..." << endl;
                                                exit(4);
                                            }
                                        } else {
                                            cout << "holup [3] - error while compiling: bro tried to yap math" << endl;
                                            exit(3);
                                        }
                                    } else if (tokens[i].tVal == "minus") {
                                        if (canAdv(i, tokens.size())) {
                                            i++;
                                            if (tokens[i].tType == "int") {
                                                sum -= stoi(tokens[i].tVal);
                                            } else {
                                                cout << "holup [4] - error while compiling: erm wtf cant put those two together..." << endl;
                                                exit(4);
                                            }
                                        } else {
                                            cout << "holup [3] - error while compiling: bro tried to yap math" << endl;
                                            exit(3);
                                        }
                                    } else if (tokens[i].tVal == "multi") {
                                        if (canAdv(i, tokens.size())) {
                                            i++;
                                            if (tokens[i].tType == "int") {
                                                sum *= stoi(tokens[i].tVal);
                                            } else {
                                                cout << "holup [4] - error while compiling: erm wtf cant put those two together..." << endl;
                                                exit(4);
                                            }
                                        } else {
                                            cout << "holup [3] - error while compiling: bro tried to yap math" << endl;
                                            exit(3);
                                        }
                                    } else if (tokens[i].tVal == "divi") {
                                        if (canAdv(i, tokens.size())) {
                                            i++;
                                            if (tokens[i].tType == "int") {
                                                sum = sum /  stoi(tokens[i].tVal);
                                                cout << 4 / 8 << endl;
                                            } else {
                                                cout << "holup [4] - error while compiling: erm wtf cant put those two together..." << endl;
                                                exit(4);
                                            }
                                        } else {
                                            cout << "holup [3] - error while compiling: bro tried to yap math" << endl;
                                            exit(3);
                                        }
                                    } else {
                                        break;
                                    }
                                } else {
                                    cout << "holup [2] - error while compiling: number and what bro?" << endl;
                                    exit(2);
                                }
                            } else {
                                break;
                            }
                        }

                        text += "mov edx, len" + to_string(strIdx)+ "\nmov ecx, jklZmmVariableIndex" + to_string(strIdx) + "\nmov ebx, 1\nmov eax, 4\nint 0x80\n";
                        data += "jklZmmVariableIndex" + to_string(strIdx) + " db '" + to_string(sum) + "', 0xa\nlen" + to_string(strIdx) + " equ $ - jklZmmVariableIndex" + to_string(strIdx) + "\n";
                        strIdx++;
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
    system("nasm -felf64 zmmOut.asm -o zmmOut.o");
    system(("ld zmmOut.o -o \"" + fileOut + "\"").c_str());

    remove("zmmOut.asm");
    remove("zmmOut.o");

    return 0;
}