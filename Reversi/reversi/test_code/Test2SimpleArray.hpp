#ifndef REVERSI_TEST_CODE_TEST2SIMPLEARRAY_HPP_
#define REVERSI_TEST_CODE_TEST2SIMPLEARRAY_HPP_

#include <memory>

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// 動的配列テスト
class Test2SimpleArray : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2SimpleArray(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2SimpleArray();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST2SIMPLEARRAY_HPP_
