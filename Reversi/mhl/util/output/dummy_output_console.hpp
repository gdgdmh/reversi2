#ifndef MHL_UTIL_OUTPUT_DUMMYOUTPUTCONSOLE_HPP_
#define MHL_UTIL_OUTPUT_DUMMYOUTPUTCONSOLE_HPP_

#include <string>

#include "ioutput_console.hpp"

namespace mhl {

// ダミーコンソール出力クラス
class DummyOutputConsole : public mhl::IOutputConsole {
 public:
  /**
   * コンストラクタ
   */
  DummyOutputConsole();

  /**
   * デストラクタ
   */
  virtual ~DummyOutputConsole();

  /**
   * 文字列を出力する(ダミーなので出力はしない)
   */
  void Print(std::string string);

  /**
   * 改行付き文字列を出力する(ダミーなので出力はしない)
   */
  void PrintLine(std::string string);
};

}  // namespace mhl

#endif  // MHL_UTIL_OUTPUT_DUMMYOUTPUTCONSOLE_HPP_
