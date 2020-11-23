#ifndef MHL_TEST_PROGRAM_TESTMHLTESTPROGRAM_HPP_
#define MHL_TEST_PROGRAM_TESTMHLTESTPROGRAM_HPP_

#include <memory>

#include "../test/unittest_base.hpp"

namespace test_program {

// MHLテストクラス
class TestMhlTestProgram : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestMhlTestProgram(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestMhlTestProgram();

  void ExecuteUnitTest();
};

}  // namespace test_program

#endif  // MHL_TEST_PROGRAM_TESTMHLTESTPROGRAM_HPP_
