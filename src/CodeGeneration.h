
#include "Parser.h"
#include <cassert>
#include <fstream>
#include <iostream>

namespace CodeGeneration {

void generate(std::vector<TreeNode<std::shared_ptr<Token>>> trees);

void printCode(std::vector<std::string> statements);

void saveToFile(std::vector<std::string> statements);

int maxStackSize(std::vector<TreeNode<std::shared_ptr<Token>>> &trees);

void countOperators(int *max, TreeNode<std::shared_ptr<Token>> *node);

void findIdentifiers(std::vector<std::string> *uniqueidentifiers,
                     TreeNode<std::shared_ptr<Token>> *node);

bool identifierSeen(std::vector<std::string> uniqueidentifiers,
                    std::shared_ptr<Token> token);

void findIdentifiers(std::vector<std::string> *uniqueidentifiers,
                     TreeNode<std::shared_ptr<Token>> *node);

void generateBytecode(std::vector<std::string> uniqueidentifiers,
                      std::vector<std::string> *statements,
                      TreeNode<std::shared_ptr<Token>> *node);

std::deque<std::shared_ptr<Token>>
toPostfix(TreeNode<std::shared_ptr<Token>> expression);

void treeToVector(TreeNode<std::shared_ptr<Token>> *node,
                  std::vector<std::shared_ptr<Token>> *expressionVec);

int indexOfIdentifier(std::string identifier, std::vector<std::string> &vector);

void printGenerateError(TreeNode<std::shared_ptr<Token>> *node);

void printTree(TreeNode<std::shared_ptr<Token>> *node);

} // namespace CodeGeneration