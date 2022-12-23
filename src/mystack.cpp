#include "interpretererror.hpp"
#include "mystack.hpp"

size_t MyStack::size() const { return mystk_.size(); }

bool MyStack::empty() const { return mystk_.empty(); }

int MyStack::top() {
  if (mystk_.empty()) {
    throw InterpreterError("Too few arguments on stack");
  }
  return mystk_.top();
}

int MyStack::pop() {
  if (mystk_.empty()) {
    throw InterpreterError("Too few arguments on stack");
  }
  int number = mystk_.top();
  mystk_.pop();
  return number;
}

void MyStack::push(int toPush) { mystk_.push(toPush); }
