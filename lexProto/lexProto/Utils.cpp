#include "Utils.h"

std::vector<char> Utils::readFile(std::string path) {
  std::ifstream file(path);
  std::vector<char> buffer;

  if (file) {
    /*
     * found this piece of code here :
     * https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
     * it allocates the size of the buffer before putting data into it, meaning
     * we don't have to resize multiple times
     */
    file.seekg(0, std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer.resize(length);
    file.read(&buffer[0], length);
  }

  file.close();

  return buffer;
}

void Utils::printTokens(const std::vector<Token *> &vec) {
  std::cout << "Tokens: {\n";
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << "\t";
    // switch through tokenType enum to get name of value
    switch (vec[i]->getTokenType()) {
    case 0:
      std::cout << "identifier";
      break;
    case 1:
      std::cout << "delimiter";
      break;
    case 2:
      std::cout << "keyword";
      break;
    case 3:
      std::cout << "operator";
      break;
    case 4:
      std::cout << "logical op";
      break;
    case 5:
      std::cout << "literal";
      break;
    default:
      std::cout << "undefined";
      break;
    }
    std::cout << ": " << vec[i]->getVal() << " - " << vec[i]->getLine() << ","
              << vec[i]->getCharPos() << std::endl;
  }
  std::cout << "}";
}
void Utils::print(std::string arg) { std::cout << arg; }