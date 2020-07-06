#ifndef MHL_EXCEPTION_UNITTESTEXCEPTION_H_
#define MHL_EXCEPTION_UNITTESTEXCEPTION_H_

#include <stdexcept>

namespace mhl {

// 使い方
// std::shared_ptr<mh_library::IOutputConsole> console(new
// mh_library::OutputConsole());
// // UnitTestExceptionTest
// try {
//   int value = 1000;
//   if (value > 10) {
//     // パラメータエラーが起こったと仮定して例外をスロー
//     throw mh_library::UnitTestException("value error", 1);
//   }
// }
// catch (const mh_library::UnitTestException& e) {
//   // e.what()でメッセージを出力
//   console->PrintLine(e.what());
// }

// 単体テスト用の例外クラス
class UnitTestException : public std::runtime_error {
 public:
  UnitTestException(const std::string& message, int error_code);

  virtual ~UnitTestException();

  int GetResult() { return error_code_; }

 private:
  int error_code_;  // エラーコード情報
};

}  // namespace mhl

#endif  // MHL_EXCEPTION_UNITTESTEXCEPTION_H_
