﻿#include "TestSubject.hpp"

/**
 * コンストラクタ
 */
test::TestSubject::TestSubject(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test::TestSubject::~TestSubject() {}

void test::TestSubject::ExecuteUnitTest() {
  mhl::Subject s;
  test::TestObserver o;
  s.Add(o);
  AssertEquals(o.Get() == 0, "TestSubject::ExecuteUnitTest not 0");
  // 正常にUpdateがCallされていれば値が0から1に切り替わる
  s.NotifyObservers();
  AssertEquals(o.Get() == 1, "TestSubject::ExecuteUnitTest not 1");
  s.Remove(o);
}
