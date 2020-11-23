#ifndef MHL_TEST_CODE_TEST_BIT_CONTROL_UINT32_HPP_
#define MHL_TEST_CODE_TEST_BIT_CONTROL_UINT32_HPP_

#include <memory>

#include "../../test/unittest_base.hpp"

namespace test_code {

// BitControlUint32のテスト
class TestBitControlUint32 : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestBitControlUint32(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestBitControlUint32();

  /**
   * @brief ユニットテスト実行
   */
  void ExecuteUnitTest();

  void TestConstructorDefault();
  void TestConstructorZero();
  void TestConstructor100();
  void TestSetZero();
  void TestSet9999();
  void TestBitOn0Bit();
  void TestBitOn1Bit();
  void TestBitOn31Bit();
  void TestBitOn12BitMulti();
  void TestBitOff0Bit();
  void TestBitOff1Bit();
  void TestBitOff31Bit();
  void TestBitOff11BitMulti();
  void TestBitToggle0Bit();
  void TestBitToggle1Bit();
  void TestBitToggle8Bit();
  void TestBitToggle31Bit();
  void TestGetZero();
  void TestGet122();
  void TestGet12345();
  void TestGetUint32Max();
  void TestGetBitOnZero();
  void TestGetBitOffZero();
  void TestGetBitOn7();
  void TestGetBitOff7();
};

}  // namespace test_code

#endif  // MHL_TEST_CODE_TEST_BIT_CONTROL_UINT32_HPP_
