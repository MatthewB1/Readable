#include "Token.h"

Token::~Token()
{
}

Token::Token(token_ token, std::string value, int line, int pos)
{
	this->token_type = token;
	this->value = value;
	this->line_number = line;
	this->character_pos = pos;
}

token_ Token::getTokenType()
{
	return token_type;
}

int Token::getLineNumber()
{
	return this->line_number;
}

int Token::getCharacterPos()
{
	return this->character_pos;
}


