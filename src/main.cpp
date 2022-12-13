#include <iostream>

#include "commands.hpp"
#include "interpreter.hpp"

int main(){
  Interpreter &i = Interpreter::GetInstance();
  Context context;

  while (true){
    context.ssOutput.str(std::string());
    context.inputStr = "";
    std::cout << "> ";
    std::getline(std::cin, context.inputStr);
    i.Interpret(context);
    std::cout << context.ssOutput.str();
  }

  return 0;
}
