#ifndef REVERSI_TEST_CODE_TEST_REVERSI_PROJECT_HPP_
#define REVERSI_TEST_CODE_TEST_REVERSI_PROJECT_HPP_

#include <memory>

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// Reversiプロジェクト全体テストクラス
class TestReversiProject : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestReversiProject(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestReversiProject();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST_REVERSI_PROJECT_HPP_
