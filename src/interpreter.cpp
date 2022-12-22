#include <algorithm>
#include <iostream>
#include <string>

#include "interpreter.hpp"
#include "interpretererror.hpp"

bool Interpreter::IsNumber(std::string &prefix) {
  const std::string::iterator &begin = prefix.begin();
  const std::string::iterator &end = prefix.end();

  auto it = begin;
  if (*it == '-' && (std::isdigit(*(it + 1)))) {
    std::string negativeNum(it + 1, end);
    for (char &symbol : negativeNum) {
      if (!std::isdigit(symbol)) {
        return false;
      }
    }
    return true;
  } 
  else if (std::isdigit(*it)) {
    std::string positiveNum(it, end);
    for (char &symbol : positiveNum) {
      if (!std::isdigit(symbol)) {
        return false;
      }
    }
    return true;
  }

  return false;
}

std::string Interpreter::Interpret(std::string input) {
  const std::string::iterator &begin = input.begin();
  const std::string::iterator &end = input.end();

  Context cont(stk_, begin, end);

  auto it = begin;

  try {
    while (it != end) {
      while (std::isspace(*it)) {
        it++;
        continue;
      }
      // std::cout << "it:"<< *it << std::endl;
      if (it == end) {
        break;
      }

      auto firstNonSpace = it;
      auto isSpaceCheck = [](char i) { return std::isspace(i); };
      std::string::iterator spaceIter =
          std::find_if(it, end, isSpaceCheck);
      // std::cout << "sp it:" << *spaceIter << ";" << std::endl;
      it = spaceIter;

      std::string prefix(firstNonSpace, spaceIter);
      // std::string prefix(firstNonSpace, it);

      // std::cout << "prefix :" << prefix << ";" << std::endl;
      if (IsNumber(prefix)) {
        // std::cout << "num" << std::endl;
        cont.stackCntxt.push(std::stoi(prefix));
      }

      else {
        // std::cout << "prefix:" << prefix << std::endl;
        // std::cout << "from cmd" << std::endl;
        auto commandIter = creatorsCmds_.find(prefix);
        if (commandIter == creatorsCmds_.end()) {
          // std::cout << "this cmd not found:" << prefix <<
          // std::endl;
          throw InterpreterError("such command not found");
        }
        (commandIter->second)->apply(cont);
        // std::cout << "after applying" << std::endl;
        // break;  //with breaks works
        continue;
      }

      // std::cout << "i am here after " << std::endl;

      if (it == end) {
        break;
      }
      it++;
    }
  } catch (InterpreterError &e) {
    cont.ssOutput << e.what() << "\n";
    return cont.ssOutput.str();
  } catch (std::out_of_range) {
    cont.ssOutput << "out of bounds of int \n";
    return cont.ssOutput.str();
  }

  if (cont.ssOutput.str().empty()) {
    cont.ssOutput << "< ok\n";
  }
  return cont.ssOutput.str();
}
