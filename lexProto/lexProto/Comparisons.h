#include "Token.h"
#include <cctype>
#include <algorithm>

namespace Comparisons {
bool isBracket(const char c);
bool isDelim(const char c);
bool isOp(const std::string str);
bool isLogicalOp(const std::string str);
bool isKeyword(const std::string str);
bool isLiteral(const std::string str);
bool isNumeric(const std::string str);
bool strIsBoolLiteral(const std::string str);
bool strIsNumericLiteral(const std::string str);
bool strIsStrLiteral(const std::string str);
bool isIdentifier(const std::string str);

const std::vector<std::string> keywords = {"var", "while", "if",
                                           "return", "flip",  "function"};
} // namespace Comparisons