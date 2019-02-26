#include <fstream>

#include "Parser.h"
namespace Utils {

std::vector<char> readFile(std::string path);

void printCode(const std::vector<char> &code);

void printTokens(const std::vector<Token *> &vec);

void visualiseProgram(const std::vector<TreeNode<Token *> *> &expressions);

} // namespace Utils