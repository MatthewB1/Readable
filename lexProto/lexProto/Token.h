#include <string>

enum class token_ { Identifier, Literal, Keyword, Comment, Seperator, Operator};

class Token
{
public:
	~Token();
	Token(token_ token, std::string value);

	token_ getTokenType();
	std::string getValue();
private:
	Token();
	token_ token_type;
	std::string value;
};

