#include "Utils.h"

int main() {
  // read the file in first
  std::vector<char> code = Utils::readFile("code.txt");
  // output the code before lexical analysis

  Utils::printCode(code);

  //tokenise the code
  std::vector<Token *> tokens = Lexical::tokenise(code);
  //print out information about tokens
  Utils::printTokens(tokens);
  
  /*
  At this point, lexical analysis has concluded.
  From this point on the program will take the tokens
  and build trees out of them
  */
  std::vector<TreeNode<Token *> *> trees = Parser::parse(tokens);

  Utils::visualiseProgram(trees);

  /*
  I would like to visually represent the expression trees here
  */


  

  return 0;
}
