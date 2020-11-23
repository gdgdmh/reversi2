#ifndef REVERSI_TEST_CODE_TEST_MOVE2_HPP_
#define REVERSI_TEST_CODE_TEST_MOVE2_HPP_

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// 着手テストクラス
class Test2Move : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2Move(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2Move();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST_MOVE2_HPP_
