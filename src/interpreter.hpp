#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>

#include "commands.hpp"
#include "mystack.hpp"

class Interpreter {
public:
  static Interpreter &GetInstance() {
    static Interpreter i;
    return i;
  }

  bool RegisterCreator(std::string &&strCmd,
                       std::unique_ptr<Command> &&cmd) {
    assert(creatorsCmds_[strCmd] = std::move(cmd));
    return true;
  }

  std::string Interpret(std::string input);

private:
  Interpreter() = default;
  Interpreter(Interpreter &other) = delete;
  Interpreter &operator=(const Interpreter &other) = delete;

  bool IsNumber(std::string &prefix);
  std::unordered_map<std::string, std::unique_ptr<Command>>
      creatorsCmds_;

  MyStack stk_;
};
