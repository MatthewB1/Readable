#include <algorithm>
#include <fstream>

#include "Lexical.h"
#include "TreeNode.hpp"
namespace Utils {

template <typename T> void printVec(const T &v) {
  std::cout << "\n";
  std::for_each(v.cbegin(), v.cend(), [](auto o) { std::cout << o; });
  std::cout << "\n";
}

void printTokens(const std::vector<Token *> &vec);

std::vector<char> readFile(std::string path);

void print(std::string arg);

// TreeNode<Token> parse(const std::vector<std::string>& tokens);

} // namespace Utils