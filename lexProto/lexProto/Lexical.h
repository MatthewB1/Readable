#include "Comparisons.h"
#include <iostream>
#include <stack>
#include <utility>

namespace Lexical {

std::vector<Token *> tokenise(const std::vector<char> &chars);


bool bracketsBalanced(const std::vector<char> &chars);
void checkIdentifierValidity(const std::vector<Token *> &tokens);

void printBracketError(std::stack<std::pair<std::string, char>> &stack);
void printBracketError(const int l, const int cp, const char delim);
void printTokenisationError(const std::string str, const int line_no, const int char_pos);

LiteralToken* createLiteralToken(const std::string str, const int line_no, const int char_pos);
LiteralToken* createBoolLiteralToken(const std::string str, const int line_no, const int char_pos);
LiteralToken* createNumericLiteralToken(const std::string str, const int line_no, const int char_pos);
LiteralToken* createStrLiteralToken(const std::string str, const int line_no, const int char_pos);

IdentifierToken* createIdentifierToken(const std::string str, const int line_no, const int char_pos);
} // namespace Lexical