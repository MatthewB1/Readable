#include <fstream>
// #include <graphvis/lib/gvc/gvc.h>

#include "Parser.h"
namespace Utils {

std::vector<char> readFile(std::string path);

void printCode(const std::vector<char> &code);

void printTokens(const std::vector<std::shared_ptr<Token>> &vec);

void visualiseProgram(
    const std::vector<TreeNode<std::shared_ptr<Token>>> &trees);

} // namespace Utils