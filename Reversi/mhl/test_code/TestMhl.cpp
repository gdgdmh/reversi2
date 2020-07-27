#include "TestMhl.hpp"

#include "../test/UnitTestExecuteList.hpp"
#include "../util/output/IOutputConsole.hpp"
#include "../util/output/OutputConsole.hpp"
#include "TestCppNewFunctionTest.hpp"
#include "TestExecuteMethod.hpp"
#include "TestInstanceOfTest.hpp"
#include "TestSceneStack.hpp"
#include "TestSubject.hpp"

/**
 * コンストラクタ
 */
test::TestMhl::TestMhl(std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test::TestMhl::~TestMhl() {}

void test::TestMhl::ExecuteUnitTest() {
  mhl::UnitTestExecuteList list;
  std::shared_ptr<mhl::IOutputConsole> console(new mhl::OutputConsole());
  list.Add(std::shared_ptr<test::TestCppNewFunctionTest>(
      new test::TestCppNewFunctionTest(console)));
  list.Add(std::shared_ptr<test::TestExecuteMethod>(
      new test::TestExecuteMethod(console)));
  list.Add(std::shared_ptr<test::TestSubject>(new test::TestSubject(console)));
  list.Add(std::shared_ptr<test::TestInstanceOfTest>(
      new test::TestInstanceOfTest(console)));
  list.Add(std::shared_ptr<test::TestSceneStack>(new test::TestSceneStack(console)));
  if (!list.Execute()) {
    AssertEquals(false, "TestMhl::ExecuteUnitTest failure");
  }
}
