#include "Comparisons.h"

bool Comparisons::isBracket(const char c) {
  if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']')
    return true;
  return false;
}

bool Comparisons::isDelim(const char c) {
  if (c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' ||
      c == '[' || c == ']')
    return true;
  return false;
}
bool Comparisons::isOp(const std::string str) {
  if (str == "+" || str == "-" || str == "*" || str == "/" || str == "=" ||
      str == "+=" || str == "-=" || str == "++" || str == "--")
    return true;
  return false;
}
bool Comparisons::isLogicalOp(const std::string str) {
  if (str == "!" || str == "!=" || str == "==" || str == "&&" || str == "||" ||
      str == "<" || str == "<=" || str == ">" || str == ">=")
    return true;
  return false;
}

bool Comparisons::isKeyword(const std::string str) {
  std::for_each(keywords.begin(), keywords.end(), [str](auto key) {
    if (key == str) {
      return true;
    }
  });
  return false;
}

bool Comparisons::isLiteral(const std::string str) {
  if (strIsBoolLiteral(str))
    return true;
  if (strIsNumericLiteral(str))
    return true;
  if (strIsStrLiteral(str))
    return true;
  return false;
}

bool Comparisons::strIsNumericLiteral(const std::string str) {
//iterates through a string, if any character is numeric 
  std::for_each(str.begin(), str.end(), [](auto c) {
    if (!isdigit(c)) {
      return false;
    }
  });
  return true;
}

bool Comparisons::strIsBoolLiteral(const std::string str) {
  if (str == "true" || str == "false")
    return true;
  return false;
}
bool Comparisons::strIsStrLiteral(const std::string str) {
    //slightly unhappy with this one, as including '\"" in a string breaks everything, but we'll see
  if (str[0] == '\"' && str.back() == '\"')
    return true;
  return false;
}