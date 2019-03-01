#include "Utils.h"

int main() {
  auto code = Utils::readFile("code.txt");
  Utils::printCode(code);

  //tokenise splits code into it's tokens, if they are valid. Ignoring context of surrounding tokens
  auto tokens = Lexical::tokenise(code);
  //print out information about tokens
  Utils::printTokens(tokens);
  
  /*
  At this point, lexical analysis has concluded.
  From this point on the program will take the tokens
  and build trees out of them
  */

 //parse will take into account context of surrounding tokens
 //if a statement does not match the pattern of a valid statement, it will be thrown out
 //if a statement is valid, a parsed tree will be built, and this is the AST of the compiler
  auto trees = Parser::parse(tokens);

  Utils::visualiseProgram(trees);

  /*
    now we have an AST, we can compile to target language
  */

  //test comment
  return 0;
}
