#include "Token.h"

//---------------------Token Implementation------------------------------
Token::Token(const TypeOf _tokenType, const std::string _val,
             const int _lineNum, const int _charPos) {
  this->tokenType = _tokenType;
  this->val = _val;
  this->lineNum = _lineNum;
  this->charPos = _charPos;
}
const TypeOf Token::getTokenType() { return this->tokenType; }
const std::string Token::getVal() { return this->val; }
const int Token::getLine() { return this->lineNum; }
const int Token::getCharPos() { return this->charPos; }

//why can't i return null :(
const LiteralType LiteralToken::getLiteralType() { return NULL; }

//----------------------LiteralToken Implementaton-----------------------
LiteralToken::LiteralToken(const TypeOf _tokenType,
                           const LiteralType _literalType,
                           const std::string _val, const int _lineNum,
                           const int _charPos)
    : Token::Token(_tokenType, _val, _lineNum, _charPos) {
  this->literalType = _literalType;
}

const LiteralType LiteralToken::getLiteralType() { return this->literalType; }

//----------------------------------------------------------------------
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