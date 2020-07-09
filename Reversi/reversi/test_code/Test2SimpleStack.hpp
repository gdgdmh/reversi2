#ifndef REVERSI_TEST_CODE_TEST2SIMPLESTACK_HPP_
#define REVERSI_TEST_CODE_TEST2SIMPLESTACK_HPP_

#include <memory>

#include "../../mhl/test/UnitTestBase.hpp"

namespace test_code {

// スタックテスト
class Test2SimpleStack : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2SimpleStack(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2SimpleStack();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST2SIMPLESTACK_HPP_
