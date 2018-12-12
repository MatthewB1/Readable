#include "Lexical.h"

#define current_char chars[i]
#define newLine current_char == '\n'
#define space current_char == ' '

std::vector<Token *> Lexical::tokenise(const std::vector<char> &chars) {
  // pre scan should do a run through to check for syntactical issues
  preScan(chars);
  /*assuming preScan() didn't cause the program to exit, we can assume the code
    is syntactically valid, and can tokenise it*/

  int line_no = 1;
  int char_pos = 1;
  std::vector<Token *> tokens;
  std::string current_str = "";

  // each time we iterate through, also increment char_pos
  for (auto i = 0; i < chars.size(); i++, char_pos++) {
    char currentchar = current_char;

    if (isDelim(current_char)) {
      // create token from current_str
      // could be identifier or literal
      tokens.push_back(
          new Token(delim, std::string(1, current_char), line_no, char_pos));
      current_str = "";
      continue;
    }
    if (newLine) {
      line_no++;
      char_pos = 0;
      continue;
    }
    if (space) {
      if (current_str == "") {
        // do nothing
      } else {
        // should be end of token, we should do checks and create the new token
        current_str = "";
      }
      continue;
    }
    // if nothing else, add char to the current string
    current_str += current_char;
  }

  return tokens;
}

void Lexical::preScan(const std::vector<char> &chars) {
  if (!bracketsBalanced(chars)) {
    std::cout << "\n Brackets were not balanced! Check log for more "
                 "info\nExiting program....";
    exit(0);
  }
  // then check for valid reference to identifiers?
  // not sure how to go about doing this yet
  // TODO ask chris
}

bool Lexical::bracketsBalanced(const std::vector<char> &chars) {
  // implement algorithm from codeschool video
  return true;
}

bool Lexical::isBracket(const char c) {
  if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']')
    return true;
  return false;
}

bool Lexical::isDelim(const char c) {
  if (c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' ||
      c == '[' || c == ']')
    return true;
  return false;
}
bool Lexical::isOp(const std::string str) {
  if (str == "+" || str == "-" || str == "*" || str == "/" || str == "=" ||
      str == "+=" || str == "-=" || str == "++" || str == "--")
    return true;
  return false;
}
bool Lexical::isLogicalOp(const std::string str) {
  if (str == "!" || str == "!=" || str == "==" || str == "&&" || str == "||" ||
      str == "<" || str == "<=" || str == ">" || str == ">=")
    return true;
  return false;
}

bool Lexical::isKeyword(const std::string str) {
  if (str == "var" || str == "while" || str == "if" || str == "return" ||
      str == "flip" || str == "function")
    return true;
  return false;
}
/*
std::vector<Token> tokens;

                std::string token("");

                //iterate through characters, creating the tokens, in order
                //for now, grammar enforces corret whitespacing
                //i.e  "x = x + 7;" is valid, "x=x+7;" is not
                for (size_t i = 0; i < chars.size(); i++)
                {
                        //if end of file,break, we're done tokenising
                        if (chars[i] == EOF)
                                break;
                        //if we are not currently inside of a string
                        if (token[0] != '\"') {
                                //if character is semi colon or new line, push
the current token, and a new one for this character if (chars[i] == ';' ||
chars[i] == '\n') { tokens.push_back(token); tokens.push_back(std::string(1,
chars[i])); token.clear(); continue;
                                }
                                //if the character is a space, as we are
enforcing whitespace, this is the end of this token
                                //push the token onto the vector, and clear it
to start again if (chars[i] == ' ') { tokens.push_back(token); token.clear();
                                        continue;
                                }
                                //else, add character to token
                                token += chars[i];
                                continue;
                        }
                        //if we are inside of a string
                        else {
                                //if previous character is not escape character
                                if (chars[i - 1] != '\\') {
                                        //if second non escape character '"',
string is over, create the token and clear it if (chars[i] == '\"') { token +=
chars[i]; tokens.push_back(token); token.clear(); continue;
                                        }
                                }
                                //else, add character to token
                                token += chars[i];
                                continue;
                        }
                }

                return tokens;



        */