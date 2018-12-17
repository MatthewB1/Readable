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
    /*
    it's obvious that formatting could be improved
    */
    std::cout << "\t" << vec[i]->getLine() << "," << vec[i]->getCharPos();
    if (vec[i]->getLine() < 10)
      std::cout << " ";
    if (vec[i]->getCharPos() < 10)
      std::cout << " ";
    std::cout << "- ";
    // switch through tokenType enum to get name of value
    switch (vec[i]->getTokenType()) {
    case identifier:
      std::cout << "identifier: ";
      break;
    case delim:
      std::cout << "delimiter:  ";
      break;
    case keyword:
      std::cout << "keyword:    ";
      break;
    case op:
      std::cout << "operator:   ";
      break;
    case logical_op:
      std::cout << "logical_op: ";
      break;
    case literal:
      std::cout << "literal:    ";
      break;
    default:
      std::cout << "undefined:  ";
      break;
    }
  
    if (vec[i]->getTokenType() == literal) {
      switch (vec[i]->getLiteralType()) {
      case number:
        std::cout << "number:  ";
        break;
      case string:
        std::cout << "string:  ";
        break;
      case boolean:
        std::cout << "boolean: ";
        break;
      case list:
        std::cout << "list:    ";
        break;
      default:
        std::cout << "undefined";
      }
    }

    std::cout << vec[i]->getVal() << std::endl;
  }
  std::cout << "}";
}
void Utils::print(std::string arg) { std::cout << arg; }