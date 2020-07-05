#ifndef REVERSI_UTIL_IOUTPUTCONSOLE_H_
#define REVERSI_UTIL_IOUTPUTCONSOLE_H_

#include <string>

namespace reversi {

// コンソール出力のインターフェースクラス
class IOutputConsole {
public:

	/**
	 * デストラクタ
	 */
	virtual ~IOutputConsole() {
	}

	/**
	 * 文字列を出力する
	 */
	virtual void Print(std::string string) = 0;

	/**
	 * 改行付き文字列を出力する
	 */
	virtual void PrintLine(std::string string) = 0;
};

}

#endif  // REVERSI_UTIL_IOUTPUTCONSOLE_H_
