#ifndef MHL_TEST_CODE_TESTSUBJECT_HPP_
#define MHL_TEST_CODE_TESTSUBJECT_HPP_

#include <memory>

#include "../test/unittest_base.hpp"
#include "../util/template/iexecute_method.hpp"
#include "../util/template/iobservable.hpp"
#include "../util/template/subject.hpp"

namespace test_code {

// テストのためのクラス
class TestObserver : public mhl::IObservable {
 public:
  TestObserver() : value(0) {}

  void Update(mhl::Subject& subject) { value = 1; }

  int Get() const { return value; }

 private:
  int value;
};

// メソッド実行テストクラス
class TestSubject : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestSubject(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestSubject();

  void ExecuteUnitTest();
};

}  // namespace test

#endif  // TEST_TESTSUBJECT_HPP_
