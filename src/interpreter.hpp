#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "commands.hpp"
#include "interpretererror.hpp"

class Interpreter {
  public:

    static Interpreter &GetInstance() {
      static Interpreter i;
      return i;
    }

    // bool registerCreator(const std::string &strCmd,
    //                      std::unique_ptr<Command> && cmd) {
    bool registerCreator(const std::string &strCmd, Command *cmd) {
      creatorsCmds_[strCmd] = std::move(cmd);
      return true;
    }

    std::string Interpret(Context &cont) {
      const std::string::iterator begin = cont.inputStr.begin();
      const std::string::iterator end = cont.inputStr.end();
      auto it = begin;
      try {
        while (it != end) {
          auto isSpaceCheck = [](char i) { return std::isspace(i); };
          std::string::iterator spaceIter =
              std::find_if(it, end, isSpaceCheck);
          std::string strToCheck = std::string(it, spaceIter);

          if ((*it == '-' && std::isdigit(*(it + 1))) ||
              std::isdigit(*it)) {

            cont.stackCntxt.push(std::stoi(strToCheck));
            it = spaceIter;
          }

          else if (std::isspace(*it)) {
            it++;
            continue;
          }

          else if (cont.inputStr.length() > 2 &&
                  cont.inputStr[0] == '.' &&
                  cont.inputStr[1] == '\"' &&
                  std::isspace(cont.inputStr[2]) &&
                  cont.inputStr[cont.inputStr.length() - 1] != '\"') {
            throw InterpreterError("No closing quote");
          }

          else if (cont.inputStr.length() > 3 &&
                  cont.inputStr[0] == '.' &&
                  cont.inputStr[1] == '\"' &&
                  std::isspace(cont.inputStr[2]) &&
                  cont.inputStr[cont.inputStr.length() - 1] == '\"') {

            cont.ssOutput << cont.inputStr.substr(
                                3, cont.inputStr.length() - 4) << "\n";
            return cont.ssOutput.str();
          }

          else {
            auto commandIter = creatorsCmds_.find(strToCheck);
            if (commandIter == creatorsCmds_.end()) {
              throw InterpreterError("such command not found");
            }

            Command *toApply = commandIter->second;
            toApply->apply(cont);
            it = spaceIter;

            // std::unique_ptr<Command> toApply = std::move(commandIter->second);
            // toApply->apply(cont);
            // if(toApply != nullptr) {
            //   toApply->apply(cont);
            // }
            // it = spaceIter;
          }
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

  private:
    Interpreter() = default;
    Interpreter(Interpreter &other) = delete;
    Interpreter &operator=(const Interpreter &other) = delete;

    std::unordered_map<std::string, Command *> creatorsCmds_;
    // std::unordered_map<std::string, std::unique_ptr<Command>>
    //     creatorsCmds_;
};
