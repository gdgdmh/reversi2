#ifndef TEST_TESTSUBJECT_HPP_
#define TEST_TESTSUBJECT_HPP_

#include <memory>

#include "../util/template/IExecuteMethod.hpp"
#include "../util/template/IObservable.hpp"
#include "../util/template/Subject.hpp"
#include "UnitTestBase.hpp"

namespace test {

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
