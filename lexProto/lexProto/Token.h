#include <memory>
#include <string>
#include <vector>

//enumdefinitions

typedef enum { identifier, delim, keyword, op, logical_op, literal } TypeOf;

typedef enum { number, string, boolean, list, nullLiteral} LiteralType;

typedef enum { variable, function, nullIdentifier } IdentifierType;

class Token {
public:
  Token(const TypeOf tokenType, const std::string val, const int lineNum,
        const int charPos);

  const TypeOf getTokenType();
  const std::string getVal();
  const int getLine();
  const int getCharPos();

  //virtual functions
  virtual const LiteralType getLiteralType();
  virtual const IdentifierType getIdentifierType();
  virtual const int getArgCount();
  virtual void setIdentifierType(const IdentifierType IdentifierType);
  virtual void setArgCount(const int argCount);

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

//not sure about this, may split into variable and function identifiers
//potential problems with identifying list variables?
class IdentifierToken : public Token {
public:
  IdentifierToken(const TypeOf tokenType, const IdentifierType identifierType,
                  const std::string val, const int lineNum, const int charPos,
                  const int argCount);

  virtual const IdentifierType getIdentifierType();
  virtual const int getArgCount();

  virtual void setIdentifierType(const IdentifierType IdentifierType);
  virtual void setArgCount(const int argCount);

private:
  IdentifierType identifierType;
  int argCount;
};