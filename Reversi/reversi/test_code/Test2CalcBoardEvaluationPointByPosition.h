#ifndef REVERSI_TEST2_TESTCALCBOARDEVALUATIONPOINTBYPOSITION_H_
#define REVERSI_TEST2_TESTCALCBOARDEVALUATIONPOINTBYPOSITION_H_

#include "../../mhl/test/UnitTestBase.hpp"

namespace test_code {
class Test2CalcBoardEvaluationPointByPosition : public mhl::UnitTestBase {
 public:
  /**
   * @brief コンストラクタ
   *
   * @param output_console 出力クラス
   */
  Test2CalcBoardEvaluationPointByPosition(
      std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * @brief デストラクタ
   *
   */
  virtual ~Test2CalcBoardEvaluationPointByPosition();

  /**
   * @brief ユニットテストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST2_TESTCALCBOARDEVALUATIONPOINTBYPOSITION_H_
