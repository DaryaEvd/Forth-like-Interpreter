#include <gtest/gtest.h>

#include "commands.hpp"
#include "interpreter.hpp"
#include "mystack.hpp"

TEST(NumberCheck, PushOnePositiveNumber) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "12345 .";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "12345\n");
}

TEST(NumberCheck, PushAmountPositiveNumber) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 2 3 4 5 909090";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "12345 67879 1010101010 . . .";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "1010101010\n67879\n12345\n");
}

TEST(NumberCheck, AnotherPushAmountPositiveNumber) { // delete
  Interpreter &i = Interpreter::getInstance();
  // std::string input = "1 2 3 4 5 6789";
  // i.interpret(input);
  // EXPECT_EQ(i.interpret(input), "< ok\n");

  std::string input = "12345 67879 1010101010 . . .";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "1010101010\n67879\n12345\n");
}

TEST(NumberCheck, PushOneNegativeNumber) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "12345 .";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "12345\n");
}
 
TEST(NumberCheck, MaxMinNumbers) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "2147483647";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "-2147483648";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "< ok\n");
}

TEST(ExceptionCheck, TooBigNumbers) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "2147483648";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "out of bounds of int \n");

  input = "-2147483649";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "out of bounds of int \n");
}

TEST(PrintCheck, NoContent) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\"";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "incorrect input\n");
}

TEST(PrintCheck, OneQuote) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\" hello";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "no closing quote\n");
}

TEST(PrintCheck, TwoQuotes) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\" hello this is my first program\"";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "hello this is my first program\n");
}

TEST(PrintCheck, AmountSpaces) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\" hello                  .                     this is my first progra                      m\"";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "hello                  .                     this is my first progra                      m\n");
}

TEST(PrintCheck, PrintWithNumbers) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 2 3 + .\" hello\" 3 4 + .";
  i.interpret(input);
  EXPECT_EQ(i.interpret(input), "hello\n7\n");
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
