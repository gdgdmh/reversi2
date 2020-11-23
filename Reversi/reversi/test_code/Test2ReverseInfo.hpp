#ifndef REVERSI_TEST_CODE_TEST2REVERSEINFO_H_
#define REVERSI_TEST_CODE_TEST2REVERSEINFO_H_

#include <memory>

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// 裏返し情報テストクラス
class Test2ReverseInfo : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2ReverseInfo(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2ReverseInfo();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TESTREVERSEINFO_H_
