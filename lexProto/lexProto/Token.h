#include <memory>
#include <string>
#include <vector>

typedef enum { identifier, delim, keyword, op, logical_op, literal } TypeOf;

typedef enum { number, string, boolean, list } LiteralType;

class Token {
public:
  Token(const TypeOf tokenType, const std::string val, const int lineNum,
        const int charPos);

  // TODO extend Token to identify data type or identifier type
  // could create new Token classes that inheret from Token

  const TypeOf getTokenType();
  const std::string getVal();
  const int getLine();
  const int getCharPos();

  virtual const LiteralType getLiteralType();

  // static const std::vector<std::string> getKeywords(){
  //   return KEYWORDS;
  // }

private:
  TypeOf tokenType;
  std::string val;
  int lineNum;
  int charPos;
};

class LiteralToken : public Token {
public:
  LiteralToken(const TypeOf tokenType, const LiteralType literalType,
               const std::string val, const int lineNum, const int charPos);

  virtual const LiteralType getLiteralType();

private:
  LiteralType literalType;
};

typedef enum { variable, function } IdentifierType;
//not sure about this, may split into variable and function identifiers
//potential problems with identifying list variables?
class IdentifierToken : public Token {
public:
  IdentifierToken(const TypeOf tokenType, const IdentifierType identifierType,
                  const std::string val, const int lineNum, const int charPos,
                  const int argCount = NULL);

  const IdentifierType getIdentifierType();
  const int getArgCount();

private:
  IdentifierType identifierType;
  int argCount;
};