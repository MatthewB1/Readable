#include "Utils.h"



int main() {

	//read the file in first, 
	std::vector<char> code = Utils::readFile("C:\\code\\repos\\lexProto\\code.txt");
	//output the code we are about to lex
	std::cout << "The code!: \n";
	Utils::printVec(code);


	//for now, tokenise will take an argument of a vector of chars, and return a vector of strings
	std::vector<std::string> tokens = Utils::tokenise(code);

	//print out the tokens!!
	Utils::printTokens(tokens);

	//TreeNode<std::string> tree = Utils::parse(tokens);

	//GraphVis for outputting tree
	return 0;
}


