#include "mystack.hpp"
#include "interpretererror.hpp"

size_t MyStack::size() const { return mystk_.size(); }

bool MyStack::empty() const { return mystk_.empty(); }

int MyStack::top() {
  return mystk_.top();
}

int MyStack::pop() {
  int number = mystk_.top();
  mystk_.pop();
  return number;
}

void MyStack::push(int toPush) { mystk_.push(toPush); }
