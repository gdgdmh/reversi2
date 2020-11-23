#ifndef MHL_TEST_CODE_UTIL_OUTPUT_IOUTPUTCONSOLE_HPP_
#define MHL_TEST_CODE_UTIL_OUTPUT_IOUTPUTCONSOLE_HPP_

#include <string>

namespace mhl {

// コンソール出力のインターフェースクラス
class IOutputConsole {
 public:
  /**
   * デストラクタ
   */
  virtual ~IOutputConsole() {}

  /**
   * 文字列を出力する
   */
  virtual void Print(std::string string) = 0;

  /**
   * 改行付き文字列を出力する
   */
  virtual void PrintLine(std::string string) = 0;
};

}  // namespace mhl

#endif  // MH_LIBRARY_UTIL_OUTPUT_IOUTPUTCONSOLE_HPP_
