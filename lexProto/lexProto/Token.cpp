#include "Token.h"

Token::~Token()
{
}

Token::Token(token_ token, std::string value)
{
	this->token_type = token;
	this->value = value;
}
