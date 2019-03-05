#include <fstream>

#include "Parser.h"
namespace Utils {

std::vector<char> readFile(std::string path);

void printCode(const std::vector<char> &code);

void printTokens(const std::vector<std::shared_ptr<Token>> &vec);

void visualiseProgram(
     std::vector<TreeNode<std::shared_ptr<Token>>> &trees);

void printTree(TreeNode<std::shared_ptr<Token>> * tree);

void printNode(TreeNode<std::shared_ptr<Token>> &node);

} // namespace Utils