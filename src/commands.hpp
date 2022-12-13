#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "interpretererror.hpp"
#include "mystack.hpp"

struct Context {
  std::string inputStr;
  std::stringstream ssOutput;
  MyStack stackCntxt;
};

class Command {
public:
  virtual void apply(Context &cont) = 0;
  virtual ~Command() {}
};

// makes an addition of two top numbers, removes them from the stack and puts
// the result on the top
class Add : public Command {
public:
  void apply(Context &cont) override {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }
    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int sum = first + second;
    cont.stackCntxt.push(sum);
  }
};

//class BinaryOp: public Command {
//    void apply(Context &cont) override {
//      this(first, second);
//    }
//
//    virtual int operator()(int a, int b) = 0;
//
//};

// makes a subtraction of two top numbers, removes them from the stack and puts
// the result on the top
class Sub : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }
    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int sub = second - first;
    cont.stackCntxt.push(sub);
  }
};

// makes a multiplication of two top numbers, removes them from the stack and puts
// the result on the top
class Mult : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }
    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int mul = first * second;
    cont.stackCntxt.push(mul);
  }
};

// makes a division of two top numbers, removes them from the stack and puts
// the result on the top
class Div : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }
    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    if (second == 0) {
      throw InterpreterError("Error: division by zero");
    }
    cont.stackCntxt.pop();

    int div = second / first;
    cont.stackCntxt.push(div);
  }
};

// counts a remainder of the division of two top numbers, removes them from the stack and puts the
// result on the top
class Mod : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }
    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    if (second == 0) {
      throw InterpreterError("Error: division by zero");
    }
    cont.stackCntxt.pop();

    int mod = second % first;
    cont.stackCntxt.push(mod);
  }
};

// copies top number and put a copy on stack over top
class Dup : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.empty()) {
      throw InterpreterError("Too few arguments on stack");
    }
    int copyTop = cont.stackCntxt.top();
    cont.stackCntxt.push(copyTop);
  }
};

// removes top number from the stack
class Drop : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.empty()) {
      throw InterpreterError("Too few arguments on stack");
    }
    cont.stackCntxt.pop();
  }
};

// writes the top of stack and removes it from stack
class Write : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.empty()) {
      throw InterpreterError("Too few arguments on stack");
    }

    int topNum = cont.stackCntxt.top();
    cont.stackCntxt.pop();
    cont.ssOutput << topNum << "\n";
  }
};

// rotates the third number in stack to top
class Rot : public Command {
public:
  void apply(Context &cont) {

    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int third = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    cont.stackCntxt.push(first);
    cont.stackCntxt.push(second);
    cont.stackCntxt.push(third);
  }
};

// copies the second number and puts it over the top
class Over : public Command {
public:
  void apply(Context &cont) {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }

    int firstCopy = cont.stackCntxt.top();
    cont.stackCntxt.push(firstCopy);
  }
};

// prints top number's ascii code and remove top number from stack
class Emit : public Command {
public:
  void apply(Context &cont) override {
    if (cont.stackCntxt.empty()) {
      throw InterpreterError("Too few arguments on stack");
    }

    int topStack = cont.stackCntxt.top();
    if ((topStack + '0' < 0) || (topStack + '0' > 255)) {
      throw InterpreterError("Out of ASCII code");
    }

    cont.ssOutput << topStack - '0' << " ";
    cont.stackCntxt.pop();
  }
};

// writes line break
class CR : public Command {
public:
  void apply(Context &cont) override { cont.ssOutput << "\n"; }
};

// logic operation '>' : if the second number on stack is greater than
// the top, push 1 on stack, otherwise push 0
class Greater : public Command {
public:
  void apply(Context &cont) override {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }

    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    if (first > second) {
      cont.stackCntxt.push(1);
    } else {
      cont.stackCntxt.push(0);
    }
  }
};

// logic operation '<' : if the second number on stack is less than
// the top, push 1 on stack, otherwise push 0
class Less : public Command {
public:
  void apply(Context &cont) override {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }

    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    if (first < second) {
      cont.stackCntxt.push(1);
    } else {
      cont.stackCntxt.push(0);
    }
  }
};

// logic operation '=' : if the first and second numbers on stack are
// equals, push 1 on stack, otherwise push 0
class Equal : public Command {
public:
  void apply(Context &cont) override {
    if (cont.stackCntxt.size() < 2) {
      throw InterpreterError("Too few arguments on stack");
    }

    int first = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    int second = cont.stackCntxt.top();
    cont.stackCntxt.pop();

    if (first == second) {
      cont.stackCntxt.push(1);
    } else {
      cont.stackCntxt.push(0);
    }
  }
};
 