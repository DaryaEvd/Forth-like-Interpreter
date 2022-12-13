#pragma once
#include <stack>

#include "interpretererror.hpp"

class MyStack{
  public:
    size_t size() const {
      return mystk_.size();
    }

    bool empty() const {
      return mystk_.empty();
    }
    
    int top() {
      if(mystk_.empty()){
        throw InterpreterError("Too few arguments on stack");
      }
      return mystk_.top();
    }

    // CR: void -> int
    void pop() {
      if(mystk_.empty()){
        throw InterpreterError("Too few arguments on stack");
      }
      mystk_.pop();
    }

    void push(int toPush) {
      mystk_.push(toPush);
    }

  private:
    std::stack<int> mystk_;
};
