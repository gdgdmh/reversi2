#ifndef MHL_TEST_CODE_TESTCALLBACKTEST_HPP_
#define MHL_TEST_CODE_TESTCALLBACKTEST_HPP_

#include <functional>
#include <memory>

#include "../test/unittest_base.hpp"

namespace test_program {

class CallbackInner {
 public:
  typedef std::function<void(uint32_t, uint32_t)> CallbackInnerComplete;

 public:
  CallbackInner();
  virtual ~CallbackInner();
  void Execute(CallbackInnerComplete callback);
};

class CallbackOuter {
 public:
  typedef std::function<void(bool)> CallbackOuterComplete;

 public:
  CallbackOuter();
  virtual ~CallbackOuter();

  void Execute(CallbackOuterComplete callback);
};

// callbackテスト
class TestCallbackTest : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestCallbackTest(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestCallbackTest();

  void ExecuteUnitTest();

  bool OuterCallback();
};

}  // namespace test

#endif  // MHL_TEST_CODE_TESTCALLBACKTEST_HPP_
