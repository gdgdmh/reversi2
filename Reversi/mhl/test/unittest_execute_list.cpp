#include "unittest_execute_list.hpp"

#include "../exception/unittest_exception.hpp"
#include "../util/output/ioutput_console.hpp"
#include "../util/output/output_console.hpp"

mhl::UnitTestExecuteList::UnitTestExecuteList() {}

mhl::UnitTestExecuteList::~UnitTestExecuteList() {}

void mhl::UnitTestExecuteList::Add(
    const std::shared_ptr<UnitTestBase>& unit_test) {
  unit_test_list.push_back(unit_test);
}

bool mhl::UnitTestExecuteList::Execute() {
  std::shared_ptr<IOutputConsole> console(new OutputConsole());
  try {
    console->PrintLine(
        "--- UnitTestExecuteList start ---------------------------");
    for (auto it = unit_test_list.begin(); it != unit_test_list.end(); ++it) {
      (*it)->ExecuteUnitTest();
    }
  } catch (const mhl::UnitTestException& e) {
    // 単体テスト失敗の例外
    console->PrintLine("UnitTestExecuteList::Execute failure");
    console->PrintLine(e.what());
    return false;
  }
  console->PrintLine(
      "--- UnitTestExecuteList end -----------------------------");
  return true;
}