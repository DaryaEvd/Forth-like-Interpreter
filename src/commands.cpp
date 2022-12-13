#include <memory>

#include "commands.hpp"
#include "interpreter.hpp"

namespace {

//   bool addCmd = Interpreter::GetInstance().registerCreator(
//     "+", std::make_unique<Add>());
//   bool subCmd = Interpreter::GetInstance().registerCreator(
//     "-", std::make_unique<Sub>());
//   bool multCmd = Interpreter::GetInstance().registerCreator(
//     "*", std::make_unique<Mult>());
//   bool divCmd = Interpreter:: GetInstance().registerCreator(
//     "/", std::make_unique<Div>());
//   bool modCmd = Interpreter:: GetInstance().registerCreator(
//     "mod", std::make_unique<Mod>());
//   bool dupCmd = Interpreter::GetInstance().registerCreator(
//     "dup", std::make_unique<Dup>());
//   bool dropCmd = Interpreter::GetInstance().registerCreator(
//     "drop", std::make_unique<Drop>());
//   bool writeCmd = Interpreter::GetInstance().registerCreator(
//     ".", std::make_unique<Write>());
//   bool rotCmd =Interpreter::GetInstance().registerCreator(
//     "rot", std::make_unique<Rot>());
//   bool overCmd = Interpreter:: GetInstance().registerCreator(
//     "over", std::make_unique<Over>());
//   bool emitCmd = Interpreter:: GetInstance().registerCreator(
//     "emit", std::make_unique<Emit>());
//   bool CRCmd =Interpreter::GetInstance().registerCreator(
//     "cr", std::make_unique<CR>());
//   bool greaterCmd = Interpreter::GetInstance().registerCreator(
//     ">", std::make_unique<Greater>());
//   bool lessCmd = Interpreter::GetInstance().registerCreator(
//     "<", std::make_unique<Less>());
//   bool equalCmd = Interpreter::GetInstance().registerCreator(
//     "=", std::make_unique<Equal>());

  Command *AddCreator() { return new Add(); }
  bool addCmd =
      Interpreter::GetInstance().registerCreator("+", AddCreator());

  Command *SubCreator() { return new Sub(); }
  bool subCmd =
      Interpreter::GetInstance().registerCreator("-", SubCreator());

  Command *MultCreator() { return (new Mult()); }
  bool multCmd =
      Interpreter::GetInstance().registerCreator("*", MultCreator());

  Command *DivCreator() { return (new Div()); }
  bool divCmd =
      Interpreter::GetInstance().registerCreator("/", DivCreator());

  Command *ModCreator() { return (new Mod()); }
  bool modCmd =
      Interpreter::GetInstance().registerCreator("mod", ModCreator());

  Command *DupCreator() { return (new Dup()); }
  bool dupCmd =
      Interpreter::GetInstance().registerCreator("dup", DupCreator());

  Command *DropCreator() { return new Drop(); }
  bool dropCmd =
      Interpreter::GetInstance().registerCreator("drop", DropCreator());

  Command *WriteCreator() { return new Write(); }
  bool writeCmd =
      Interpreter::GetInstance().registerCreator(".", WriteCreator());

  Command *RotCreator() { return (new Rot()); }
  bool rotCmd =
      Interpreter::GetInstance().registerCreator("rot", RotCreator());

  Command *OverCreator() { return (new Over()); }
  bool overCmd =
      Interpreter::GetInstance().registerCreator("over", OverCreator());

  Command *EmitCreator() { return (new Emit()); }
  bool emitCmd =
      Interpreter::GetInstance().registerCreator("emit", EmitCreator());

  Command *CRCreator() { return (new CR()); }
  bool crCmd =
      Interpreter::GetInstance().registerCreator("cr", CRCreator());

  Command *GreaterCreator() { return (new Greater()); }
  bool greaterCmd =
      Interpreter::GetInstance().registerCreator(">", GreaterCreator());

  Command *LessCreator() { return (new Less()); }
  bool lessCmd =
      Interpreter::GetInstance().registerCreator("<", LessCreator());

  Command *EqualCreator() { return (new Equal()); }
  bool equalCmd =
      Interpreter::GetInstance().registerCreator("=", EqualCreator());

} // namespace
