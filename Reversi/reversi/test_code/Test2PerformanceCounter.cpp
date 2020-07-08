#include "Test2PerformanceCounter.hpp"

#include "../../reversi/util/PerformanceCounter.h"

/**
 * コンストラクタ
 */
test_code::TestPerformanceCounter::TestPerformanceCounter(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::TestPerformanceCounter::~TestPerformanceCounter() {}

/**
 * @brief テストの実行
 *
 */
void test_code::TestPerformanceCounter::ExecuteUnitTest() {
  // 時間計測ができるか
  reversi::PerformanceCounter counter;
  counter.Start();
  // 少しだけ時間稼ぎ
  for (int i = 0; i < 1000; ++i) {
  }
  counter.End();
  double diff = counter.GetDiff();
  AssertEquals(diff > 0.0000000,
               "TestPerformanceCounter::Execute diff invalid");
}
