#include "CodeGeneration.h"

void CodeGeneration::generate(
    std::vector<TreeNode<std::shared_ptr<Token>>> trees) {
  std::vector<std::string> uniqueidentifiers;
  std::vector<std::string> statements;

  std::cout << "\n**********************************************************\n";
  std::cout << "generating target code..." << std::endl << std::endl;

  /*
  Bytecode contains information about the code in the form
  stack=2, locals=4, args_size=1

  where stack is the maximum size of stack required to evaluate an expression
  locals is number of local variables
  args_size is the number of values added to local variables when the frame is
  created

  */

  // calculate max stack size
  int stacksize = maxStackSize(trees);

  // find local variables
  for (int i = 0; i < trees.size(); ++i) {
    std::cout << "finding identifiers in tree : ";
    findIdentifiers(&uniqueidentifiers, &trees[i]);
    std::cout << "..." << std::endl;
  }

  // output unique identifiers
  std::cout << std::endl << "unique identifiers in code : ";
  for (size_t i = 0; i < uniqueidentifiers.size(); i++) {
    std::cout << uniqueidentifiers[i];
    if (i != uniqueidentifiers.size() - 1)
      std::cout << ", ";
  }
  std::cout << std::endl;

  // uniqueIdentifiers now corresponds to the java bytecode local variables

  // output java bytecode information
  std::cout << std::endl
            << "maximum stack size for frame: " << stacksize << std::endl
            << "No. of identifiers in code: " << uniqueidentifiers.size()
            << std::endl
            << "No. of arguments being passed into function: 0" << std::endl
            << std::endl;

  statements.push_back(std::string("Code:"));

  // build information, like - stack=2, locals=4, args_size=1
  std::string argsString = "stack=";
  argsString += std::to_string(stacksize);
  argsString += ", locals=";
  argsString += std::to_string(uniqueidentifiers.size());
  argsString += ", args_size=0";
  statements.push_back(argsString);


  for (int i = 0; i < trees.size(); ++i) {
    std::cout << "generating bytecode for statement..." << std::endl;
    generateBytecode(uniqueidentifiers, &statements, &trees[i]);
  }

  printCode(statements);
  saveToFile(statements);
}

void CodeGeneration::printCode(std::vector<std::string> statements) {
  std::cout << "\n**********************************************************\n";
  std::cout << "Bytecode: " << std::endl;

  for (size_t i = 0; i < statements.size(); ++i) {
    std::cout << "\t" << statements[i] << std::endl;
  }

  std::cout << std::endl << "code compiled and saved to bytecode.txt...";
}

void CodeGeneration::saveToFile(std::vector<std::string> statements) {
  std::ofstream file("bytecode.txt");
  
  for (size_t i = 0; i < statements.size(); ++i){
    file << statements[i] << '\n';
  }
  file.close();
}

int CodeGeneration::maxStackSize(
    std::vector<TreeNode<std::shared_ptr<Token>>> &trees) {

  std::cout << std::endl << "calculating max stack size..." << std::endl;

  int max = 0;
  int count = 0;

  for (size_t i = 0; i < trees.size(); ++i) {
    countOperators(&count, &trees[i]);
    if (count > max)
      max = count;
    count = 0;
  }

  return max;
}
void CodeGeneration::countOperators(int *count,
                                    TreeNode<std::shared_ptr<Token>> *node) {
  if (node == NULL)
    return;
  countOperators(count, node->getLeft());
  if (node->getData()->getTokenType() == op)
    (*count)++;
  countOperators(count, node->getRight());
}

void CodeGeneration::findIdentifiers(
    std::vector<std::string> *uniqueidentifiers,
    TreeNode<std::shared_ptr<Token>> *node) {
  if (node == NULL)
    return;
  findIdentifiers(uniqueidentifiers, node->getLeft());
  std::cout << node->getData()->getVal() << " ";
  if (node->getData()->getTokenType() == identifier) {
    if (!identifierSeen(*uniqueidentifiers, node->getData())) {
      uniqueidentifiers->push_back(node->getData()->getVal());
    }
  }
  findIdentifiers(uniqueidentifiers, node->getRight());
}

bool CodeGeneration::identifierSeen(std::vector<std::string> uniqueidentifiers,
                                    std::shared_ptr<Token> token) {
  assert(token->getTokenType() == identifier);

  for (size_t i = 0; i < uniqueidentifiers.size(); ++i) {
    if (uniqueidentifiers[i] == token->getVal())
      return true;
  }

  return false;
}

void CodeGeneration::generateBytecode(
    std::vector<std::string> uniqueidentifiers,
    std::vector<std::string> *statements,
    TreeNode<std::shared_ptr<Token>> *node) {
  if (node == NULL)
    printGenerateError(node);
  if (node->getLeft() == nullptr || node->getRight() == nullptr)
    printGenerateError(node);

  if (node->getLeft()->getData()->getTokenType() != identifier) {
    printGenerateError(node);
    return;
  }

  if (node->getData()->getTokenType() != op &&
      node->getData()->getVal() != "=") {
    return;
  }

  auto statement = toPostfix(*node->getRight());

  //create bytecode instructions
  while (statement.size() > 0) {

    if (statement.front()->getTokenType() == literal &&
        statement.front()->getLiteralType() == number) {
      statements->push_back("iconst_" + statement.front()->getVal());
      statement.pop_front();
      continue;
    }

    if (statement.front()->getTokenType() == identifier) {
      auto i = indexOfIdentifier(statement.front()->getVal(),
                                 uniqueidentifiers);
      statements->push_back("iload_" + std::to_string(i));
      statement.pop_front();
      continue;
    }

    if (statement.front()->getTokenType() == op &&
        statement.front()->getVal() != "=") {

      if (statement.front()->getVal() == "+")
        statements->push_back("iadd");

      if (statement.front()->getVal() == "-")
        statements->push_back("isub");

      if (statement.front()->getVal() == "/")
        statements->push_back("idiv");

      if (statement.front()->getVal() == "*")
        statements->push_back("imul");

      statement.pop_front();
      continue;
    }

    //if no case matches
    printGenerateError(node);
    return;
  }

  auto index = indexOfIdentifier(node->getLeft()->getData()->getVal(),
                                 uniqueidentifiers);
  // if (index != NULL)
    statements->push_back("istore_" + std::to_string(index));
}

std::deque<std::shared_ptr<Token>>
CodeGeneration::toPostfix(TreeNode<std::shared_ptr<Token>> expression) {
  // turn tree into vector
  std::vector<std::shared_ptr<Token>> expressionVec;
  treeToVector(&expression, &expressionVec);

  auto size = expressionVec.size();

  auto expressionDeque = Parser::toPostfix(expressionVec);

  auto size2 = expressionVec.size();

  return expressionDeque;
}

void CodeGeneration::treeToVector(
    TreeNode<std::shared_ptr<Token>> *node,
    std::vector<std::shared_ptr<Token>> *expressionVec) {
  if (node == NULL)
    return;
  treeToVector(node->getLeft(), expressionVec);
  expressionVec->push_back(node->getData());
  treeToVector(node->getRight(), expressionVec);
}

int CodeGeneration::indexOfIdentifier(std::string identifier,
                                      std::vector<std::string> &vector) {
  for (size_t index = 0; index < vector.size(); ++index) {
    if (identifier == vector[index])
      return index;
  }
  return NULL;
}

void CodeGeneration::printGenerateError(
    TreeNode<std::shared_ptr<Token>> *node) {
  std::cout << "Error generating code for statement : ";
  printTree(node);
  std::cout << "I only generate code for expression statements!\nexample: x = "
               "3 + y\nsorry :~( "
            << std::endl
            << "exiting program...";
}

void CodeGeneration::printTree(TreeNode<std::shared_ptr<Token>> *node) {
  if (node == NULL)
    return;
  printTree(node->getLeft());
  std::cout << node->getData()->getVal() + " ";
  printTree(node->getRight());
}
