#ifndef REVERSI_UTIL_OUTPUTCONSOLE_H_
#define REVERSI_UTIL_OUTPUTCONSOLE_H_

#include <string>
#include "./IOutputConsole.h"

namespace reversi {

// コンソール出力クラス
class OutputConsole : public reversi::IOutputConsole {
public:
	/**
	 * コンストラクタ
	 */
	OutputConsole();

	/**
	 * デストラクタ
	 */
	virtual ~OutputConsole();

	/**
	 * 文字列を出力する
	 */
	void Print(std::string string);

	/**
	 * 改行付き文字列を出力する
	 */
	void PrintLine(std::string string);
};

}

#endif  // REVERSI_UTIL_OUTPUTCONSOLE_H_
