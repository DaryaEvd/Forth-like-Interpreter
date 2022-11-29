#pragma once

#include <iostream>

#include "interpretererror.hpp"
#include "mystack.hpp"

class Command {
  public:
  virtual void apply(MyStack &stk_) = 0;
  virtual ~Command(){};
};

// makes an addition of two top numbers and puts the result on the top
class Add : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.top();
    int second = stk_.top();
    int sum = first + second;
    stk_.push(sum);
  }
};

// makes a subtraction of two top numbers and puts the result on the
// top
class Sub : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.top();
    int second = stk_.top();
    int sub = first - second;
    stk_.push(sub);
  }
};

// makes a multiplication of two top numbers and puts the result on
// the top
class Mul : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.top();
    int second = stk_.top();
    int mul = first * second;
    stk_.push(mul);
  }
};

// makes a division of two top numbers and puts the result on the top
class Div : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.top();
    int second = stk_.top();
    if (second == 0) {
      throw interpreterError("division by zero");
    }
    int sub = first / second;
    stk_.push(sub);
  }
};

// counts a remainder of the division of two top numbers and puts the
// result on the top
class Mod : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.top();
    int second = stk_.top();
    int result = first % second;
  }
};

// copies top of stack and puts it on stack
class Dup : public Command {
  public:
  void apply(MyStack &stk_) override {
    int copyOfTop = stk_.peek();
    stk_.push(copyOfTop);
  }
};

// removes top of stack
class Drop : public Command {
  public:
  void apply(MyStack &stk_) override { stk_.pop(); }
};

// writes the top of stack and removes it from stack
class WriteDot : public Command {
  public:
  void apply(MyStack &stk_) override {
    int topOfStack = stk_.top();
    std::cout << topOfStack << std::endl;
    stk_.pop();
  }
};

// switches the order of the top two numbers on stack
class Swap : public Command {
  public:
  void apply(MyStack &stk_) override {
    int topOfStack = stk_.top();
    int afterTop = stk_.top();

    stk_.push(topOfStack);
    stk_.push(afterTop);
  }
};

// rotates the third number in stack to top
class Rot : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 3) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.top();
    int second = stk_.top();
    int third = stk_.top();

    stk_.push(first);
    stk_.push(third);
    stk_.push(second);
  }
};

// copies the second number and puts it to top
class Over : public Command {
  public:
  void apply(MyStack &stk_) override {
    int first = stk_.top();
    int second = stk_.peek();

    stk_.push(first);
    stk_.push(second);
  }
};

// prints top number's ascii code and remove it from stack
class Emit : public Command {
  public:
  void apply(MyStack &stk_) override {
    int topOfStack = stk_.peek();
    // if ((topOfStack + '0') < 0 || (topOfStack + '0') > 255) {
    //   throw interpreterError("No ascii code");
    // }
    std::cout << (topOfStack + '0') << std::endl;
    stk_.pop();
  }
};

// writes line break
class CR : public Command {
  public:
  void apply(MyStack &stk_) override {
    std::cout << "\n" << std::endl;
  }
};

// logic operation '>' : if the first number on stack is greater than
// the second, push 1 on stack, otherwise push 0
class Greater : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.peek();
    int second = stk_.peek();
    if (first > second) {
      std::cout << 1 << std::endl;
      stk_.push(1);
    } else {
      std::cout << 0 << std::endl;
      stk_.push(0);
    }
  }
};

// logic operation '<' : if the first number on stack is less than the
// second, push 1 on stack, otherwise push 0
class Less : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.peek();
    int second = stk_.peek();
    if (first < second) {
      std::cout << 1 << std::endl;
      stk_.push(1);
    } else {
      std::cout << 0 << std::endl;
      stk_.push(0);
    }
  }
};

// logic operation '=' : if the first and second numbers on stack are
// equals, push 1 on stack, otherwise push 0
class Equal : public Command {
  public:
  void apply(MyStack &stk_) override {
    if (stk_.size() < 2) {
      throw interpreterError("too few arguments on stack");
    }
    int first = stk_.peek();
    int second = stk_.peek();
    if (first == second) {
      std::cout << 1 << std::endl;
      stk_.push(1);
    } else {
      std::cout << 0 << std::endl;
      stk_.push(0);
    }
  }
};
