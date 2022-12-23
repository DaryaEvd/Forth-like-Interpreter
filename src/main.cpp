#include <iostream>

#include "commands.hpp"
#include "interpreter.hpp"
#include <sstream>

int main(){
  Interpreter &i = Interpreter::getInstance();
  
  while (true) {
    std::string input = "";
    std::cout << "> ";
    std::getline(std::cin, input);

    // for tests better not iterators
    // const std::string::iterator &begin = input.begin();
    // const std::string::iterator &end = input.end();
    // std::cout << i.Interpret(begin, end) << std::endl;

    std::cout << i.interpret(input) << std::endl;
  }

  return 0;
}
