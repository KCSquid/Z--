#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "header.hpp"

using namespace std;

bool canAdvance(int i, int s) {
    if (i+1 == s) {
        return false;
    } else return true;
}

void compile(vector<Token> tokens, string fileOutputName) {
    string start = "SYS_WRITE    equ 4 ; write text to stdout\nSYS_READ     equ 3 ; read text from stdin\nSYS_EXIT     equ 1 ; terminate the program\nSYS_FORK     equ 2\n";
    string data = "\nsection .data\n";
    string bss = "\nsection .bss\n";
    string text = "\n\nsection .text\n     global _start\n\n_start:\n";
    string end = "     mov eax, SYS_EXIT\n     mov ebx, 0\n     int 0x80\n";

    int strIdx, bssIdx = 0;

    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].tType == "func") {
            if (tokens[i].tVal == "yap") {
                if (canAdvance(i, tokens.size())) {
                    i++;
                    if (tokens[i].tType == "string") {
                        text += "     mov edx, len" + to_string(strIdx)+ "\n     mov ecx, jklZmmVariableIndex" + to_string(strIdx) + "\n     mov ebx, 1\n     mov eax, SYS_WRITE\n     int 0x80\n\n";
                        data += "     jklZmmVariableIndex" + to_string(strIdx) + " db '" + tokens[i].tVal + "', 0xa\n     len" + to_string(strIdx) + " equ $ - jklZmmVariableIndex" + to_string(strIdx) + "\n";
                        strIdx++;
                        continue;
                    } else if (tokens[i].tType == "int") {
                        double sum = stoi(tokens[i].tVal);
                        while (true) {
                            if (canAdvance(i, tokens.size())) {
                                i++;
                                if (tokens[i].tType == "math") {
                                    if (tokens[i].tVal == "plus") {
                                        if (canAdvance(i, tokens.size())) {
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
                                        if (canAdvance(i, tokens.size())) {
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
                                        if (canAdvance(i, tokens.size())) {
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
                                        if (canAdvance(i, tokens.size())) {
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

                        text += "     mov edx, len" + to_string(strIdx)+ "\n     mov ecx, jklZmmVariableIndex" + to_string(strIdx) + "\n     mov ebx, 1\n     mov eax, SYS_WRITE\n     int 0x80\n\n";
                        data += "     jklZmmVariableIndex" + to_string(strIdx) + " db '" + to_string(sum) + "', 0xa\n     len" + to_string(strIdx) + " equ $ - jklZmmVariableIndex" + to_string(strIdx) + "\n";
                        strIdx++;
                    }
                } else {
                    cout << "holup [1] - error while compiling: can't yap allat" << endl;
                    exit(1);
                }
            } else if (tokens[i].tVal == "erm") {
                if (canAdvance(i, tokens.size())) {
                    i++;
                    if (tokens[i].tType == "string") {
                        // length of question
                        bss += "     jklZmmVariableIndexBss" + to_string(bssIdx) + " resb 1024\n";
                        bss += "     jklZmmVariableIndexBss" + to_string(bssIdx) + "len equ $ - jklZmmVariableIndexBss" + to_string(bssIdx);

                        // message to output
                        data += "     jklZmmVariableIndex" + to_string(strIdx) + " db '" + tokens[i].tVal + "'\n     len" + to_string(strIdx) + " equ $ - jklZmmVariableIndex" + to_string(strIdx) + "\n";

                        // output message
                        text += "     mov edx, len" + to_string(strIdx)+ "\n     mov ecx, jklZmmVariableIndex" + to_string(strIdx) + "\n     mov ebx, 1\n     mov eax, SYS_WRITE\n     int 0x80\n\n";
                        strIdx++;

                        // store input
                        text += "     mov eax, SYS_READ\n     mov ebx, SYS_FORK\n     mov ecx, jklZmmVariableIndexBss" + to_string(bssIdx) + "\n     mov edx, 1024\n     int 0x80\n\n";
                        bssIdx++;
                    } else {
                        cout << "holup [1] - error while compiling: can't yap allat" << endl;
                        exit(1);
                    }

                    continue;
                }
            }
        }
    }

    ofstream zmmOut("zmmOut.asm");
    zmmOut << start + data + bss + text + end;
    zmmOut.close();
    system("nasm -felf64 zmmOut.asm -o zmmOut.o");
    system(("ld zmmOut.o -o \"" + fileOutputName + "\"").c_str());

    // remove("zmmOut.asm");
    remove("zmmOut.o");
}
