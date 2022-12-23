#include <gtest/gtest.h>

#include "commands.hpp"
#include "interpreter.hpp"
#include "mystack.hpp"

TEST(NumberCheck, PushOnePositiveNumber) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1";
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "drop 12345 .";
  EXPECT_EQ(i.interpret(input), "12345\n");
}

TEST(NumberCheck, PushAmountPositiveNumbers) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 2 3 4 5 909090";
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "drop drop drop drop drop drop 12345 67879 1010101010 . . .";
  EXPECT_EQ(i.interpret(input), "1010101010\n67879\n12345\n");
}

TEST(NumberCheck, PushOneNegativeNumber) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "-1";
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "drop -12345 .";
  EXPECT_EQ(i.interpret(input), "-12345\n");
}
 
TEST(NumberCheck, PushAmountNegativeNumbers) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "-1 -2 -3 -4 -5 -909090";
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "drop drop drop drop drop drop -12345 -67879 -1010101010 . . .";
  EXPECT_EQ(i.interpret(input), "-1010101010\n-67879\n-12345\n");
}

TEST(NumberCheck, MaxMinNumbers) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "2147483647";
  EXPECT_EQ(i.interpret(input), "< ok\n");

  input = "drop -2147483648";
  EXPECT_EQ(i.interpret(input), "< ok\n");
}

TEST(NumberCheck, TooBigNumbers) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "drop 2147483648";
  EXPECT_EQ(i.interpret(input), "Out of bounds of int \n");

  input = "-2147483649";
  EXPECT_EQ(i.interpret(input), "Out of bounds of int \n");
}

TEST(NumberCheck, NumbersStartsWithZero) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "000000000001 .";
  EXPECT_EQ(i.interpret(input), "1\n");

  input = " -0000678 .";
  EXPECT_EQ(i.interpret(input), "-678\n");
}

TEST(BetweenQuotesCheck, OneQuoteNoContent) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\"";
  EXPECT_EQ(i.interpret(input), "Incorrect input\n");
}

TEST(BetweenQuotesCheck, OneQuoteAndContent) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\" hello";
  EXPECT_EQ(i.interpret(input), "No closing quote\n");
}

TEST(BetweenQuotesCheck, TwoQuotesAndContentBetween) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\" hello this is my first program\"";
  EXPECT_EQ(i.interpret(input), "hello this is my first program\n");
}

TEST(BetweenQuotesCheck, ContentWithAmountSpacesBetweenTwoQuotes) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\" hello                  .                     this is my first progra                      m\"";
  EXPECT_EQ(i.interpret(input), "hello                  .                     this is my first progra                      m\n");
}

TEST(BetweenQuotesCheck, BeforeOtherCmds) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = ".\" hello\" 3 4 + .";
  EXPECT_EQ(i.interpret(input), "hello\n7\n");
}

TEST(BetweenQuotesCheck, BetweenOtherCmds) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 2 3 + .\" hello\" 3 4 + .";
  EXPECT_EQ(i.interpret(input), "hello\n7\n");
}

TEST(BetweenQuotesCheck, AfterOtherCmds) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "drop 1 2 3 + . .\" hello\"";
  EXPECT_EQ(i.interpret(input), "5\nhello\n");
}

TEST(BetweenQuotesCheck, IncorrectStart) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "drop d.\"";
  EXPECT_EQ(i.interpret(input), "Such command not found\n");
}

TEST(CommandsCheck, CheckAdd) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "drop 1 2 +";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop 123 9 + .";
  EXPECT_EQ(i.interpret(input), "132\n");
 
  input = "457            -9                        + .";
  EXPECT_EQ(i.interpret(input), "448\n");
}

TEST(CommandsCheck, CheckSub) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2 -";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop -123               9 -                  .";
  EXPECT_EQ(i.interpret(input), "-132\n");
}

TEST(CommandsCheck, CheckMult) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2 *";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop -5 9 * .";
  EXPECT_EQ(i.interpret(input), "-45\n");

  input = "-50 -3 * .";
  EXPECT_EQ(i.interpret(input), "150\n");

  input = "-50                0 *                 .";
  EXPECT_EQ(i.interpret(input), "0\n");
}

TEST(CommandsCheck, CheckDiv) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2 /";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop -5 9 / .";
  EXPECT_EQ(i.interpret(input), "0\n");

  input = "-50 -5 / .";
  EXPECT_EQ(i.interpret(input), "10\n");

  input = "87           0                 / .";
  EXPECT_EQ(i.interpret(input), "Error: division by zero\n");
}

TEST(CommandsCheck, CheckMod) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2 mod";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop -56 9 mod .";
  EXPECT_EQ(i.interpret(input), "-2\n");

  input = "-50 -5 mod .";
  EXPECT_EQ(i.interpret(input), "0\n");

  input = "87             0 mod                   .";
  EXPECT_EQ(i.interpret(input), "Error: division by zero\n");
}

TEST(CommandsCheck, CheckDup) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2 dup";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop drop drop -56 9 dup . . .";
  EXPECT_EQ(i.interpret(input), "9\n9\n-56\n");

  input = "                            -50            -5 dup .     . .";
  EXPECT_EQ(i.interpret(input), "-5\n-5\n-50\n");
}

TEST(CommandsCheck, CheckDrop) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2 drop";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop -56 9 drop .";
  EXPECT_EQ(i.interpret(input), "-56\n");

  input = "      -47                   -50            -5 drop .    .";
  EXPECT_EQ(i.interpret(input), "-50\n-47\n");
}

TEST(CommandsCheck, CheckWrite) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2 .";
  EXPECT_EQ(i.interpret(input), "-2\n");
  
  input = "drop -56 9 . .";
  EXPECT_EQ(i.interpret(input), "9\n-56\n");

  input = "      -47      .             -50       . 23123     -5 .    .";
  EXPECT_EQ(i.interpret(input), "-47\n-50\n-5\n23123\n");
}

TEST(CommandsCheck, CheckSwap) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "1 -2      swap           ";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop drop -56 9 swap . .";
  EXPECT_EQ(i.interpret(input), "-56\n9\n");

  input = "45 -89 67 swap . swap .";
  EXPECT_EQ(i.interpret(input), "-89\n45\n");
}

TEST(CommandsCheck, CheckRot) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "drop 4 1 2 3  rot   ";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop drop drop drop 4 1 2 3  rot  . . .";
  EXPECT_EQ(i.interpret(input), "2\n1\n3\n");
}

TEST(CommandsCheck, CheckOver) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "drop 498 1 56 over ";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop drop drop drop 498 -1 56 over . . . ";
  EXPECT_EQ(i.interpret(input), "-1\n56\n-1\n");
}

TEST(CommandsCheck, CheckEmit) {
  Interpreter &i = Interpreter::getInstance();

  std::string input = "drop 498 -1 65 emit";
  EXPECT_EQ(i.interpret(input), "A\n");

  input = "drop drop 112 113 114 emit emit emit";
  EXPECT_EQ(i.interpret(input), "r\nq\np\n");

  input = "34785 emit";
  EXPECT_EQ(i.interpret(input), "Out of ASCII code\n");
}

TEST(CommandsCheck, CheckCR) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "498 1 56 cr";
  EXPECT_EQ(i.interpret(input), "\n");
}

TEST(CommandsCheck, CheckGreater) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "drop drop drop 498 1 56 > ";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop drop 498 -1 56 > .";
  EXPECT_EQ(i.interpret(input), "0\n");

  input = "drop 906 -89 -123 > .   .";
  EXPECT_EQ(i.interpret(input), "1\n906\n");
}

TEST(CommandsCheck, CheckLess) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "498 1 56 < ";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop drop 498 -1 56 < .";
  EXPECT_EQ(i.interpret(input), "1\n");

  input = "drop 47 -89 -123 < .     . ";
  EXPECT_EQ(i.interpret(input), "0\n47\n");
}

TEST(CommandsCheck, CheckEqual) {
  Interpreter &i = Interpreter::getInstance();
  std::string input = "498 1 56 = ";
  EXPECT_EQ(i.interpret(input), "< ok\n");
  
  input = "drop drop 498 -1 56 = .";
  EXPECT_EQ(i.interpret(input), "0\n");

  input = "drop 47 -89 -123 = .     . ";
  EXPECT_EQ(i.interpret(input), "0\n47\n");

  input = "62 78 78 = .";
  EXPECT_EQ(i.interpret(input), "1\n");

  input = "drop 47 -89 -89 = .     . ";
  EXPECT_EQ(i.interpret(input), "1\n47\n");
}

TEST(CommandsCheckException, CheckAdd) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop drop +";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 + ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop + 1 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckSub) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop -";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 - ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop - 1 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckMult) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop *";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 * ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop * 1 9 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckDiv) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop drop /";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 / ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop / 2 1 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckMod) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "mod";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 mod ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop mod 1";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckDup) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "dup";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "dup 176";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop dup 2 1 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckDrop) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop 567";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckWtite) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = ".";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = ". .             . .";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = ". 1 321 1 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckSwap) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "swap";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 swap";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop 1 swap 3 4 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckRot) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop rot";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 rot";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop 1 2 rot ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop drop 1 2 rot 3";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckOver) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop drop over";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 over";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "drop 1 over 2 ";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckEmit) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop emit";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "emit 1";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckGreater) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop >";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 > 123";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckLess) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop <";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 < 123";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CheckEqual) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "drop <";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");

  input = "1 = 123";
  EXPECT_EQ(i.interpret(input), "Too few arguments on stack\n");
}

TEST(CommandsCheckException, CmdNotExist) {
  Interpreter &i = Interpreter::getInstance();
  
  std::string input = "+hwaed";
  EXPECT_EQ(i.interpret(input), "Such command not found\n");

  input = "                  wer";
  EXPECT_EQ(i.interpret(input), "Such command not found\n");

  input = " 12 45 ==";
  EXPECT_EQ(i.interpret(input), "Such command not found\n");
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
