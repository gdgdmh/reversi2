#ifndef REVERSI_TEST_CODE_TEST2PERFORMANCECOUNTER_HPP_
#define REVERSI_TEST_CODE_TEST2PERFORMANCECOUNTER_HPP_

#include <memory>

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// パフォーマンスカウンタテストクラス
class TestPerformanceCounter : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestPerformanceCounter(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestPerformanceCounter();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST2PERFORMANCECOUNTER_HPP_
