
#include "Parser.h"
#include <iostream>

namespace CodeGeneration {

void generate(std::vector<TreeNode<std::shared_ptr<Token>>> trees);

void printCode(std::vector<std::string> statements);

std::string walkTree(TreeNode<std::shared_ptr<Token>> tree);

void printTree(TreeNode<std::shared_ptr<Token>> *tree);

} // namespace CodeGeneration