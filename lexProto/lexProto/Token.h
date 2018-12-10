#include <string>

enum class token_ { Identifier, Literal, Keyword, Comment, Seperator, Operator};

class Token
{
public:
	~Token();
	Token(token_ token, std::string value, int line, int pos);

	token_ getTokenType();
	std::string getValue();
	int getLineNumber();
	int getCharacterPos();
private:
	Token();
	token_ token_type;
	//how to store the value??
	std::string value;
	int line_number;
	int character_pos;
};

