#pragma once

#include <sstream>

#include "mystack.hpp"

struct Context {
  MyStack &stackCntxt;
  std::string::iterator &it;
  const std::string::iterator &endCnt;
  std::stringstream ssOutput;

  Context(MyStack &stackCntxt, std::string::iterator &it,
          const std::string::iterator &endCnt)
      : stackCntxt(stackCntxt), it(it), endCnt(endCnt) {}
};

class Command {
public:
  virtual void apply(Context &cont) = 0;
  virtual ~Command() {}
};

class BinaryOp : public Command {
  void apply(Context &cont) override;

  // virtual int operator()(int a, int b) = 0;
  virtual int makeBinOp(int num1, int num2) = 0;
};

// makes an addition of two top numbers, removes them from the stack
// and puts the result on the top
class Add : public BinaryOp {
public:
  int makeBinOp(int num1, int num2) override;
};

// makes a subtraction of two top numbers, removes them from the stack
// and puts the result on the top
class Sub : public BinaryOp {
public:
  // void apply(Context &cont) override;
  int makeBinOp(int num1, int num2) override;
};

// makes a multiplication of two top numbers, removes them from the
// stack and puts the result on the top
class Mult : public BinaryOp {
public:
  // void apply(Context &cont) override;
  int makeBinOp(int num1, int num2) override;
};

// makes a division of two top numbers, removes them from the stack
// and puts the result on the top
class Div : public BinaryOp {
public:
  // void apply(Context &cont) override;
  int makeBinOp(int num1, int num2) override;
};

// counts a remainder of the division of two top numbers, removes them
// from the stack and puts the result on the top
class Mod : public BinaryOp {
public:
  // void apply(Context &cont) override;
  int makeBinOp(int num1, int num2) override;
};

// copies top number and puts a copy on stack over top
class Dup : public Command {
public:
  void apply(Context &cont) override;
};

// removes top number from the stack
class Drop : public Command {
public:
  void apply(Context &cont) override;
};

// writes the top of stack and removes it from stack
class Write : public Command {
public:
  void apply(Context &cont) override;
};

//  swaps the first and the second numbers on stack
class Swap : public Command {
public:
  void apply(Context &cont) override;
};

// rotates the third number in stack to top
class Rot : public Command {
public:
  void apply(Context &cont) override;
};

// copies the second number and puts it over the top
class Over : public Command {
public:
  void apply(Context &cont) override;
};

// prints top number's ascii code and removes top number from stack
class Emit : public Command {
public:
  void apply(Context &cont) override;
};

// writes line break
class CR : public Command {
public:
  void apply(Context &cont) override;
};

// logic operation '>' : if the second number on stack is greater than
// the top, push 1 on stack, otherwise push 0
class Greater : public Command {
public:
  void apply(Context &cont) override;
};

// logic operation '<' : if the second number on stack is less than
// the top, push 1 on stack, otherwise push 0
class Less : public Command {
public:
  void apply(Context &cont) override;
};

// logic operation '=' : if the first and second numbers on stack are
// equals, push 1 on stack, otherwise push 0
class Equal : public Command {
public:
  void apply(Context &cont) override;
};

// prints a content between ." " (quotes are not included in printing)
class BetweenQuotes : public Command {
public:
  void apply(Context &cont) override;
};
