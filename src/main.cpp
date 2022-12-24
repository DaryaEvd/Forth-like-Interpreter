#include <iostream>
#include <sstream>

#include "commands.hpp"
#include "interpreter.hpp"

int main() {
  Interpreter &i = Interpreter::getInstance();

  while (true) {
    std::string input = "";
    std::cout << "> ";
    std::getline(std::cin, input);

    std::cout << i.interpret(input) << std::endl;
  }

  return 0;
}
