#ifndef REVERSI_UTIL_ASSERT_H_
#define REVERSI_UTIL_ASSERT_H_

#include <string>

namespace reversi {

// 実装テスト用クラス
class Assert {
public:

	/**
	 * 値の比較結果がfalseだったときにmessageを出力してプログラム停止する
	 * @param expected 比較結果
	 * @param message  出力するメッセージ
	 */
	static void AssertEquals(bool expected, std::string message);

	/**
	 * 値の比較結果が0だったときにmessageを出力してプログラム停止する
	 * @param expected 比較結果
	 * @param message  出力するメッセージ
	 */
	static void AssertEquals(int expected, std::string message);

	/**
	 * 配列の範囲をチェックして超えていたときはmessageを出力してプログラムを停止する
	 * @param index   チェックをするindex
	 * @param maxSize 配列のサイズ
	 * @param message 出力するメッセージ
	 */
	static void AssertArrayRange(int index, int maxSize, std::string message);

private:

	/**
	 * メッセージを出力する
	 * @param message 出力するメッセージ
	 */
	static void Output(std::string message);

	/**
	 * コンソールにメッセージを出力する
	 * @param message 出力するメッセージ
	 */
	static void OutputConsole(std::string message);
};

}

#endif  // REVERSI_UTIL_ASSERT_H_
