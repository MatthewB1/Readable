#include <memory>
#include <string>

typedef enum { identifier, delim, keyword, op, logical_op, literal } TypeOf;

class Token {
public:
  Token(const TypeOf tokenType, const std::string val, const int lineNum,
        const int charPos);

  const TypeOf getTokenType();
  const std::string getVal();
  const int getLine();
  const int getCharPos();

private:
  TypeOf tokenType;
  // for now data is just going to be stored as a string, will look into better
  // ways of doing this
  std::string val;
  int lineNum;
  int charPos;
};