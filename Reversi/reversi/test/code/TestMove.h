#ifndef REVERSI_TEST_CODE_TESTMOVE_H_
#define REVERSI_TEST_CODE_TESTMOVE_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// 着手テストクラス
class TestMove : public UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestMove(mhl::IOutputConsole* outputConsole);

  /**
   * デストラクタ
   */
  virtual ~TestMove();

  /**
   * 実行
   * @return trueなら成功 falseなら失敗
   */
  bool Execute();
};

}  // namespace reversi

#endif  // REVERSI_TEST_CODE_TESTMOVE_H_
