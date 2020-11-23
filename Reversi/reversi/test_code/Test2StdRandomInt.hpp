#ifndef REVERSI_TEST_CODE_TEST2STDRANDOMINT_HPP_
#define REVERSI_TEST_CODE_TEST2STDRANDOMINT_HPP_

#include <memory>

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// 整数乱数生成テスト
class Test2StdRandomInt : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2StdRandomInt(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2StdRandomInt();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST2STDRANDOMINT_HPP_
