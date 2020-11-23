#include "test_mhl_test_program.hpp"

#include "../test/unittest_execute_list.hpp"
#include "../test_program/test_binarytree_test.hpp"
#include "../test_program/test_cpp_new_function_test.hpp"
#include "../test_program/test_instance_of_test.hpp"
#include "../test_program/test_multithread_test.hpp"
#include "../test_program/test_callback_test.hpp"
#include "../test_program/test_vector_test.hpp"
#include "../util/output/ioutput_console.hpp"
#include "../util/output/output_console.hpp"

/**
 * コンストラクタ
 */
test_program::TestMhlTestProgram::TestMhlTestProgram(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_program::TestMhlTestProgram::~TestMhlTestProgram() {}

void test_program::TestMhlTestProgram::ExecuteUnitTest() {
  mhl::UnitTestExecuteList list;
  std::shared_ptr<mhl::IOutputConsole> console(new mhl::OutputConsole());
  list.Add(std::shared_ptr<test_program::TestCppNewFunctionTest>(
      new test_program::TestCppNewFunctionTest(console)));
  list.Add(std::shared_ptr<test_program::TestInstanceOfTest>(
      new test_program::TestInstanceOfTest(console)));
  list.Add(std::shared_ptr<test_program::TestBinaryTest>(
      new test_program::TestBinaryTest(console)));
  list.Add(std::shared_ptr<test_program::TestVectorTest>(
  new test_program::TestVectorTest(console)));
  // できれば最後の実行したい(マルチスレッドが途中だと原因がわからなくなる可能性があるかもしれない)
  list.Add(std::shared_ptr<test_program::TestMultithreadTest>(
      new test_program::TestMultithreadTest(console)));
  // execute test
  if (!list.Execute()) {
    AssertEquals(false, "TestMhlTestProgram::ExecuteUnitTest failure");
  }
}
