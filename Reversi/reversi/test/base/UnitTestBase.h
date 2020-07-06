#ifndef REVERSI_TEST_UNITTESTBASE_H_
#define REVERSI_TEST_UNITTESTBASE_H_

#include <string>

#include "../../../mhl/util/output/IOutputConsole.hpp"

namespace reversi {

// 単体テスト用のベースクラス
class UnitTestBase {
 public:
  /**
   * コンストラクタ
   * @param outputConsole コンソール出力クラス
   */
  UnitTestBase(mhl::IOutputConsole* outputConsole);

  /**
   * デストラクタ
   */
  virtual ~UnitTestBase();

  /**
   * 実行
   * @return trueなら成功 falseなら失敗
   */
  virtual bool Execute();

 protected:
  /**
   * 条件のチェックの成否をチェックして失敗したときはメッセージを表示する
   * メソッド内ではプログラム停止をしないので注意
   * @param expected 条件チェックした値(0なら失敗とする)
   * @param message  失敗した際のメッセージ
   * @return          falseなら失敗
   */
  bool AssertEqual(int expected, std::string message);

 protected:
  mhl::IOutputConsole* outputConsole;  // コンソール出力
};

}  // namespace reversi

#endif  // REVERSI_TEST_UNITTESTBASE_H_
