#ifndef REVERSI_TEST_CODE_TESTBOARD_H_
#define REVERSI_TEST_CODE_TESTBOARD_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// 盤テストクラス
class TestBoard : public UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestBoard(mhl::IOutputConsole* outputConsole);

  /**
   * デストラクタ
   */
  virtual ~TestBoard();

  /**
   * 実行
   * @return trueなら成功 falseなら失敗
   */
  bool Execute();
};

}  // namespace reversi

#endif  // REVERSI_TEST_CODE_TESTBOARD_H_
