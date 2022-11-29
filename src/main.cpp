#include "commands.hpp"
#include "interpreter.hpp"

int main() {
  Interpreter &interpreter = Interpreter::getInstance();
  std::string expr;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, expr);
    // std::cout << interpreter.Interpret(expr.begin(), expr.end()) << std::endl;  
    interpreter.Interpret(expr);
  }
  return 0;
}
