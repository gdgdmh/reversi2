#ifndef REVERSI_TEST_CODE_TEST2REVERSI_HPP_
#define REVERSI_TEST_CODE_TEST2REVERSI_HPP_

#include <memory>

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// リバーシテストクラス
class Test2Reversi : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2Reversi(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2Reversi();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST2REVERSI_HPP_
