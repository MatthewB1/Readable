#include "Lexical.h"

#define current_char chars[i]
#define prev_char chars[i-1]
#define newLine current_char == '\n'
#define space current_char == ' '

std::vector<Token *> Lexical::tokenise(const std::vector<char> &chars) {
  // pre scan should do a run through to check for syntactical issues

//hoistIdentifiers(chars);
  bracketsBalanced(chars);

  /*if pre scan didn't cause the program to exit, we can assume the code
    is syntactically valid, and can tokenise it*/

  int line_no = 1;
  int char_pos = 1;
  std::vector<Token *> tokens;
  std::string current_str = "";

  // each time we iterate through, also increment char_pos
  for (auto i = 0; i < chars.size(); i++, char_pos++) {
    char currentchar = current_char;

    if (isDelim(current_char)) {
      tokens.push_back(new Token(delim, std::string(1, current_char), line_no, char_pos));
      current_str.clear();
      continue;
    }
    if (newLine) {
      line_no++;
      char_pos = 0;
      continue;
    }
    if (space) {
      //if previous character was also a space, we don't need to run the rest of the logic
      if (current_str != "") {
        // should be end of token, we should do checks and create the new token
        if (isKeyword(current_str)){
          tokens.push_back(new Token(keyword, current_str, line_no, char_pos));
          current_str.clear();
          continue;
        }
        if (isOp(current_str)){
          tokens.push_back(new Token(op, current_str, line_no, char_pos));
          current_str.clear();
          continue;
        }
        if (isLogicalOp(current_str)) {
          tokens.push_back(new Token(logical_op, current_str, line_no, char_pos));
          current_str.clear();
          continue;
        }
        /*
        at this stage I need to distinguish between literals and identifiers
        I should be able to do this by looking at the last token
        might not have to, because if it isn't identifier it has to be a literal
        and if it is non-numeric, not true/false and not surrounded by ""
        it is a identifier?
        then we need to check if it's a valid identifier
        */
      }
      current_str.clear();
      continue;
    }
    // if nothing else, add char to the current string
    current_str += current_char;
  }

  return tokens;
}

std::vector<std::string> Lexical::hoistIdentifiers(const std::vector<char> &chars){
  //run through code to find valid references to identifiers
  //would it make sense to do this beforehand?
  //could potentially do it after.

}

#define openPeren '('
#define closePeren ')'
#define openBrace '{'
#define closeBrace '}'
#define openSquare '['
#define closeSquare ']'
#define doubleQuote '\"'
#define singleQuote '\'

    bool Lexical::bracketsBalanced(const std::vector<char> &chars) {
  //TODO extend for other delims " and ' (easy to do, but check for escape characters)
  int line_no = 0;
  int char_pos = 0;
  std::stack<std::pair<std::string, char>> stack;

  for (int i = 0; i < chars.size(); i++, char_pos++) {
    char currentchar = current_char;
    // if it's not a bracket, we ignore it
    if (newLine) {
      line_no++;
      char_pos = 0;
      continue;
    }
    if (isBracket(current_char)) {
      if (current_char == openPeren || current_char == openBrace ||current_char == openSquare) {
        stack.push(std::pair<std::string, char>(std::string(std::to_string(line_no) + "," + std::to_string(char_pos)), current_char));
      } else {
        // check top of stack for corresponding opening bracket
        switch (current_char) {

        case closePeren:
          if (stack.size() > 0 && stack.top().second == openPeren)
            stack.pop();
          else
            printBracketError(line_no, char_pos, current_char);
          break;

        case closeBrace:
          if (stack.size() > 0 && stack.top().second == openBrace)
            stack.pop();
          else
            printBracketError(line_no, char_pos, current_char);
          break;

        case closeSquare:
          if (stack.size() > 0 && stack.top().second == openSquare)
            stack.pop();
          else
            printBracketError(line_no, char_pos, current_char);
          break;
        }
      }
    }
  }

  if (stack.size() > 0) {
    printBracketError(stack);
  }
}

void Lexical::printBracketError(
    std::stack<std::pair<std::string, char>> &stack) {
  // reduce stack to first added bracket, only printing first error
  while (stack.size() > 1) {
    stack.pop();
  }
  //stack.top().first not currently working, might change to a struct rather than pair
  //not actually sure it's storing it
  std::cout << "\n***Error at " << stack.top().first << "\nReason: '"
            << stack.top().second
            << "' has no corresponding closer\nExiting program...";
  exit(0);
}

void Lexical::printBracketError(const int l, const int cp, const char delim) {
  std::cout << "\n***Error at " << l << "," << cp << "\nReason: '" << delim
            << "' had no corresponding opener to close\nExiting program...";
  exit(0);
}

void Lexical::print(const std::string arg) { std::cout << arg; }

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
                                //if previous character is not escape
character if (chars[i - 1] != '\\') {
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