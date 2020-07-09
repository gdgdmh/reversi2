#ifndef REVERSI_TEST_CODE_TESTREVERSICPU_HPP_
#define REVERSI_TEST_CODE_TESTREVERSICPU_HPP_

#include <memory>

#include "../../mhl/test/UnitTestBase.hpp"

namespace test_code {

// リバーシCPU連続対局テストクラス
class Test2ReversiCpu : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2ReversiCpu(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2ReversiCpu();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TESTREVERSICPU_HPP_
