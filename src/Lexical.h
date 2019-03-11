#include "Comparisons.h"
#include <iostream>
#include <stack>
#include <utility>
#include <memory>

namespace Lexical {

std::vector<std::shared_ptr<Token>> tokenise(const std::vector<char> &chars);

bool bracketsBalanced(const std::vector<char> &chars);
void checkIdentifierValidity(const std::vector<std::shared_ptr<Token>> &tokens);

bool vecContainsIdentifier(Token *token,
                           const std::vector<std::shared_ptr<Token>> &vec);

int findArgCount(Token *token, const std::vector<std::shared_ptr<Token>> &vec,
                 int index);

typedef enum {
  invalid_reference,
  multiple_declaration,
  invalid_decleration
} identifierErrors;

void printBracketError(std::stack<std::pair<std::string, char>> &stack);
void printBracketError(const int line_no, const int char_pos, const char delim);
void printTokenisationError(const std::string str, const int line_no,
                            const int char_pos);
void printIdentifierError(Token *const token, const identifierErrors error);

LiteralToken *createLiteralToken(const std::string str, const int line_no,
                                 const int char_pos);
LiteralToken *createBoolLiteralToken(const std::string str, const int line_no,
                                     const int char_pos);
LiteralToken *createNumericLiteralToken(const std::string str,
                                        const int line_no, const int char_pos);
LiteralToken *createStrLiteralToken(const std::string str, const int line_no,
                                    const int char_pos);

IdentifierToken *createIdentifierToken(const std::string str, const int line_no,
                                       const int char_pos);
} // namespace Lexical