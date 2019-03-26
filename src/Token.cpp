#include "Token.h"

//---------------------Token Implementation------------------------------
Token::Token(const TypeOf _tokenType, const std::string _val,
             const int _lineNum, const int _charPos) {
  this->tokenType = _tokenType;
  this->val = _val;
  this->lineNum = _lineNum;
  this->charPos = _charPos;
}
Token::Token(const Token &old) {
  this->tokenType = old.tokenType;
  this->val = old.val;
  this->lineNum = old.lineNum;
  this->charPos = old.charPos;
}
const TypeOf Token::getTokenType() { return tokenType; }
const std::string Token::getVal() { return val; }
const int Token::getLine() { return lineNum; }
const int Token::getCharPos() { return charPos; }

//virtual functions
const LiteralType Token::getLiteralType() { return nullLiteral; }
const IdentifierType Token::getIdentifierType() { return nullIdentifier; }
const int Token::getArgCount() { return NULL; }
void Token::setIdentifierType(const IdentifierType _identifierType) {}
void Token::setArgCount(const int _argCount) {}






//----------------------LiteralToken Implementaton-----------------------
LiteralToken::LiteralToken(const TypeOf _tokenType,
                           const LiteralType _literalType,
                           const std::string _val, const int _lineNum,
                           const int _charPos)
    : Token::Token(_tokenType, _val, _lineNum, _charPos) {
  this->literalType = _literalType;
}

const LiteralType LiteralToken::getLiteralType() { return this->literalType; }







//----------------------IdentifierToken Implementation----------------------
IdentifierToken::IdentifierToken(const TypeOf _tokenType,
                                 const IdentifierType _identifierType,
                                 const std::string _val, const int _lineNum,
                                 const int _charPos, const int _argCount)
    : Token::Token(_tokenType, _val, _lineNum, _charPos) {
  this->identifierType = _identifierType;
  this->argCount = _argCount;
}

const IdentifierType IdentifierToken::getIdentifierType() {return this->identifierType;}
const int IdentifierToken::getArgCount() { return this->argCount; }

void IdentifierToken::setIdentifierType(const IdentifierType _identifierType) {
  this->identifierType = _identifierType;
}
void IdentifierToken::setArgCount(const int _argCount){
  this->argCount = _argCount;
}