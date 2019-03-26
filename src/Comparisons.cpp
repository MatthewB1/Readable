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
      str == "+=" || str == "-=" || str == "*=" || str == "/=" || str == "++" ||
      str == "--")
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
  //checks if the string can be found in the vector of keywords
  //defined in the Comparisons namespace
  if (std::find(Comparisons::keywords.begin(), Comparisons::keywords.end(),
                str) != Comparisons::keywords.end()) {return true;}
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
//iterates through a string, if any character is not numeric, return false
  for (char c : str){
    if (!isdigit(c))
      return false;
  }
  return true;
}

bool Comparisons::strIsBoolLiteral(const std::string str) {
  //true and false are valid boolean values, anything else is not
  if (str == "true" || str == "false")
    return true;
  return false;
}
bool Comparisons::strIsStrLiteral(const std::string str) {
  if (str[0] == '\"' && str.back() == '\"')
    return true;
  return false;
}

bool Comparisons::isIdentifier(const std::string str) {
  /*
  following (most of) the c++ rules on identifier naming:

  1. Only Alphabets,Digits and Underscores are permitted.
  2. Identifier name cannot start with a digit.
  3. Key words cannot be used as a name.
  4. Upper case and lower case letters are distinct.
  */

  // keywords cannot be used as identifier
  if (isKeyword(str)) {
    return false;
  }

//true or false cannot be used as identifier names
  if (strIsBoolLiteral(str)){
    return false;
  }

  // if the first character is a digit, it's not a valid identifier
  if (isdigit(str[0]))
    return false;

  for (auto c : str) {
    //if a character is NOT, an underscore, digit, or alphabet character
    //then it is not a valid identifier
    if (!(int(c) == 95 || (int(c) >= 48 && int(c) <= 57) ||
          (tolower(c) >= 97 && tolower(c) <= 122)))
      return false;
  }

//if it passes these tests, it's a valid syntactically identifier
  return true;
}

bool Comparisons::isUnfString(const std::string str) {
  //if a string begins with a '"', but doesn't end with one
  //then it is an unfinished string
  if (str[0] == '\"' && str[str.size() - 1] != '\"')
    return true;
  return false;
}