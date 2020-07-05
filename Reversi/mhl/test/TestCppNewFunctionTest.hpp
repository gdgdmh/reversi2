#ifndef TEST_TESTCPPNEWFUNCTIONTEST_HPP_
#define TEST_TESTCPPNEWFUNCTIONTEST_HPP_

#include <memory>
#include "UnitTestBase.hpp"

namespace test {

  class TestEmplace {
    public:
    TestEmplace() : aaa(0), bbb(0) {
    }
    TestEmplace(int a, int b) : aaa(a), bbb(b) {
    }
    void Get(int& a, int& b) {
      a = aaa;
      b = bbb;
    }

    private:
    int aaa;
    int bbb;
  };

// C++機能テスト
class TestCppNewFunctionTest : public mhl::UnitTestBase {
public:
  /**
   * コンストラクタ
   */
  TestCppNewFunctionTest(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestCppNewFunctionTest();

  void ExecuteUnitTest();

  /**
   * C++11のnullptrテスト
   */
  void TestCpp11Nullptr();

  /**
   * 統一初期化記法case001
   */
  void TestUniformInitialization001();

  /**
   * 統一初期化記法case002
   */
  void TestUniformInitialization002();

  /**
   * 統一初期化記法case003
   */
  void TestUniformInitialization003();

  /**
   * 統一初期化記法case004
   */
  void TestUniformInitialization004();

  /**
   * emplaceメソッドテスト
   */
  void TestEmplace();

  /**
   * スマートポインタ
   */
  void TestSmartPointer();

  /**
   * 型エイリアス
   */
  void TestTypeAlias();
};

}

#endif  // TEST_TESTCPPNEWFUNCTIONTEST_HPP_
