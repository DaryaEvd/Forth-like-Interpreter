#pragma once

#include <functional>
#include <limits>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>

#include "commands.hpp"
#include "interpretererror.hpp"

class Interpreter {
  public:
  typedef std::function<Command *(std::string::iterator &,
                                  std::string::iterator &)>
      creatorType;

  static Interpreter &getInstance() {
    static Interpreter i;
    return i;
  }

  bool registerCreator(const std::string &comand,
                       creatorType &creator) {
    creators_[comand] = creator;
    return true;
  }

  bool IsOverflowNumber(int number) {
    if (number > INT32_MAX || number < INT32_MIN) {
      return true;
    }
    return false;
  }

  std::list<Command *> GetCommands(std::string::iterator &begin,
                                   std::string::iterator &end) {
    std::list<Command *> commands;
    auto it = begin;
    std::string strCommand = "";
    for (it; it < end; it++) {
      if (*it != ' ') {
        if ((*it) != std::isdigit(*it)) {
          strCommand += std::to_string(*it);
        }
      }
      std::unordered_map<std::string, creatorType>::iterator
          iterCreator = creators_.find(strCommand);
      if (iterCreator == creators_.end()) {
        std::stringstream ss;
        ss << "no such command: '" << *it << "'";
        throw interpreterError(ss.str());
      }
      creatorType creator = (*iterCreator).second;
      Command *cmd = creator(it, end);
      commands.push_back(cmd);
    }
    return commands;
  }

  void Interpret(std::string expression_) {
    auto begin = expression_.begin();
    auto end = expression_.end();

    auto it = begin;
    while (it != end) {

      if ((std::isdigit(*it)) || (*it == '-' && std::isdigit(*(it + 1)))) {
        std::string strToConvertToNum = "";
        while (*it != ' ') {
          strToConvertToNum += (std::to_string(*it));
          it++;
        }
        int number = (std::stoi(strToConvertToNum));
        if (IsOverflowNumber(number)) {
          throw interpreterError("number is overflow max int");
        }
        stack_.push(number);
      }

      if (*it == '-') {
        if (std::isdigit(*(it + 1))) {
          continue;
        }

      }

      else if (*it == '.' && (*(it + 1) == '"') && (*(it + 2) == ' ')) {
        it = it + 3;
        std::string strContent = "";
        while (*it != '"') {
          strContent += std::to_string(*it);
          it++;
        }
        std::cout << "< " << strContent << std::endl;
      }

      else if (*it != ' ') {
        continue;
      }

      else {
        try {
          std::list<Command *> commands = GetCommands(it, end);  
          for (Command *cmd : commands) {
            cmd->apply(stack_);
            delete cmd;
          }
        } catch (interpreterError &e) {
          std::cerr << e.what() << std::endl;
        }
      }
    }
  }

  private:
  Interpreter() = default;
  // ~Interpreter() = delete; //???
  Interpreter(Interpreter &other) = delete;
  Interpreter &operator=(const Interpreter &other) = delete;

  std::unordered_map<std::string, creatorType> creators_;
  MyStack stack_;

  std::string expression_;
};
