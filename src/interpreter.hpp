#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "commands.hpp"
#include "interpretererror.hpp"

// CR : move implementation to separate file
class Interpreter {
  public:

    static Interpreter &GetInstance() {
      static Interpreter i;
      return i;
    }

    bool registerCreator(std::string && strCmd,
                         std::unique_ptr<Command> && cmd) {
      // CR: assert that we do not have this command already
      creatorsCmds_[strCmd] = std::move(cmd);
      return true;
    }

    std::string Interpret(Context &cont) {
      std::string &input = cont.inputStr;
      const std::string::iterator begin = input.begin();
      const std::string::iterator end = input.end();
      std::stringstream out;
//      MyStack ms;
//      Context ctx { input, out, ms };
      auto it = begin;
      try {
        while (it != end) {
          auto isSpaceCheck = [](char i) { return std::isspace(i); };
          // CR: skip spaces
          std::string::iterator spaceIter =
              std::find_if(it, end, isSpaceCheck);
          std::string strToCheck = std::string(it, spaceIter);

          // CR: check if it + 1 == end
          if ((*it == '-' && std::isdigit(*(it + 1))) ||
              std::isdigit(*it)) {

            cont.stackCntxt.push(std::stoi(strToCheck));
            it = spaceIter;
          }

          else if (std::isspace(*it)) {
            it++;
            continue;
          }

          // CR: ." hello" .
          // CR: either input or iterator everywhere
          else if (input.length() > 3 &&
                   input[0] == '.' &&
                   input[1] == '\"' &&
                   std::isspace(input[2]) &&
                   input[input.length() - 1] != '\"') {
            throw InterpreterError("No closing quote");
          }

          // CR: merge
          // CR: get_string(iterator str_start) -> std::string (string content)
          else if (input.length() > 3 &&
                   input[0] == '.' &&
                   input[1] == '\"' &&
                   std::isspace(input[2]) &&
                   input[input.length() - 1] == '\"') {

            cont.ssOutput << input.substr(
                    3, input.length() - 4) << "\n";
            return cont.ssOutput.str();
          }

          else {
            auto commandIter = creatorsCmds_.find(strToCheck);
            if (commandIter == creatorsCmds_.end()) {
              throw InterpreterError("such command not found");
            }
            (commandIter->second)->apply(cont);
            it = spaceIter;
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

     std::unordered_map<std::string, std::unique_ptr<Command>>
         creatorsCmds_;
};
