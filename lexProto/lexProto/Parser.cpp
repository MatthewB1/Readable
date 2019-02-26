#include "Parser.h"

#define current_token tokens[i]

std::vector<TreeNode<Token *> *>
Parser::parse(const std::vector<Token *> &tokens) {
  /*
  To begin with I am going to focus on parsing some simple lines of code :
  var y = 3;

  I expect this to be visually represented as something like
        =
      /   \
    Y       3

    This basic <operand><operator><operand> will be the building block of
  expressions I assume. For example a slightly more complex line of code: x = 4
  + 7;
        =
      /   \
     x     +
         /   \
        4     7

    For now I want to approach parsing these simple statements. Before moving on
  to more complex things.
  */

  // trees vector will hold pointers to the top of each tree
  std::vector<TreeNode<Token *> *> trees;
  std::vector<Token *> current_statement;

  for (auto i = 0; i < tokens.size(); i++) {

    if (current_token->getTokenType() == delim &&
        current_token->getVal() == ";") {
      // if we reach a semi colon, that denotes the end of a statement
      // not sure how this works when defining a function, but we'll get to that
      trees.push_back(evaluateStatement(current_statement));

      current_statement.clear();
      continue;
    }

    current_statement.push_back(current_token);
  }

  return trees;
}

TreeNode<Token *> *Parser::evaluateStatement(const std::vector<Token *> &statement) {
  std::cout << "\n**********************************************************\n";
  std::cout << "Evaluating the following statement:"
            << "\n\t";
  std::for_each(statement.begin(), statement.end(),
                [](auto token) { std::cout << token->getVal() << " "; });

  switch (statement[0]->getTokenType()) {
  case keyword: {
    TreeNode<Token *> * tree = evaluateKeywordStatement(statement);
    return tree;
  }
  default: {
    errorEvaluatingStatement();
  }
  }
}

TreeNode<Token *> *Parser::evaluateKeywordStatement(const std::vector<Token *> &statement) {
  //C++ does not support switch statements for strings lol
  //variable declaration
  if (statement[0]->getVal() == "var"){
    if (statement[2]->getVal() == "=") {
      //set '=' as head of tree
      TreeNode<Token *> head = TreeNode<Token *>(statement[2]);
      //left of tree is identifier
      head.setLeft(new TreeNode<Token*>(statement[1]));
      
      //if total length of statement is 4, ex - var y = 3, set rhs and return
      auto x = statement.size();
      if (x == 4){
        head.setRight(new TreeNode<Token *>(statement[3]));
        return &head;
      }
      //else, rhs is complex expression, evaluate and return head of expression
      else{
                      // evaluates expression, passes vector elements after '='
        head.setRight(evaluateExpression(std::vector<Token *>(
                std::make_move_iterator(statement.begin() + 3),
                std::make_move_iterator(statement.end()))));
      }
    }
     else{
       errorEvaluatingStatement();
     }
  }
}

TreeNode<Token *> *Parser::evaluateExpression(const std::vector<Token *> &expression) {
  return new TreeNode<Token *>(expression[0]);
}

void Parser::errorEvaluatingStatement(){
  std::cout << "\n***Error evaluating statement...\nExiting program...";
  exit(0);
}