#include "TestSimpleArray.h"
// test
#include "../../util/Assert.h"
#include "../../util/SimpleArray.h"

/**
 * コンストラクタ
 */
reversi::TestSimpleArray::TestSimpleArray(mhl::IOutputConsole* outputConsole)
    : UnitTestBase(outputConsole) {}

/**
 * デストラクタ
 */
reversi::TestSimpleArray::~TestSimpleArray() {}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestSimpleArray::Execute() {
  // PushBackとAtをチェック
  {
    const int STACK_SIZE = 10;
    reversi::SimpleArray<int> simpleArray(STACK_SIZE);

    for (int i = 0; i < STACK_SIZE; ++i) {
      simpleArray.PushBack(i);
    }
    if (!AssertEqual(simpleArray.GetSize() == STACK_SIZE,
                     "TestSimpleArray::Execute size invalid")) {
      return false;
    }
    for (int i = (STACK_SIZE - 1); i >= 0; --i) {
      int data = simpleArray.At(i);
      if (!AssertEqual(data == i,
                       "TestSimpleArray::Execute At value invalid")) {
        return false;
      }
    }

    // 書き換え
    const int TEST_INDEX = 5;
    const int VALUE = 20;
    simpleArray.At(TEST_INDEX) = VALUE;
    if (!AssertEqual(simpleArray.At(TEST_INDEX) == VALUE,
                     "TestSimpleArray::Execute At overwrite value invalid")) {
      return false;
    }
  }
  return true;
}
