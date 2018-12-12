#include "Token.h"

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
