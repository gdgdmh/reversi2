#include "Test2SimpleStack.hpp"

#include "../util/SimpleStack.h"

/**
 * コンストラクタ
 */
test_code::Test2SimpleStack::Test2SimpleStack(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2SimpleStack::~Test2SimpleStack() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2SimpleStack::ExecuteUnitTest() {
  // pushとpopの値とサイズをチェック
  {
    const int STACK_SIZE = 10;
    reversi::SimpleStack<int> stack(STACK_SIZE);

    for (int i = 0; i < STACK_SIZE; ++i) {
      stack.Push(i);
    }
    AssertEquals(stack.GetSize() == STACK_SIZE,
                 "TestSimpleStack::Execute size invalid");
    // 最後尾データをチェック
    AssertEquals(stack.Back() == (STACK_SIZE - 1),
                     "TestSimpleStack::Execute back invalid");
    for (int i = (STACK_SIZE - 1); i >= 0; --i) {
      int data = stack.Pop();
      AssertEquals(data == i, "TestSimpleStack::Execute pop value invalid");
      int stackSize = stack.GetSize();
      AssertEquals(stackSize == i,
                   "TestSimpleStack::Execute pop after size invalid");
    }
  }
}
