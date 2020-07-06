#ifndef MH_LIBRABY_TEST_UNITTESTBASE_H_
#define MH_LIBRABY_TEST_UNITTESTBASE_H_

#include <memory>
#include <string>

#include "../exception/UnitTestException.hpp"
#include "../util/output/IOutputConsole.hpp"
#include "../util/string/StdStringFormatter.hpp"

namespace mhl {

// 単体テスト用のベースクラス
class UnitTestBase {
 public:
  // アサーションマクロ定義
#ifdef NDEBUG
#define AssertEquals(expected, msg)
#else
/**
 * 条件のチェックの成否をチェックして失敗したときはメッセージを表示して例外をスローする
 * @param  expected 条件チェックした値(0なら失敗とする)
 * @param  msg      失敗した際のメッセージ
 */
#define AssertEquals(expected, msg)                                           \
  if (!(expected)) {                                                          \
    std::string msg1 =                                                        \
        mhl::StdStringFormatter::Format("UnitTestBase Assert %s ", (#msg));   \
    std::string msg2 = mhl::StdStringFormatter::Format("file %s ", __FILE__); \
    std::string msg3 =                                                        \
        mhl::StdStringFormatter::Format("function %s ", __FUNCTION__);        \
    std::string msg4 = mhl::StdStringFormatter::Format("line %d ", __LINE__); \
    throw mhl::UnitTestException(msg1 + msg2 + msg3 + msg4, 0);               \
  }
#endif

 public:
  /**
   * コンストラクタ
   * @param outputConsole コンソール出力クラス
   */
  UnitTestBase(std::shared_ptr<mhl::IOutputConsole> output_console)
      : output_console_(output_console) {}

  /**
   * デストラクタ
   */
  virtual ~UnitTestBase() {}

  /**
   * 実行
   */
  virtual void ExecuteUnitTest() = 0;

 protected:
  std::shared_ptr<mhl::IOutputConsole> output_console_;  // コンソール出力
};

}  // namespace mhl

#endif  // MH_LIBRABY_TEST_UNITTESTBASE_H_
