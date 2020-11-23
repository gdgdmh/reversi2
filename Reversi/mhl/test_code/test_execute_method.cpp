#include "test_execute_method.hpp"

/**
 * コンストラクタ
 */
test_code::TestExecuteMethod::TestExecuteMethod(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console),
      on_exec_(&test_code::TestExecuteMethod::Initialize),
      scene_(SCENE::kInitialize) {}

/**
 * デストラクタ
 */
test_code::TestExecuteMethod::~TestExecuteMethod() {}

void test_code::TestExecuteMethod::ExecuteUnitTest() {
  AssertEquals(scene_ == SCENE::kInitialize, "TestExecuteMethod not kInitialize");
  Task();
  AssertEquals(scene_ == SCENE::kInitialize, "TestExecuteMethod not kInitialize(2)");
  Task();
  AssertEquals(scene_ == SCENE::kLoad, "TestExecuteMethod not kLoad");
  Task();
  AssertEquals(scene_ == SCENE::kMain, "TestExecuteMethod not kMain");
  Task();
  AssertEquals(scene_ == SCENE::kMain, "TestExecuteMethod not kMain(2)");
}

void test_code::TestExecuteMethod::Task() {
  on_exec_ = on_exec_.executeMethod(this);
}

mhl::IExecuteMethod<test_code::TestExecuteMethod>
test_code::TestExecuteMethod::Initialize() {
  scene_ = SCENE::kInitialize;
  return &test_code::TestExecuteMethod::Load;
}

mhl::IExecuteMethod<test_code::TestExecuteMethod>
test_code::TestExecuteMethod::Load() {
  scene_ = SCENE::kLoad;
  return &test_code::TestExecuteMethod::Main;
}

mhl::IExecuteMethod<test_code::TestExecuteMethod>
test_code::TestExecuteMethod::Main() {
  scene_ = SCENE::kMain;
  return &test_code::TestExecuteMethod::Main;
}
