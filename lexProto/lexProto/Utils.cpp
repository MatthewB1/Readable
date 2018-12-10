#include "Utils.h"

namespace Utils {

	std::vector<char> Utils::readFile(std::string path) {
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

	std::vector<Token> Utils::tokenise(const std::vector<char>& chars) {
		//all of this needs rewriting
		std::vector<std::string> tokens;

		std::string token("");

		//iterate through characters, creating the tokens, in order
		//for now, grammar enforces corret whitespacing
		//i.e  "x = x + 7;" is valid, "x=x+7;" is not
		for (size_t i = 0; i < chars.size(); i++)
		{
			//if end of file,break, we're done tokenising
			if (chars[i] == EOF)
				break;
			//if we are not currently inside of a string
			if (token[0] != '\"') {
				//if character is semi colon or new line, push the current token, and a new one for this character
				if (chars[i] == ';' || chars[i] == '\n') {
					tokens.push_back(token);
					tokens.push_back(std::string(1, chars[i]));
					token.clear();
					continue;
				}
				//if the character is a space, as we are enforcing whitespace, this is the end of this token
				//push the token onto the vector, and clear it to start again
				if (chars[i] == ' ') {
					tokens.push_back(token);
					token.clear();
					continue;
				}
				//else, add character to token 
				token += chars[i];
				continue;
			}
			//if we are inside of a string
			else {
				//if previous character is not escape character
				if (chars[i - 1] != '\\') {
					//if second non escape character '"', string is over, create the token and clear it
					if (chars[i] == '\"') {
						token += chars[i];
						tokens.push_back(token);
						token.clear();
						continue;
					}
				}
				//else, add character to token
				token += chars[i];
				continue;
			}
		}

		return tokens;
	}

	/*TreeNode<std::string> Utils::parse(const std::vector<std::string>& tokens)
	{
		return TreeNode<std::string>();
	}*/
}

