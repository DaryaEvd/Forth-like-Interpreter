#pragma once
#include <stack>

class MyStack {
  public:

  //counts amount of elements in stack
  size_t size(){
    return stack_.size();
  }

  bool empty(){
    return stack_.empty();
  }

  //returns the top number on the stack and removes it 
  int top() {
    if (stack_.empty()){
      throw interpreterError("too few arguments on stack");
    }
    int topOfStack = stack_.top();
    stack_.pop();
    return topOfStack;
  }
  
  //returns top number on the stack (doesn't remove it)
  int peek(){
    if (stack_.empty()){
      throw interpreterError("too few arguments on stack");
    }
    return stack_.top();
  }

  //puts a number of the top of the stack
  void push(int toPush) { stack_.push(toPush); }

  //removes top number from the stack
  void pop() { 
    if (stack_.empty()){
      throw interpreterError("too few arguments on stack");
    }
    stack_.pop(); 
  }
  
  private:
  std::stack<int> stack_;
};
