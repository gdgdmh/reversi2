#ifndef REVERSI_TEST_CODE_TESTTHINKINGNODE_H_
#define REVERSI_TEST_CODE_TESTTHINKINGNODE_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// 整数乱数生成テスト
class TestThinkingNode : public UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestThinkingNode(mhl::IOutputConsole* outputConsole);

  /**
   * デストラクタ
   */
  virtual ~TestThinkingNode();

  /**
   * 実行
   * @return trueなら成功 falseなら失敗
   */
  bool Execute();
};

}  // namespace reversi

#endif  // REVERSI_TEST_CODE_TESTTHINKINGNODE_H_
