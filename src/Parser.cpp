#include "Parser.h"

#define current_token tokens[i]

std::vector<TreeNode<std::shared_ptr<Token>>>
Parser::parse(const std::vector<std::shared_ptr<Token>> &tokens) {

  // trees vector holds the root of all trees
  std::vector<TreeNode<std::shared_ptr<Token>>> trees;
  std::vector<std::shared_ptr<Token>> current_statement;

  for (auto i = 0; i < tokens.size(); i++) {

    /*
    encountering 'for' or 'function' should enter a special loop?
    */

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

  // print statement that is being evaluated
  std::cout << "\n**********************************************************\n";
  std::cout << "Evaluating the following statement:"
            << "\n\t";
  std::for_each(statement.begin(), statement.end(),
                [](auto token) { std::cout << token->getVal() << " "; });
  std::cout << std::endl;

  // switch case to select appropriate handler
  switch (statement[0]->getTokenType()) {

  //<keyword><identifier><operator><expression>
  case keyword: {
    TreeNode<std::shared_ptr<Token>> tree = evaluateKeywordStatement(statement);
    return tree;
  }

  //<identifier><operator><expression>
  case identifier: {
    TreeNode<std::shared_ptr<Token>> tree =
        evaluateIdentifierStatement(statement);
    return tree;
  }

  // default case is an error, as it matches no defined grammar
  default: {
    errorEvaluatingStatement();
    exit(0);
  }
  }
}

// KEYWORD
TreeNode<std::shared_ptr<Token>> Parser::evaluateKeywordStatement(
    const std::vector<std::shared_ptr<Token>> &statement) {

  if (statement[0]->getVal() == "var") {
    // variable declaration must match grammar:
    //<keyword><identifier><operator><expression>
    // keyword MUST be var, operator MUST be assignment operator
    if (statement[1]->getTokenType() == identifier &&
        statement[2]->getVal() == "=") {
      // set '=' as root of tree
      TreeNode<std::shared_ptr<Token>> head =
          TreeNode<std::shared_ptr<Token>>(statement[2]);
      // lhs is identifier
      head.setLeft(new TreeNode<std::shared_ptr<Token>>(statement[1]));
      // rhs is expression
      // pass in every element after "=" to evaluate
      head.setRight(evaluateExpression(std::vector<std::shared_ptr<Token>>(
          std::make_move_iterator(statement.begin() + 3),
          std::make_move_iterator(statement.end()))));

      return head;
    } else {
      /*
        statement does not match grammar : <identifier><operator><expression>
      */
      errorEvaluatingStatement();
      exit(0);
    }
  }
  if (statement[0]->getVal() == "flip") {
    // // flip statement must match grammar:
    // //<keyword><identifier>
    // // keyword MUST be flip, identifier MUST be bool type
    // if (statement[1]->getTokenType() == identifier &&
    //     statement[1]->getLiteralType() == boolean) {

    //   // flip <identifier>; will be implemented as
    //   // <identifier> = !<identifier>

    //   // set '=' as root of tree
    //   TreeNode<std::shared_ptr<Token>> head =
    //       TreeNode<std::shared_ptr<Token>>(std::make_shared<Token>(Token(op, "=", 0, 0)));
    //   // lhs is identifier
    //   head.setLeft(new TreeNode<std::shared_ptr<Token>>(statement[1]));
    //   // rhs is expression
    //   // pass in every element after "=" to evaluate
    //   if (statement[1]->getVal() == "true") {
    //     head.setRight(new TreeNode<std::shared_ptr<Token>>(
    //         std::make_shared<Token>(Token(literal, "false", 0, 0))));
    //     return head;
    //   }
    //   if (statement[1]->getVal() == "false") {
    //     head.setRight(new TreeNode<std::shared_ptr<Token>>(
    //         std::make_shared<Token>(Token(literal, "true", 0, 0))));
    //     return head;
    //   }
      
    //   //if for some reason the value of a boolean literal is neither true nor false, error
    //   errorEvaluatingStatement();
    //   exit(0);
    // } else {
    //   /*
    //    statement does not match grammar : <keyword><identifier>
    //  */
    //   errorEvaluatingStatement();
    //   exit(0);
    // }
  }
}

// IDENTIFIER
TreeNode<std::shared_ptr<Token>> Parser::evaluateIdentifierStatement(
    const std::vector<std::shared_ptr<Token>> &statement) {

  // variable declaration must match grammar:
  //<identifier><operator><expression>
  // operator can be assignment or add/sub/mult/div assignment
  if (statement[0]->getTokenType() == identifier

      && (statement[1]->getVal() == "=" || statement[1]->getVal() == "+=" ||
          statement[1]->getVal() == "-=" || statement[1]->getVal() == "*=" ||
          statement[1]->getVal() == "-=" || statement[1]->getVal() == "/=")) {
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
    exit(0);
  }
}

TreeNode<std::shared_ptr<Token>> *Parser::evaluateExpression(
    const std::vector<std::shared_ptr<Token>> &expression) {
  if (expression.size() == 1) {
    return new TreeNode<std::shared_ptr<Token>>(expression[0]);
  }

  std::stack<TreeNode<std::shared_ptr<Token>>> stack;
  auto postfix = toPostfix(expression);

  while (postfix.size() > 0) {
    // if front is an operand, place on stack
    auto token = postfix.front();
    if (postfix.front()->getTokenType() == TypeOf::literal ||
        postfix.front()->getTokenType() == TypeOf::identifier) {
      stack.push(postfix.front());
      postfix.pop_front();
      continue;
    }
    // if operator, make node, set top two stack elements as right and left,
    // place on stack
    if (postfix.front()->getTokenType() == TypeOf::op &&
            postfix.front()->getVal() != "=" ||
        postfix.front()->getTokenType() == TypeOf::logical_op) {
      if (stack.size() >= 2) {
        auto node = TreeNode<std::shared_ptr<Token>>(postfix.front());
        postfix.pop_front();
        node.setRight(new TreeNode<std::shared_ptr<Token>>(stack.top()));
        stack.pop();
        node.setLeft(new TreeNode<std::shared_ptr<Token>>(stack.top()));
        stack.pop();
        stack.push(node);
      } else {
        errorEvaluatingStatement();
        exit(0);
      }
      continue;
    }
    errorEvaluatingStatement();
    exit(0);
  }

  // if stack is not empty, expression was invalid
  // throw error and exit program
  if (stack.size() != 1) {
    errorEvaluatingStatement();
    exit(0);
  }

  return new TreeNode<std::shared_ptr<Token>>(stack.top());
}

// converts an expression - a vector of tokens into a deque of the same
// expression, in postfix
std::deque<std::shared_ptr<Token>>
Parser::toPostfix(const std::vector<std::shared_ptr<Token>> &expression) {

  std::deque<std::shared_ptr<Token>> postfix;
  std::stack<std::shared_ptr<Token>> stack;

  for (auto i = 0; i < expression.size(); ++i) {
    // push operands to postfix deque
    if (expression[i]->getTokenType() == literal ||
        expression[i]->getTokenType() == identifier) {
      postfix.push_back(expression[i]);
      continue;
    }
    // evaluate operator, if it's of higher precedence than the operator at the
    // top of the stack
    // push it straight on to the postfix deque
    // if it's of equal or lower precedence (or stack is empty) place on stack
    if (expression[i]->getTokenType() == op ||
        expression[i]->getTokenType() == logical_op) {
      while (!stack.empty() &&
             higherPrecedence(stack.top()->getVal(), expression[i]->getVal())) {
        postfix.push_back(stack.top());
        stack.pop();
      }
      stack.push(expression[i]);
      continue;
    }
    // if it's neither of these it's invalid (for now)
    // print error and end program
    errorEvaluatingStatement();
    exit(0);
  }

  // after the entire expression has been parsed
  // push any operators left on the stack to deque
  while (!stack.empty()) {
    postfix.push_back(stack.top());
    stack.pop();
  }

  return postfix;
}

// returns true when precedence of arg1 is higher than arg 2
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
    second = addsub;
  if (op2 == "*" || op2 == "/")
    second = multdiv;
  if (op2 == "(" || op2 == ")")
    second == paren;

  return first > second;
}

void Parser::errorEvaluatingStatement() {
  std::cout << "\n***Error evaluating statement...\nExiting program...";
}