
#include "Lexical.h"
#include "TreeNode.h"

namespace Parser {

std::vector<TreeNode<std::shared_ptr<Token>>>
parse(const std::vector<std::shared_ptr<Token>> &tokens);

TreeNode<std::shared_ptr<Token>>
evaluateStatement(const std::vector<std::shared_ptr<Token>> &statement);

TreeNode<std::shared_ptr<Token>>
evaluateKeywordStatement(const std::vector<std::shared_ptr<Token>> &statement);

TreeNode<std::shared_ptr<Token>> *
evaluateExpression(const std::vector<std::shared_ptr<Token>> &expression);

void errorEvaluatingStatement();
}