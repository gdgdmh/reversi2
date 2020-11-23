#include "Assert.h"

#include "../../mhl/util/output/ioutput_console.hpp"
#include "../../mhl/util/output/output_console.hpp"
    //#include "../../mhl/util/output/OutputConsole.hpp"

/**
 * 値の比較結果がfalseだったときにmessageを出力してプログラム停止する
 * @param expected 比較結果
 * @param message  出力するメッセージ
 */
void reversi::Assert::AssertEqual(bool expected, std::string message) {
  if (expected == false) {
    Output(message);
    _ASSERT(false);
  }
}

/**
 * 値の比較結果が0だったときにmessageを出力してプログラム停止する
 * @param expected 比較結果
 * @param message  出力するメッセージ
 */
void reversi::Assert::AssertEqual(int expected, std::string message) {
  if (expected == 0) {
    Output(message);
    _ASSERT(false);
  }
}

/**
 * 配列の範囲をチェックして超えていたときはmessageを出力してプログラムを停止する
 * @param index   チェックをするindex
 * @param maxSize 配列のサイズ
 * @param message 出力するメッセージ
 */
void reversi::Assert::AssertArrayRange(int index, int maxSize,
                                       std::string message) {
  // indexの範囲(0～maxSize-1)に入っていない
  if ((index < 0) || (index >= maxSize)) {
    Output(message);
    _ASSERT(false);
  }
}

/**
 * メッセージを出力する
 * @param message 出力するメッセージ
 */
void reversi::Assert::Output(std::string message) { OutputConsole(message); }

/**
 * コンソールにメッセージを出力する
 * @param message 出力するメッセージ
 */
void reversi::Assert::OutputConsole(std::string message) {
  mhl::OutputConsole* output = new mhl::OutputConsole();
  output->PrintLine(message);
  if (output) {
    delete output;
    output = NULL;
  }
}
