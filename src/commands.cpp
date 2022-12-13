#include <memory>

#include "commands.hpp"
#include "interpreter.hpp"

namespace {

   bool addCmd = Interpreter::GetInstance().registerCreator(
     "+", std::make_unique<Add>());
   bool subCmd = Interpreter::GetInstance().registerCreator(
     "-", std::make_unique<Sub>());
   bool multCmd = Interpreter::GetInstance().registerCreator(
     "*", std::make_unique<Mult>());
   bool divCmd = Interpreter:: GetInstance().registerCreator(
     "/", std::make_unique<Div>());
   bool modCmd = Interpreter:: GetInstance().registerCreator(
     "mod", std::make_unique<Mod>());
   bool dupCmd = Interpreter::GetInstance().registerCreator(
     "dup", std::make_unique<Dup>());
   bool dropCmd = Interpreter::GetInstance().registerCreator(
     "drop", std::make_unique<Drop>());
   bool writeCmd = Interpreter::GetInstance().registerCreator(
     ".", std::make_unique<Write>());
   bool rotCmd =Interpreter::GetInstance().registerCreator(
     "rot", std::make_unique<Rot>());
   bool overCmd = Interpreter:: GetInstance().registerCreator(
     "over", std::make_unique<Over>());
   bool emitCmd = Interpreter:: GetInstance().registerCreator(
     "emit", std::make_unique<Emit>());
   bool CRCmd =Interpreter::GetInstance().registerCreator(
     "cr", std::make_unique<CR>());
   bool greaterCmd = Interpreter::GetInstance().registerCreator(
     ">", std::make_unique<Greater>());
   bool lessCmd = Interpreter::GetInstance().registerCreator(
     "<", std::make_unique<Less>());
   bool equalCmd = Interpreter::GetInstance().registerCreator(
     "=", std::make_unique<Equal>());

} // namespace
