#include "UnitTestBase.h"

/**
 * コンストラクタ
 * @param outputConsole コンソール出力クラス
 */
reversi::UnitTestBase::UnitTestBase(mhl::IOutputConsole* outputConsole)
    : outputConsole(outputConsole) {}

/**
 * デストラクタ
 */
reversi::UnitTestBase::~UnitTestBase() {}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::UnitTestBase::Execute() { return true; }

/**
 * 条件のチェックの成否をチェックして失敗したときはメッセージを表示する
 * @param expected 条件チェックした値(0なら失敗とする)
 * @param message  失敗した際のメッセージ
 * @return          falseなら失敗
 */
bool reversi::UnitTestBase::AssertEqual(int expected, std::string message) {
  if (expected != 0) {
    // 正常
    return true;
  }
  if (outputConsole != NULL) {
    // 失敗しているのでメッセージを出力する
    // 後に__LINE__や__FILE__を追加することも考慮する
    outputConsole->PrintLine(message);
  }
  return false;
}
