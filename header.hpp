// #ifndef zpp_header
// #define zpp_header
#include <vector>
#include <string>

// using namespace std;

struct Token{
    std::string tType;
    std::string tVal;
};

std::vector<Token> lex(std::string fileName);

// #endif