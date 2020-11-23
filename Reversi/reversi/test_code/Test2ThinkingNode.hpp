#ifndef REVERSI_TEST_CODE_TEST2THINKINGNODE_HPP_
#define REVERSI_TEST_CODE_TEST2THINKINGNODE_HPP_

#include <memory>

#include "../../mhl/test/unittest_base.hpp"

namespace test_code {

// 整数乱数生成テスト
class Test2ThinkingNode : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  Test2ThinkingNode(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~Test2ThinkingNode();

  /**
   * @brief テストの実行
   *
   */
  void ExecuteUnitTest();
};

}  // namespace test_code

#endif  // REVERSI_TEST_CODE_TEST2THINKINGNODE_HPP_
