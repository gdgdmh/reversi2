#ifndef MHL_TEST_CODE_TEST_BINARYTREE_TEST_HPP_
#define MHL_TEST_CODE_TEST_BINARYTREE_TEST_HPP_

#include <memory>

#include "../test/unittest_base.hpp"

namespace test_program {

class TestBinaryClass {
public:
  /**
   * @brief コンストラクタ
   * 
   */
 TestBinaryClass(int id, const std::string& value) : id_(id), value_(value) {}

  /**
   * @brief デストラクタ
   *
   */
  virtual ~TestBinaryClass() {}

  void SetId(int id) { id_ = id; }
  int GetId() const { return id_; }
  void SetValue(const std::string& value) { value_ = value;}
  const std::string& GetValue() const { return value_; }

private:
  int id_;
  std::string value_;
};

// 2分木テスト
class TestBinaryTest : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestBinaryTest(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestBinaryTest();

  void ExecuteUnitTest();

 private:
  void TestIntTest();
  void TestBinaryClassTest();
};

}  // namespace test

#endif  // MHL_TEST_CODE_TEST_BINARYTREE_TEST_HPP_
