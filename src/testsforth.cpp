#include <gtest/gtest.h>

#include "commands.hpp"
#include "interpreter.hpp"

TEST(CheckOK, PushOnePositiveNumber){
  Interpreter &i = Interpreter::GetInstance();
  Context cont;
  cont.inputStr = "1";    
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "< ok\n");

  cont.inputStr = "123415";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "< ok\n");
}

TEST(CheckOK, PushOneNegativeNumber){
  Interpreter &i = Interpreter::GetInstance();
  Context cont;
  cont.inputStr = "-1";    
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "< ok\n");

  cont.inputStr = "-12342315";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "< ok\n");
}

TEST(CheckOK, PushAmountOfPositiveNumbers){
    Interpreter &i = Interpreter::GetInstance();
    Context cont;
    cont.inputStr = "1 2 3 4 5 6 7 8 9";
    i.Interpret(cont);
    EXPECT_EQ(cont.ssOutput.str(), "< ok\n");
}

TEST(CheckOK, PushAmountOfNegativeNumbers){
    Interpreter &i = Interpreter::GetInstance();
    Context cont;
    cont.inputStr = "-1 -2 -3 -4 -5 -6 -7 -8 -9";
    i.Interpret(cont);
    EXPECT_EQ(cont.ssOutput.str(), "< ok\n");
}

TEST(Commands, CheckDotWriteCommand) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "1 .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "1\n");
  EXPECT_TRUE(cont.stackCntxt.empty());
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "-10 20 30 .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "30\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = ".";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "20\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = ".";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "-10\n");
  EXPECT_TRUE(cont.stackCntxt.empty());
}

TEST(CheckExceptions, TooFewElemsOnStackOneCommand) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;  
  
  cont.ssOutput.str(std::string());
  cont.inputStr = ".";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "+";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "-";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "*";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "/";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "mod";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "dup";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "drop";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "rot";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "over";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "emit";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
}

TEST(CheckExceptions, TooFewElemsOnStackMultipleCommands) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;
  
  cont.ssOutput.str(std::string());
  cont.inputStr = ". . . . . . .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "+ + + + + + +";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "- - - - - - - - -";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "* * * * * * * *";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "/ / / / / / /";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "mod mod mod mod mod mod mod";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");

 cont.ssOutput.str(std::string());
  cont.inputStr = "dup dup dup dup dup";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "drop drop drop drop drop";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "rot rot rot rot rot rot";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "over over over over over";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");
  
  cont.ssOutput.str(std::string());
  cont.inputStr = "emit emit emit emit emit";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Too few arguments on stack\n");  
}

TEST(Command, NotFound) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;  
  cont.inputStr = "fwerf";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "such command not found\n");
}

TEST(WriteString, BetweenTwoQuotes) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;  
  cont.inputStr = ".\" Hello from input!\"";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "Hello from input!\n");
}

TEST(WriteString, OneQuote) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;  
  cont.inputStr = ".\" Hello from input!";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "No closing quote\n");
}

TEST(WriteString, NotCorrectCommand) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;  
  cont.inputStr = ".\"Hello from input!";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "such command not found\n");
}


TEST(CheckArithm, MathCmdsWithPositiveNumbers) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;

  cont.ssOutput.str(std::string());
  cont.inputStr = "1 2 + .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "3\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "6 2 - .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "4\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "8 2 * .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "16\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "65 5 / .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "13\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "66 5 mod .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "1\n");
}

TEST(CheckArithm, MathCmdsWithNegativeNumbers) {
  Interpreter &i = Interpreter::GetInstance();
  Context cont;

  cont.ssOutput.str(std::string());
  cont.inputStr = "-1 -2 + .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "-3\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "-6 -2 - .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "-4\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "-8 2 * .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "-16\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "-65 5 / .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "-13\n");

  cont.ssOutput.str(std::string());
  cont.inputStr = "66 -5 mod .";
  i.Interpret(cont);
  EXPECT_EQ(cont.ssOutput.str(), "1\n");
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
