#include <algorithm>
#include <iostream>
#include <string>

#include "interpreter.hpp"
#include "interpretererror.hpp"

bool Interpreter::isNumber(std::string &prefix) {
  const std::string::iterator &begin = prefix.begin();
  const std::string::iterator &end = prefix.end();

  auto it = begin;
  if (*it == '-') {
    if (prefix.size() == 1) {
      return false;
    }
    it++;
  }
  return std::all_of(it, end, ::isdigit);
}

std::string Interpreter::interpret(std::string input) {
  std::string::iterator it = input.begin();
  const std::string::iterator &end = input.end();

  Context cont(stk_, it, end);

  try {
    while (it != end) {
      while (std::isspace(*it)) {
        it++;
      }
      if (it == end) {
        break;
      }

      auto firstNonSpace = it;
      auto isSpaceCheck = [](char i) { return std::isspace(i); };
      std::string::iterator spaceIter =
          std::find_if(it, end, isSpaceCheck);
      it = spaceIter;

      std::string prefix(firstNonSpace, spaceIter);
      if (isNumber(prefix)) {
        try {
          cont.stackCntxt.push(std::stoi(prefix));
        } catch (std::out_of_range &) {
          cont.ssOutput << "Out of bounds of int \n";
          return cont.ssOutput.str();
        }
      }

      else {
        auto commandIter = creatorsCmds_.find(prefix);
        if (commandIter == creatorsCmds_.end()) {
          throw InterpreterError("Such command not found");
        }
        (commandIter->second)->apply(cont);
      }

      if (it == end) {
        break;
      }
      it++;
    }
  } catch (InterpreterError &e) {
    cont.ssOutput << e.what() << "\n";
    return cont.ssOutput.str();
  }

  if (cont.ssOutput.str().empty()) {
    cont.ssOutput << "< ok\n";
  }
  return cont.ssOutput.str();
}
