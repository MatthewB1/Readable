#include "Utils.h"

int main() {

  // read the file in first, idk how to do this relative to the project lol
  std::vector<char> code = Utils::readFile(
      "C:\\code\\repos\\finalProject\\lexProto\\lexProto\\code.txt");
  // output the code we are about to lex
  Utils::print("The code! "
               ":\n**********************************************************");
  Utils::printVec(code);
  Utils::print("**********************************************************\n");

  // tokenise the code, and then print the tokens found
  Utils::printTokens(Lexical::tokenise(code));

  // TreeNode<Token> tree = Utils::parse(tokens);

  // GraphVis for outputting tree***
  return 0;
}
