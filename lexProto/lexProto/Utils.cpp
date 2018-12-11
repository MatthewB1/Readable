#include "Utils.h"

namespace Utils {

	std::vector<char> readFile(std::string path) {
		std::ifstream file(path);
		std::vector<char> buffer;

		if (file) {
			/*
			 * found this piece of code here : https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
			 * it allocates the size of the buffer before putting data into it, meaning we don't have to resize multiple times
			 */
			file.seekg(0, std::ios::end);
			std::streampos          length = file.tellg();
			file.seekg(0, std::ios::beg);

			buffer.resize(length);
			file.read(&buffer[0], length);
		}

		file.close();

		return buffer;
	}

	void print(std::string arg){
		std::cout << arg;
	}
	
	/*TreeNode<std::string> Utils::parse(const std::vector<std::string>& tokens)
	{
		return TreeNode<std::string>();
	}*/
}

