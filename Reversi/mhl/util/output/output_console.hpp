#ifndef MHL_UTIL_OUTPUT_OUTPUTCONSOLE_HPP_
#define MHL_UTIL_OUTPUT_OUTPUTCONSOLE_HPP_

#include <string>

#include "ioutput_console.hpp"

namespace mhl {

// コンソール出力クラス
class OutputConsole : public mhl::IOutputConsole {
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

}  // namespace mhl

#endif  // MH_LIBRARY_UTIL_OUTPUT_OUTPUTCONSOLE_HPP_
