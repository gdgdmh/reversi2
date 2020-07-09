#include "Test2SimpleArray.hpp"

#include "../util/SimpleArray.h"

/**
 * コンストラクタ
 */
test_code::Test2SimpleArray::Test2SimpleArray(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2SimpleArray::~Test2SimpleArray() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2SimpleArray::ExecuteUnitTest() {
  // PushBackとAtをチェック
  {
    const int STACK_SIZE = 10;
    reversi::SimpleArray<int> simpleArray(STACK_SIZE);

    for (int i = 0; i < STACK_SIZE; ++i) {
      simpleArray.PushBack(i);
    }
    AssertEquals(simpleArray.GetSize() == STACK_SIZE,
                 "TestSimpleArray::Execute size invalid");
    for (int i = (STACK_SIZE - 1); i >= 0; --i) {
      int data = simpleArray.At(i);
      AssertEquals(data == i, "TestSimpleArray::Execute At value invalid");
    }

    // 書き換え
    const int TEST_INDEX = 5;
    const int VALUE = 20;
    simpleArray.At(TEST_INDEX) = VALUE;
    AssertEquals(simpleArray.At(TEST_INDEX) == VALUE,
                 "TestSimpleArray::Execute At overwrite value invalid");
  }
}
