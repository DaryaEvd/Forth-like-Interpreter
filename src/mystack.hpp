#pragma once
#include <stack>

class MyStack{
  public:
    size_t size() const;
    bool empty() const;

    int top();

    int pop();
    
    void push(int toPush);

  private:
    std::stack<int> mystk_;
};
