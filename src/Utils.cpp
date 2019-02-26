#include "Utils.h"

std::vector<char> Utils::readFile(std::string path) {
/*
Reads in from a file, returns a vector of characters ready to be processed.
*/
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

void Utils::printCode(const std::vector<char> &v) {
  std::cout << "The "
               "code:\n********************************************************"
               "**\n";
  std::for_each(v.cbegin(), v.cend(), [](auto o) { std::cout << o; });
}

void Utils::printTokens(const std::vector<Token *> &vec) {
/*
This function prints out the tokens,
formatting them through switch cases depending on token type
it's a horrendous function to read but I think that's fine for now.
*/

std::cout << "\n**********************************************************\n";

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

  std::cout << vec[i]->getVal();

  if (vec[i]->getTokenType() == identifier &&
      vec[i - 1]->getTokenType() == keyword) {
    if (vec[i]->getIdentifierType() == function) {
      switch (vec[i]->getArgCount()) {
      case NULL:
        std::cout << "\tno. of args: NULL";
        break;
      default:
        std::cout << "\tno.of args: " << vec[i]->getArgCount();
      }
    }
  }

  std::cout << std::endl;
  }
  std::cout << "}";
}

void Utils::visualiseProgram(const std::vector<TreeNode<Token *> *> &trees){
  std::cout << "\n**********************************************************\n"
  << "Visualised program:\n\nNo. of statements in program : "
  << trees.size();

}