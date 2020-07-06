#ifndef REVERSI_TEST_CODE_TESTDEVELOP_H_
#define REVERSI_TEST_CODE_TESTDEVELOP_H_

#include "../../../mhl/util/output/IOutputConsole.hpp"
#include "../base/UnitTestBase.h"

namespace reversi {

// 実装テスト用クラス
class TestDevelop : public UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestDevelop(mhl::IOutputConsole* outputConsole);

  /**
   * デストラクタ
   */
  virtual ~TestDevelop();

  /**
   * 実行
   * @return trueなら成功 falseなら失敗
   */
  bool Execute();

 private:
  mhl::IOutputConsole* console;
};
}  // namespace reversi

#endif  // REVERSI_TEST_CODE_TESTDEVELOP_H_
