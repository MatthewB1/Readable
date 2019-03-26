#include "Lexical.h"

#define current_char chars[i]
#define prev_char chars[i - 1]
#define newLine current_char == '\n'
#define space current_char == ' '

std::vector<std::shared_ptr<Token>>
Lexical::tokenise(const std::vector<char> &chars) {
  // pre scan should do a run through to check for syntactical issues

  // if brackets balanced encounters an issue
  // it prints a meaningful error essage and returns
  // if false, exit program
  if (!bracketsBalanced(chars))
    exit(0);

  /*if pre scan didn't cause the program to exit, we can assume the code
    is syntactically valid, and can tokenise it*/

  int line_no = 1;
  int char_pos = 1;
  std::vector<std::shared_ptr<Token>> tokens;
  std::string current_str = "";

  // each time we iterate through, also increment char_pos
  for (auto i = 0; i < chars.size(); i++, char_pos++) {
    if (newLine) {
      // if there is untokenised code when starting a new line
      // print error and exit program
      if (current_str != "") {
        printTokenisationError(current_str, line_no,
                               char_pos - current_str.size());
        exit(0);
      }
      line_no++;
      char_pos = 0;
      current_str.clear();
      continue;
    }

    if (space || (Comparisons::isDelim(current_char) && prev_char != '\\')) {
      if (!Comparisons::isUnfString(current_str)) {
        // if previous character was also a space, we don't need to run the rest
        // of the logic
        if (current_str != "") {
          // should be end of token, we should do checks and create the new
          // token
          if (Comparisons::isKeyword(current_str)) {
            tokens.emplace_back(new Token(keyword, current_str, line_no,
                                          char_pos - current_str.size()));
            current_str.clear();
          } else if (Comparisons::isOp(current_str)) {
            tokens.emplace_back(new Token(op, current_str, line_no,
                                          char_pos - current_str.size()));
            current_str.clear();
          } else if (Comparisons::isLogicalOp(current_str)) {
            tokens.emplace_back(new Token(logical_op, current_str, line_no,
                                          char_pos - current_str.size()));
            current_str.clear();
          } else if (Comparisons::isLiteral(current_str)) {
            tokens.emplace_back(createLiteralToken(
                current_str, line_no, char_pos - current_str.size()));
            current_str.clear();
          } else if (Comparisons::isIdentifier(current_str)) {
            tokens.emplace_back(createIdentifierToken(
                current_str, line_no, char_pos - current_str.size()));
            current_str.clear();
          }
          // if nothing else picks it up, it's an invalid token
          // print the error and exit the program
          else {
            printTokenisationError(current_str, line_no,
                                   char_pos - -current_str.size());
            exit(0);
          }
        }
        if (Comparisons::isDelim(current_char) && prev_char != '\\') {
          tokens.emplace_back(new Token(delim, std::string(1, current_char),
                                        line_no, char_pos));
        }
        current_str.clear();
        continue;
      }
    }
    // if nothing else, add char to the current string
    current_str += current_char;
  }

  // after tokenisation, do checks for valid references to identifiers
  checkIdentifierValidity(tokens);

  return tokens;
}

void Lexical::printTokenisationError(const std::string str, const int line_no,
                                     const int char_pos) {
  std::cout << "\n***Error at " << line_no << "," << char_pos << "\n"
            << "Reason: Error trying to tokenise " << str
            << "\nExiting program... ";
}

#define openPeren '('
#define closePeren ')'
#define openBrace '{'
#define closeBrace '}'
#define openSquare '['
#define closeSquare ']'

bool Lexical::bracketsBalanced(const std::vector<char> &chars) {
  int line_no = 1;
  int char_pos = 1;
  std::stack<std::pair<std::string, char>> stack;

  for (int i = 0; i < chars.size(); i++, char_pos++) {
    char currentchar = current_char;
    // if it's not a bracket, we ignore it
    if (newLine) {
      line_no++;
      char_pos = 0;
      continue;
    }
    if (Comparisons::isBracket(current_char)) {
      if (current_char == openPeren || current_char == openBrace ||
          current_char == openSquare) {
        stack.push(std::pair<std::string, char>(
            std::string(std::to_string(line_no) + "," +
                        std::to_string(char_pos)),
            current_char));
      } else {
        // check top of stack for corresponding opening bracket
        if (prev_char != '\\') {
          switch (current_char) {

          case closePeren:
            if (stack.size() > 0 && stack.top().second == openPeren)
              stack.pop();
            else {
              printBracketError(line_no, char_pos, current_char);
              return false;
            }
            break;

          case closeBrace:
            if (stack.size() > 0 && stack.top().second == openBrace)
              stack.pop();
            else {
              printBracketError(line_no, char_pos, current_char);
              return false;
            }
            break;

          case closeSquare:
            if (stack.size() > 0 && stack.top().second == openSquare)
              stack.pop();
            else {
              printBracketError(line_no, char_pos, current_char);
              return false;
            }
            break;
          }
        }
      }
    }
  }

  // if anything remains in stack
  // brackets were not balanced
  if (stack.size() > 0) {
    printBracketError(stack);
    return false;
  }
  return true;
}

void Lexical::printBracketError(
    std::stack<std::pair<std::string, char>> &stack) {
  // reduce stack to first added bracket, only printing first error
  while (stack.size() > 1) {
    stack.pop();
  }
  std::cout << "\n***Error at " << stack.top().first << "\n"
            << "Reason: '" << stack.top().second
            << "' has no corresponding closer\nExiting program...";
}

void Lexical::printBracketError(const int line_no, const int char_pos,
                                const char delim) {
  std::cout << "\n***Error at " << line_no << "," << char_pos << "\nReason: '"
            << delim
            << "' does not match last opening delimiter...\nExiting program...";
}

#define current_token tokens[i].get()
#define previous_token tokens[i - 1].get()

void Lexical::checkIdentifierValidity(
    const std::vector<std::shared_ptr<Token>> &tokens) {
  std::vector<std::shared_ptr<Token>> validIdentifiers;
  for (int i = 0; i < tokens.size(); i++) {
    Token *currenttoken = current_token;
    // only running logic on identifier tokens
    if (current_token->getTokenType() == identifier) {
      // if token is preceded by keyword "var" or "function" it is a decleration
      if (previous_token->getVal() == "var" ||
          previous_token->getVal() == "function") {
        // if the identifer decleration is not already in the list, add it
        if (!vecContainsIdentifier(current_token, validIdentifiers)) {
          if (previous_token->getVal() == "var") {
            current_token->setIdentifierType(variable);
          } else {
            current_token->setIdentifierType(function);
            current_token->setArgCount(findArgCount(current_token, tokens, i));
          }
          validIdentifiers.emplace_back(new Token(*current_token));
        } else {
          // if the identifier decleration IS already in the vector
          // this identifer has previously been defined, so throw an error
          printIdentifierError(current_token, multiple_declaration);
          exit(0);
        }
      }
      // if it is not preceded by those keywords, it's a reference
      else {
        // if the vector of valid identifiers does not contain the token
        // print an error and exit
        if (!vecContainsIdentifier(current_token, validIdentifiers)) {
          printIdentifierError(current_token, invalid_reference);
          exit(0);
        }
      }
    }
  }
}

bool Lexical::vecContainsIdentifier(
    Token *token, const std::vector<std::shared_ptr<Token>> &vec) {
  for (auto &identifier : vec) {
    if (token->getVal() == identifier->getVal()) {
      token->setIdentifierType(identifier->getIdentifierType());
      token->setArgCount(identifier->getArgCount());
      return true;
    }
  }
  return false;
}

int Lexical::findArgCount(Token *token,
                          const std::vector<std::shared_ptr<Token>> &vec,
                          int index) {
  int argCount = 0;
  index++;
  // if function declaration is not followed by open perentheses, print an error
  // and exit
  if (vec[index]->getVal() != "(") {
    printIdentifierError(token, invalid_decleration);
  }
  while (vec[index]->getVal() != ")") {
    if (vec[index]->getVal() == "var" &&
        vec[index + 1]->getTokenType() == identifier) {
      argCount++;
    }
    index++;
  }
  return argCount;
}

void Lexical::printIdentifierError(Token *const token,
                                   const identifierErrors error) {
  std::cout << "\n***Error at " << token->getLine() << ","
            << token->getCharPos() << "\nReason:";
  switch (error) {
  case invalid_reference:
    std::cout << " invalid reference to identifier \'" << token->getVal()
              << "\' - no definition found";
    break;

  case multiple_declaration:
    std::cout << "Identifier \'" << token->getVal()
              << "\' already defined earlier in the program";
    break;
  default:
    std::cout << "none";
    break;
  }
  std::cout << "\nExiting program...";
}

// Literal Token
// creation-----------------------------------------------------------
LiteralToken *Lexical::createLiteralToken(const std::string str,
                                          const int line_no,
                                          const int char_pos) {
  if (Comparisons::strIsBoolLiteral(str))
    return createBoolLiteralToken(str, line_no, char_pos);
  if (Comparisons::strIsNumericLiteral(str))
    return createNumericLiteralToken(str, line_no, char_pos);
  if (Comparisons::strIsStrLiteral(str))
    return createStrLiteralToken(str, line_no, char_pos);
  // if (Comparisons::strIsListLiteral(str))
  // return createListLiteralToken
}

LiteralToken *Lexical::createBoolLiteralToken(const std::string str,
                                              const int line_no,
                                              const int char_pos) {
  return new LiteralToken(literal, boolean, str, line_no, char_pos);
}
LiteralToken *Lexical::createNumericLiteralToken(const std::string str,
                                                 const int line_no,
                                                 const int char_pos) {
  return new LiteralToken(literal, number, str, line_no, char_pos);
}
LiteralToken *Lexical::createStrLiteralToken(const std::string str,
                                             const int line_no,
                                             const int char_pos) {
  return new LiteralToken(literal, string, str, line_no, char_pos);
}

// Identifier Token
// creation-------------------------------------------------------------
IdentifierToken *Lexical::createIdentifierToken(const std::string str,
                                                const int line_no,
                                                const int char_pos) {
  /*
  checks for valid reference to identifiers are done after tokenisation
  */
  return new IdentifierToken(identifier, nullIdentifier, str, line_no, char_pos,
                             NULL);
}