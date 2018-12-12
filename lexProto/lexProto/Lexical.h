#include "Token.h"
#include <iostream>
#include <vector>

namespace Lexical {

std::vector<Token *> tokenise(const std::vector<char> &chars);

void preScan(const std::vector<char> &chars);

void print(const std::string arg);

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
/*
for this function I need to implement an algorithm to check for balanced
brackets, I've seen a good implementation online that I referenced as a part of
my information review, so will likely implement that
*/
bool bracketsBalanced(const std::vector<char> &chars);

} // namespace Lexical