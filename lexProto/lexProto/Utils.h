#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Token.h"
#include "TreeNode.hpp"
namespace Utils {

	template <typename T>
	void printVec(const T& v) {
			std::for_each(v.cbegin(), v.cend(), [](auto o) {std::cout << o; });
			std::cout << "\n\n";
		}


	template <typename T>
	void printTokens(const T& v) {
		std::cout << "Tokens: {";
		for (size_t i = 0; i < v.size(); i++)
		{
			//specialcase for printing new line character
			if (v[i] == "\n")
				std::cout << "\\n";
			else
				std::cout << v[i];

			if (v[i] != v[v.size() - 1]) {
				std::cout << ", ";
			}
		}
		std::cout << "}";
	}

	std::vector<char> readFile(std::string path);

	std::vector<Token> tokenise(const std::vector<char>& chars);

	//TreeNode<Token> parse(const std::vector<std::string>& tokens);

}