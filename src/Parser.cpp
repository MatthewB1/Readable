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
  std::cout << std::endl;

  switch (statement[0]->getTokenType()) {
  case keyword: {
    TreeNode<std::shared_ptr<Token>> tree = evaluateKeywordStatement(statement);
    return tree;
  }
  case identifier: {
    TreeNode<std::shared_ptr<Token>> tree =
        evaluateIdentifierStatement(statement);
    return tree;
  }
  default: { errorEvaluatingStatement(); }
  }
}

// KEYWORD
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

// IDENTIFIER
TreeNode<std::shared_ptr<Token>> Parser::evaluateIdentifierStatement(
    const std::vector<std::shared_ptr<Token>> &statement) {
  if (statement[0]->getTokenType() != identifier ||
      statement[1]->getVal() == "=") {
    // set '=' as root of tree
    TreeNode<std::shared_ptr<Token>> head =
        TreeNode<std::shared_ptr<Token>>(statement[1]);
    // lhs is identifier
    head.setLeft(new TreeNode<std::shared_ptr<Token>>(statement[0]));
    // rhs is expression
    head.setRight(evaluateExpression(std::vector<std::shared_ptr<Token>>(
        std::make_move_iterator(statement.begin() + 2),
        std::make_move_iterator(statement.end()))));

    return head;
  } else {
    /*
      statement does not match grammar : <identifier><operator><expression>
    */
    errorEvaluatingStatement();
  }
}

TreeNode<std::shared_ptr<Token>> *Parser::evaluateExpression(
    const std::vector<std::shared_ptr<Token>> &expression) {
  if (expression.size() == 1) {
    return new TreeNode<std::shared_ptr<Token>>(expression[0]);
  }

  // std::stack<TreeNode<std::shared_ptr<Token>>> stack;
  // auto postfix = toPostfix(expression);

  return new TreeNode<std::shared_ptr<Token>>(expression[0]);
}

std::deque<std::shared_ptr<Token>>
Parser::toPostfix(const std::vector<std::shared_ptr<Token>> &expression) {

  //**THIS SUCCESSFULLY ACCESSES THE VALUE
  std::cout << std::endl;
  for (auto i = 0; i < expression.size(); ++i){
    std::cout << expression[i]->getVal();
  }

  std::deque<std::shared_ptr<Token>> postfix;
  postfix.resize(expression.size());
  std::stack<std::shared_ptr<Token>> stack;

  for (auto i = 0; i < expression.size(); ++i) {
    // push operands to postfix deque
    if (expression[i]->getTokenType() == literal ||
        expression[i]->getTokenType() == identifier) {
      postfix.push_back(expression[i]);
      //**THIS SUCCESSFULLY ACCESSES THE VALUE
      std::cout << postfix[postfix.size() - 1]->getVal();
      continue;
    }
    // evaluate operator
    if (expression[i]->getTokenType() == op) {
      while (!stack.empty() && higherPrecedence(stack.top()->getVal(), expression[i]->getVal())) {
        postfix.push_back(stack.top());
        //**THIS SUCCESSFULLY ACCESSES THE VALUE
        std::cout << postfix[postfix.size() - 1]->getVal();
        stack.pop();
      }
      stack.push(expression[i]);
      continue;
    }
    // if it's neither of these it's invalid (for now)
    errorEvaluatingStatement();
  }
  // after the entire expression has been parsed
  // push any operators left on the stack to deque
  while (!stack.empty()) {
    postfix.push_back(stack.top());
    //**THIS SUCCESSFULLY ACCESSES THE VALUE
    std::cout << postfix[postfix.size() - 1]->getVal();
    stack.pop();
  }

  //**THIS SUCCESSFULLY ACCESSES THE VALUE
  std::cout << postfix[postfix.size() - 1]->getVal();

  //**THIS IS A SEG ERROR
  std::cout << postfix[0]->getVal();

  //**THIS IS A SEG ERROR
  std::cout <<std::endl << postfix[0]->getVal() << " " << postfix[1]->getVal() << " " << postfix[2]->getVal();
  
  std::cout << std::endl;

  //**THIS IS A SEG ERROR
  for(auto i = 0; i < postfix.size(); ++i){
    std::cout << postfix[i]->getVal();
  }

  


  return postfix;
}

bool Parser::higherPrecedence(std::string op1, std::string op2) {
  int first;
  int second;

  if (op1 == "+" || op1 == "-")
    first = addsub;
  if (op1 == "*" || op1 == "/")
    first = multdiv;
  if (op1 == "(" || op1 == ")")
    first == paren;

  if (op2 == "+" || op2 == "-")
    first = addsub;
  if (op2 == "*" || op2 == "/")
    first = multdiv;
  if (op2 == "(" || op2 == ")")
    first == paren;

  return first > second;
}

void Parser::errorEvaluatingStatement() {
  std::cout << "\n***Error evaluating statement...\nExiting program...";
  exit(0);
}