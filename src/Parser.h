
#include "Lexical.h"
#include "TreeNode.h"

namespace Parser {

typedef enum {addsub, multdiv, expo, paren} precedence;

std::vector<TreeNode<std::shared_ptr<Token>>>
parse(const std::vector<std::shared_ptr<Token>> &tokens);

TreeNode<std::shared_ptr<Token>>
evaluateStatement(const std::vector<std::shared_ptr<Token>> &statement);

TreeNode<std::shared_ptr<Token>>
evaluateKeywordStatement(const std::vector<std::shared_ptr<Token>> &statement);

TreeNode<std::shared_ptr<Token>>
evaluateIdentifierStatement(const std::vector<std::shared_ptr<Token>> &statement);

TreeNode<std::shared_ptr<Token>> *
evaluateExpression(const std::vector<std::shared_ptr<Token>> &expression);

std::deque<std::shared_ptr<Token>> 
toPostfix(const std::vector<std::shared_ptr<Token>> &expression); 

bool higherPrecedence(std::string op1, std::string op2);
 
void errorEvaluatingStatement();
}