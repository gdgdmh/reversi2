#ifndef TEST_TESTEXECUTEMETHOD_HPP_
#define TEST_TESTEXECUTEMETHOD_HPP_

#include <memory>
#include "UnitTestBase.hpp"
#include "../util/template/IExecuteMethod.hpp"

namespace test {

// メソッド実行テストクラス
class TestExecuteMethod : public mhl::UnitTestBase {
public:
  typedef mhl::IExecuteMethod<test::TestExecuteMethod> MEB;
  enum class SCENE {
    kInitialize,
    kLoad,
    kMain
  };

public:
  /**
   * コンストラクタ
   */
  TestExecuteMethod(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestExecuteMethod();

  void ExecuteUnitTest();

  void Task();

  SCENE GetScene() {
    return scene_;
  }

public:

  mhl::IExecuteMethod<test::TestExecuteMethod> Initialize();
  mhl::IExecuteMethod<test::TestExecuteMethod> Load();
  mhl::IExecuteMethod<test::TestExecuteMethod> Main();

private:
  mhl::IExecuteMethod<test::TestExecuteMethod> on_exec_;
  SCENE scene_;
};

}

#endif  // TEST_TESTEXECUTEMETHOD_HPP_
