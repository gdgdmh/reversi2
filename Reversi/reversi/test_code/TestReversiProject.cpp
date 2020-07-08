#include "TestReversiProject.hpp"

#include "../../mhl/test/UnitTestExecuteList.hpp"
#include "../../mhl/util/output/OutputConsole.hpp"
#include "Test2Board.h"
#include "Test2CalcBoardEvaluationPointByPosition.h"
#include "Test2Move.hpp"
#include "Test2PerformanceCounter.hpp"

/**
 * コンストラクタ
 */
test_code::TestReversiProject::TestReversiProject(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::TestReversiProject::~TestReversiProject() {}

void test_code::TestReversiProject::ExecuteUnitTest() {
  mhl::UnitTestExecuteList list;
  std::shared_ptr<mhl::IOutputConsole> console(new mhl::OutputConsole());

  // テスト実行登録
  list.Add(std::shared_ptr<test_code::Test2Board>(
      new test_code::Test2Board(console)));
  list.Add(std::shared_ptr<test_code::Test2CalcBoardEvaluationPointByPosition>(
      new test_code::Test2CalcBoardEvaluationPointByPosition(console)));
  list.Add(
      std::shared_ptr<test_code::Test2Move>(new test_code::Test2Move(console)));
  list.Add(std::shared_ptr<test_code::TestPerformanceCounter>(
      new test_code::TestPerformanceCounter(console)));
  // テスト実行
  if (!list.Execute()) {
    AssertEquals(false, "TestReversiProject::ExecuteUnitTest failure");
  }
}
