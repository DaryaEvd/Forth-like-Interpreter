#include "commands.hpp"
#include "interpreter.hpp"

namespace {

Command *AddCreator(std::string::iterator &it,
                    const std::string::iterator &end) {
  return new Add();
}
bool addCmd =
    Interpreter::getInstance().registerCreator("+", AddCreator);

Command *SubCreator(std::string::iterator &it,
                    const std::string::iterator &end) {
  return new Sub();
}
bool subCmd =
    Interpreter::getInstance().registerCreator("-", SubCreator);

Command *MulCreator(std::string::iterator &it,
                    const std::string::iterator &end) {
  return new Mul();
}
bool mulCmd =
    Interpreter::getInstance().registerCreator("*", MulCreator);

Command *DivCreator(std::string::iterator &it,
                    const std::string::iterator &end) {
  return new Div();
}
bool divCmd =
    Interpreter::getInstance().registerCreator("/", DivCreator);

Command *ModCreator(std::string::iterator &it,
                    const std::string::iterator &end) {
  return new Mod();
}
bool modCmd =
    Interpreter::getInstance().registerCreator("mod", DivCreator);

Command *DropCreator(std::string::iterator &it,
                     const std::string::iterator &end) {
  return new Drop();
}
bool dropCmd =
    Interpreter::getInstance().registerCreator("drop", DropCreator);

Command *WriteDotCreator(std::string::iterator &it,
                         const std::string::iterator &end) {
  return new WriteDot();
}
bool writeDotCmd =
    Interpreter::getInstance().registerCreator(".", WriteDotCreator);

Command *SwapCreator(std::string::iterator &it,
                     const std::string::iterator &end) {
  return new Swap();
}
bool swapCmd =
    Interpreter::getInstance().registerCreator("swap", SwapCreator);

Command *RotCreator(std::string::iterator &it,
                    const std::string::iterator &end) {
  return new Rot();
}
bool rotCmd =
    Interpreter::getInstance().registerCreator("rot", RotCreator);

Command *OverCreator(std::string::iterator &it,
                     const std::string::iterator &end) {
  return new Over();
}
bool overCmd =
    Interpreter::getInstance().registerCreator("over", OverCreator);

Command *EmitCreator(std::string::iterator &it,
                     const std::string::iterator &end) {
  return new Emit();
}
bool emitCmd =
    Interpreter::getInstance().registerCreator("emit", EmitCreator);

Command *CRCreator(std::string::iterator &it,
                   const std::string::iterator &end) {
  return new CR();
}
bool crCmd =
    Interpreter::getInstance().registerCreator("cr", CRCreator);

Command *GreaterCreator(std::string::iterator &it,
                        const std::string::iterator &end) {
  return new Over();
}
bool greaterCmd =
    Interpreter::getInstance().registerCreator(">", GreaterCreator);

Command *LessCreator(std::string::iterator &it,
                     const std::string::iterator &end) {
  return new Over();
}
bool lessCmd =
    Interpreter::getInstance().registerCreator("<", LessCreator);

Command *EqualCreator(std::string::iterator &it,
                      const std::string::iterator &end) {
  return new Over();
}

} // namespace
