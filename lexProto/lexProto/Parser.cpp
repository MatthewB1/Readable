#include "Parser.h"

#define current_token tokens[i]

std::vector<TreeNode<Token *> *> Parser::parse(const std::vector<Token *> &tokens) {
  /*
  To begin with I am going to focus on parsing some simple lines of code :
  var y = 3;

  I expect this to be visually represented as something like
        =
      /   \
    Y       3

    This basic <operand><operator><operand> will be the building block of expressions I assume.
    For example a slightly more complex line of code:
    x = 4 + 7;
        =
      /   \
     x     +
         /   \
        4     7

    For now I want to approach parsing these simple statements. Before moving on to more complex things.
  */

 //trees vector will hold pointers to the top of each tree
 std::vector<TreeNode<Token *> *> trees;
 std::vector<Token *> current_statement;

  for (auto i = 0; i < tokens.size(); i++) {

      if(current_token->getTokenType() == delim && current_token->getVal() == ";"){
          //if we reach a semi colon, that denotes the end of a statement
          //not sure how this works when defining a function, but we'll get to that
          evaluateStatement(current_statement);
          continue;
      }

      current_statement.push_back(current_token);
  }

  return trees;
}

void Parser::evaluateStatement(const std::vector<Token *> &statement){
    std::cout << "\n**********************************************************\n";
    std::cout << "Evaluating the following statement:" <<"\n\t";
    std::for_each(statement.begin(), statement.end(), [](auto token){std::cout << token->getVal() << " "; });


    //at this point we need to see if the expression is valid
    //potentially build regular expressions



}