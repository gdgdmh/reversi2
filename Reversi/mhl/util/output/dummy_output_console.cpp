#include "dummy_output_console.hpp"

#include <iostream>

/**
 * コンストラクタ
 */
mhl::DummyOutputConsole::DummyOutputConsole() {}

/**
 * デストラクタ
 */
mhl::DummyOutputConsole::~DummyOutputConsole() {}

/**
 * 文字列を出力する(ダミーなので出力はしない)
 */
void mhl::DummyOutputConsole::Print(std::string string) {}

/**
 * 改行付き文字列を出力する(ダミーなので出力はしない)
 */
void mhl::DummyOutputConsole::PrintLine(std::string string) {}
