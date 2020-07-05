#include "OutputConsole.h"
#include <iostream>

/**
 * コンストラクタ
 */
reversi::OutputConsole::OutputConsole() {
}

/**
 * デストラクタ
 */
reversi::OutputConsole::~OutputConsole() {
}

/**
 * 文字列を出力する
 */
void reversi::OutputConsole::Print(std::string string) {
	std::cout << string;
}

/**
 * 改行付き文字列を出力する
 */
void reversi::OutputConsole::PrintLine(std::string string) {
	std::cout << string << std::endl;
}
