#include <iostream>
#include "ConsoleInputKeyboard.h"

/**
 * コンストラクタ
 */
reversi::ConsoleInputKeyboard::ConsoleInputKeyboard() {
}

/**
 * デストラクタ
 */
reversi::ConsoleInputKeyboard::~ConsoleInputKeyboard() {
}

/**
 * 1行単位での文字列入力を取る
 * @return 取得した文字列
 */
std::string reversi::ConsoleInputKeyboard::GetStringLine() {
	std::string inputString;
	// コンソールから入力を取る
	std::getline(std::cin, inputString);
	return inputString;
}
