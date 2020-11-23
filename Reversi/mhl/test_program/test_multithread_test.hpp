#ifndef MHL_TEST_CODE_TEST_MULTITHREAD_TEST_HPP_
#define MHL_TEST_CODE_TEST_MULTITHREAD_TEST_HPP_

#include <memory>
#include <mutex>

#include "../test/unittest_base.hpp"

namespace test_program {

class MultiThreadTestTask {
 public:
  MultiThreadTestTask(std::shared_ptr<mhl::IOutputConsole> output_console);
  virtual ~MultiThreadTestTask();

  void SetId(int id) { id_ = id; }
  void Add() { ++value_; }
  int GetId() const { return id_; }
  int GetValue() const { return value_; }
  void Print() { output_console_->PrintLine(mhl::StdStringFormatter::Format("ID %d value %d", id_, value_)); }
  void Task1();
  void Task2();

 private:
  std::shared_ptr<mhl::IOutputConsole> output_console_;
  std::mutex mutex_;
  int id_;
  int value_;
};

// マルチスレッド
class TestMultithreadTest : public mhl::UnitTestBase {
 public:
  /**
   * コンストラクタ
   */
  TestMultithreadTest(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * デストラクタ
   */
  virtual ~TestMultithreadTest();

  void ExecuteUnitTest();
};

}  // namespace test

#endif  // MHL_TEST_CODE_TEST_MULTITHREAD_TEST_HPP_
