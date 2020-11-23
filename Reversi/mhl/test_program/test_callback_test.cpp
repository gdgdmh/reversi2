#include "test_callback_test.hpp"

#include <chrono>
#include <iostream>
#include <thread>

test_program::CallbackInner::CallbackInner() {}

test_program::CallbackInner::~CallbackInner() {}

void test_program::CallbackInner::Execute(CallbackInnerComplete callback) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 5));
  std::cout << "inner";
  if (callback != nullptr) {
    callback(1, 0);
  }
}

test_program::CallbackOuter::CallbackOuter() {}
test_program::CallbackOuter::~CallbackOuter() {}

void test_program::CallbackOuter::Execute(CallbackOuterComplete callback) {
  test_program::CallbackInner inner;
  inner.Execute([callback](uint32_t p1, uint32_t p2) {
    if ((p1 == 0) && (p2 == 0)) {
      callback(true);
    } else {
      callback(false);
    }
  });
}

/**
 * コンストラクタ
 */
test_program::TestCallbackTest::TestCallbackTest(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_program::TestCallbackTest::~TestCallbackTest() {}

void test_program::TestCallbackTest::ExecuteUnitTest() {
  test_program::CallbackOuter outer;
  outer.Execute([](bool result) {
    if (result) {
      std::cout << "success";
    } else {
      std::cout << "failure";
    }
  });

  // TestCpp11Nullptr();
}
