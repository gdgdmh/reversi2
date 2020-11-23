#include "output_console.hpp"

#include <iostream>

/**
 * コンストラクタ
 */
mhl::OutputConsole::OutputConsole() {}

/**
 * デストラクタ
 */
mhl::OutputConsole::~OutputConsole() {}

/**
 * 文字列を出力する
 */
void mhl::OutputConsole::Print(std::string string) { std::cout << string; }

/**
 * 改行付き文字列を出力する
 */
void mhl::OutputConsole::PrintLine(std::string string) {
  std::cout << string << std::endl;
}
