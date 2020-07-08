#ifndef REVERSI_TEST2_TESTBOARD_H_
#define REVERSI_TEST2_TESTBOARD_H_

#include "../../mhl/test/UnitTestBase.hpp"

namespace test_code {
class Test2Board : public mhl::UnitTestBase {
 public:
  /**
   * @brief コンストラクタ
   *
   * @param output_console 出力クラス
   */
  Test2Board(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * @brief デストラクタ
   *
   */
  virtual ~Test2Board();

  /**
   * @brief ユニットテストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test2

#endif  // REVERSI_TEST_CODE_TESTBOARD_H_
