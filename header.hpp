#include <vector>
#include <string>

struct Token{
    std::string tType;
    std::string tVal;
};

std::vector<Token> lex(std::string fileName);
void compile(std::vector<Token> tokens, std::string fileOutputName);