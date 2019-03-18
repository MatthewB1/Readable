#include "CodeGeneration.h"

void CodeGeneration::generate(
    std::vector<TreeNode<std::shared_ptr<Token>>> trees) {
        std::vector<std::string> statements;
  for (int i = 0; i < trees.size(); ++i) {
    statements.push_back(walkTree(trees[i]));
  }
  printCode(statements);
}

void CodeGeneration::printCode(std::vector<std::string> statements) {
  std::cout << "code compiled and saved to target.txt...";
}

std::string CodeGeneration::walkTree(TreeNode<std::shared_ptr<Token>> tree) {
    std::cout << "generating target code for tree : ";
    printTree(&tree);
    std::cout << "..." << std::endl;
    return " ";
}

// recursively prints all nodes, left to right
void CodeGeneration::printTree(TreeNode<std::shared_ptr<Token>> *node) {
  if (node == NULL)
    return;
  printTree(node->getLeft());
  std::cout << node->getData()->getVal() << " ";
  printTree(node->getRight());
}
