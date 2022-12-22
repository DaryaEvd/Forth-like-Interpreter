#include <memory>

#include "commands.hpp"
#include "interpreter.hpp"

namespace {
  bool addCmd = Interpreter::GetInstance().RegisterCreator(
    "+", std::make_unique<Add>());
  bool subCmd = Interpreter::GetInstance().RegisterCreator(
    "-", std::make_unique<Sub>());
  bool multCmd = Interpreter::GetInstance().RegisterCreator(
    "*", std::make_unique<Mult>());
  bool divCmd = Interpreter:: GetInstance().RegisterCreator(
    "/", std::make_unique<Div>());
  bool modCmd = Interpreter:: GetInstance().RegisterCreator(
    "mod", std::make_unique<Mod>());
  bool dupCmd = Interpreter::GetInstance().RegisterCreator(
    "dup", std::make_unique<Dup>());
  bool dropCmd = Interpreter::GetInstance().RegisterCreator(
    "drop", std::make_unique<Drop>());
  bool writeCmd = Interpreter::GetInstance().RegisterCreator(
    ".", std::make_unique<Write>());
  bool swapCmd = Interpreter::GetInstance().RegisterCreator(
    "swap", std::make_unique<Swap>());
  bool rotCmd =Interpreter::GetInstance().RegisterCreator(
    "rot", std::make_unique<Rot>());
  bool overCmd = Interpreter:: GetInstance().RegisterCreator(
    "over", std::make_unique<Over>());
  bool emitCmd = Interpreter:: GetInstance().RegisterCreator(
    "emit", std::make_unique<Emit>());
  bool CRCmd =Interpreter::GetInstance().RegisterCreator(
    "cr", std::make_unique<CR>());
  bool greaterCmd = Interpreter::GetInstance().RegisterCreator(
    ">", std::make_unique<Greater>());
  bool lessCmd = Interpreter::GetInstance().RegisterCreator(
    "<", std::make_unique<Less>());
  bool equalCmd = Interpreter::GetInstance().RegisterCreator(
    "=", std::make_unique<Equal>());
  bool printQuotes = Interpreter::GetInstance().RegisterCreator(
    ".\"", std::make_unique<BetweenQuotes>());
  
} // namespace
