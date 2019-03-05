#include "Parser.h"

#define current_token tokens[i]

std::vector<TreeNode<std::shared_ptr<Token>>>
Parser::parse(const std::vector<std::shared_ptr<Token>> &tokens) {
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
  std::vector<TreeNode<std::shared_ptr<Token>>> trees;
  std::vector<std::shared_ptr<Token>> current_statement;

  for (auto i = 0; i < tokens.size(); i++) {

    if (current_token->getTokenType() == delim &&
        current_token->getVal() == ";") {
      // if we reach a semi colon, that denotes the end of a statement
      // not sure how this works when defining a function, but we'll get to that
      trees.emplace_back(evaluateStatement(current_statement));

      current_statement.clear();
      continue;
    }

    current_statement.emplace_back(current_token);
  }

  return trees;
}

TreeNode<std::shared_ptr<Token>> Parser::evaluateStatement(
    const std::vector<std::shared_ptr<Token>> &statement) {
  std::cout << "\n**********************************************************\n";
  std::cout << "Evaluating the following statement:"
            << "\n\t";
  std::for_each(statement.begin(), statement.end(),
                [](auto token) { std::cout << token->getVal() << " "; });

  switch (statement[0]->getTokenType()) {
  case keyword: {
    TreeNode<std::shared_ptr<Token>> tree = evaluateKeywordStatement(statement);
    return tree;
  }
  default: { errorEvaluatingStatement(); }
  }
}

TreeNode<std::shared_ptr<Token>> Parser::evaluateKeywordStatement(
    const std::vector<std::shared_ptr<Token>> &statement) {
  // variable declaration
  if (statement[0]->getVal() == "var") {
    if (statement[1]->getTokenType() != identifier ||
        statement[2]->getVal() == "=") {
      // set '=' as root of tree
      TreeNode<std::shared_ptr<Token>> head =
          TreeNode<std::shared_ptr<Token>>(statement[2]);
      // lhs is identifier
      head.setLeft(new TreeNode<std::shared_ptr<Token>>(statement[1]));
      // rhs is expression
      head.setRight(evaluateExpression(std::vector<std::shared_ptr<Token>>(
          std::make_move_iterator(statement.begin() + 3),
          std::make_move_iterator(statement.end()))));

      return head;
    } else {
      /*
        statement does not match grammar : <identifier><operator><expression>
      */
      errorEvaluatingStatement();
    }
  }
}

TreeNode<std::shared_ptr<Token>> *Parser::evaluateExpression(
    const std::vector<std::shared_ptr<Token>> &expression) {
  if (expression.size() == 1) {
    return new TreeNode<std::shared_ptr<Token>>(expression[0]);
  }

  // std::stack<TreeNode<std::shared_ptr<Token>>> stack;

  // // we want deque behaviour, so copy vector elements into deque,
  // // we also would like the expression in postfix notation
  // TreeNode<std::shared_ptr<Token>> hold;
  // std::deque<TreeNode<std::shared_ptr<Token>>> expr(expression.size());
  // std::copy(expression.begin(), expression.end(), expr.begin());

  // while (expr.size() > 0) {
  // }

  return new TreeNode<std::shared_ptr<Token>>(expression[0]);
}

void Parser::errorEvaluatingStatement() {
  std::cout << "\n***Error evaluating statement...\nExiting program...";
  exit(0);
}