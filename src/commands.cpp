#include <algorithm>
#include <iostream>

#include "commands.hpp"
#include "interpretererror.hpp"

void BinaryOp::apply(Context &cont) {
  int first = cont.stackCntxt.pop();
  int second = cont.stackCntxt.pop();
  cont.stackCntxt.push(this->makeBinOp(first, second));
}

int Add::makeBinOp(int first, int second) { return first + second; }

int Sub::makeBinOp(int first, int second) { return second - first; }

int Mult::makeBinOp(int first, int second) { return first * second; }

int Div::makeBinOp(int first, int second) {
  if (first == 0) {
    throw InterpreterError("Error: division by zero");
  }
  return second / first;
}

int Mod::makeBinOp(int first, int second) {
  if (first == 0) {
    throw InterpreterError("Error: division by zero");
  }
  return second % first;
}

void Dup::apply(Context &cont) {
  if (cont.stackCntxt.empty()) {
    throw InterpreterError("Too few arguments on stack");
  }
  int copyTop = cont.stackCntxt.top();
  cont.stackCntxt.push(copyTop);
};

void Drop::apply(Context &cont) {
  if (cont.stackCntxt.empty()) {
    throw InterpreterError("Too few arguments on stack");
  }
  cont.stackCntxt.pop();
};

void Write::apply(Context &cont) {
  if (cont.stackCntxt.empty()) {
    throw InterpreterError("Too few arguments on stack");
  }
  int topNum = cont.stackCntxt.pop();
  cont.ssOutput << topNum << "\n";
};

void Swap::apply(Context &cont) {
  if (cont.stackCntxt.size() < 2) {
    throw InterpreterError("Too few arguments on stack");
  }
  int fisrt = cont.stackCntxt.pop();
  int second = cont.stackCntxt.pop();

  cont.stackCntxt.push(fisrt);
  cont.stackCntxt.push(second);
}

void Rot::apply(Context &cont) {

  int first = cont.stackCntxt.pop();
  int second = cont.stackCntxt.pop();
  int third = cont.stackCntxt.pop();

  cont.stackCntxt.push(first);
  cont.stackCntxt.push(second);
  cont.stackCntxt.push(third);
};

void Over::apply(Context &cont) {
  if (cont.stackCntxt.size() < 2) {
    throw InterpreterError("Too few arguments on stack");
  }

  int firstCopy = cont.stackCntxt.pop();
  int secondCopy = cont.stackCntxt.pop();
  cont.stackCntxt.push(firstCopy);
  cont.stackCntxt.push(secondCopy);
};

void Emit::apply(Context &cont) {
  if (cont.stackCntxt.empty()) {
    throw InterpreterError("Too few arguments on stack");
  }

  int topStack = cont.stackCntxt.pop();
  if ((topStack + '0' < 0) || (topStack + '0' > 255)) {
    throw InterpreterError("Out of ASCII code");
  }

  cont.ssOutput << topStack - '0' << " ";
}

void CR::apply(Context &cont) { cont.ssOutput << "\n"; }

void Greater::apply(Context &cont) {
  if (cont.stackCntxt.size() < 2) {
    throw InterpreterError("Too few arguments on stack");
  }

  int rightOperand = cont.stackCntxt.pop();
  int leftOperand = cont.stackCntxt.pop();

  cont.stackCntxt.push(leftOperand > rightOperand);
};

void Less::apply(Context &cont) {
  if (cont.stackCntxt.size() < 2) {
    throw InterpreterError("Too few arguments on stack");
  }

  int rightOperand = cont.stackCntxt.pop();
  int leftOperand = cont.stackCntxt.pop();

  cont.stackCntxt.push(leftOperand < rightOperand);
};

void Equal::apply(Context &cont) {
  if (cont.stackCntxt.size() < 2) {
    throw InterpreterError("Too few arguments on stack");
  }

  int rightOperand = cont.stackCntxt.pop();
  int leftOperand = cont.stackCntxt.pop();

  cont.stackCntxt.push(rightOperand == leftOperand);
};

void BetweenQuotes::apply(Context &cont) {

  // std::cout << "before while: " << *(cont.it) << ";" << std::endl;
  if (cont.it == cont.endCnt) {
    // std::cout << "from forst if" << std::endl;
    throw InterpreterError("incorrect input");
  }
  while (cont.it != cont.endCnt) {
    // std::cout << "cont.it:" << *(cont.it) << std::endl;
    // std::cout << "cont.it + 1:" << *(cont.it + 1) << std::endl;
    // while (std::isspace(*cont.it)) {
    //   cont.it++;
    // }
    // if (*cont.it == '.' && *(cont.it + 1) == '\"') {
    //   cont.it = cont.it + 2; //skip . and "
    //   std::cout << "dot qoute" << std::endl;
    // }
    // std::cout << "after jumping: " << *(cont.it) << ";" <<
    // std::endl;
    if (!std::isspace(*(cont.it))) {
      //std::cout << "!isspace:" << *cont.it << std::endl;
      throw InterpreterError("no closing quote");
    }
    cont.it++;
    auto firstSymbol = cont.it;

    auto isQuote = [](char i) { return i == '\"'; };
    std::string::iterator quoteIter =
        std::find_if(cont.it, cont.endCnt, isQuote);
   
    if (quoteIter == cont.endCnt) {
      // std::cout << "quoteIter == cont.endCnt:" << *cont.it
      //           << std::endl;
      throw InterpreterError("no closing quote");
    }
    std::string toPrint(firstSymbol, quoteIter);
    cont.ssOutput << toPrint << '\n';

    cont.it = quoteIter;
    break;

    // 1 2 + ." esrewp" 3 4 + .
    // std::cout << "cont.endCnt before ==" << *cont.endCnt << ";"
    //           << std::endl;
    // std::cout << "quoteIter before ==" << *quoteIter << ";"
    //           << std::endl;
    // if (quoteIter == cont.endCnt) {
    //   std::cout << "quoteIter == cont.endCnt:" << *cont.it <<
    //   std::endl; throw InterpreterError("no closing quote");
    // }
    // std::string toPrint(firstSymbol, quoteIter);
    // cont.ssOutput << toPrint << '\n';

    // cont.it = quoteIter + 1;

    // if (cont.it == cont.endCnt) {
    //   std::cout << "hello from break" << std::endl;
    //   break;
    // }
    // cont.it++;
  }
};
