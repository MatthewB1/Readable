
#include "Lexical.h"
#include "TreeNode.h"

namespace Parser {

std::vector<TreeNode<Token *> *> parse(const std::vector<Token *> &tokens);

TreeNode<Token *> * evaluateStatement(const std::vector<Token *> &statement);

TreeNode<Token *> *evaluateKeywordStatement(const std::vector<Token *> &statement);

TreeNode<Token *> *evaluateExpression(const std::vector<Token *> &expression);

void errorEvaluatingStatement();
}