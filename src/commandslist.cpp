#include <memory>

#include "commands.hpp"
#include "interpreter.hpp"

namespace {
  bool addCmd = Interpreter::getInstance().registerCreator(
    "+", std::make_unique<Add>());
  bool subCmd = Interpreter::getInstance().registerCreator(
    "-", std::make_unique<Sub>());
  bool multCmd = Interpreter::getInstance().registerCreator(
    "*", std::make_unique<Mult>());
  bool divCmd = Interpreter:: getInstance().registerCreator(
    "/", std::make_unique<Div>());
  bool modCmd = Interpreter:: getInstance().registerCreator(
    "mod", std::make_unique<Mod>());
  bool dupCmd = Interpreter::getInstance().registerCreator(
    "dup", std::make_unique<Dup>());
  bool dropCmd = Interpreter::getInstance().registerCreator(
    "drop", std::make_unique<Drop>());
  bool writeCmd = Interpreter::getInstance().registerCreator(
    ".", std::make_unique<Write>());
  bool swapCmd = Interpreter::getInstance().registerCreator(
    "swap", std::make_unique<Swap>());
  bool rotCmd =Interpreter::getInstance().registerCreator(
    "rot", std::make_unique<Rot>());
  bool overCmd = Interpreter:: getInstance().registerCreator(
    "over", std::make_unique<Over>());
  bool emitCmd = Interpreter:: getInstance().registerCreator(
    "emit", std::make_unique<Emit>());
  bool CRCmd =Interpreter::getInstance().registerCreator(
    "cr", std::make_unique<CR>());
  bool greaterCmd = Interpreter::getInstance().registerCreator(
    ">", std::make_unique<Greater>());
  bool lessCmd = Interpreter::getInstance().registerCreator(
    "<", std::make_unique<Less>());
  bool equalCmd = Interpreter::getInstance().registerCreator(
    "=", std::make_unique<Equal>());
  bool printQuotes = Interpreter::getInstance().registerCreator(
    ".\"", std::make_unique<BetweenQuotes>());
}
