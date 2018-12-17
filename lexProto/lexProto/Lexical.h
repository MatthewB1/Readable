#include "Token.h"
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

namespace Lexical {

std::vector<Token *> tokenise(const std::vector<char> &chars);


bool bracketsBalanced(const std::vector<char> &chars);
std::vector<std::string> hoistIdentifiers(const std::vector<char> &chars);

void print(const std::string arg);
void printBracketError(std::stack<std::pair<std::string, char>> &stack);
void printBracketError(const int l, const int cp, const char delim);

bool isBracket(const char c);
bool isDelim(const char c);
bool isOp(const std::string str);
bool isLogicalOp(const std::string str);
bool isKeyword(const std::string str);
/*
 this function needs to keep track of all function and variable names in the
 program this process will be done as part of the scan prior to tokenisation,
 to check for valid syntax
 */
bool isIdentifier(const std::string str);

} // namespace Lexical