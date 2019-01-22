
#include "Lexical.h"
#include "TreeNode.hpp"

namespace Parser {

std::vector<TreeNode<Token *> *> parse(const std::vector<Token *> &tokens);

void evaluateStatement(const std::vector<Token *> &statement);
}