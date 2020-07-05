#include "TestSubject.hpp"

/**
 * �R���X�g���N�^
 */
test::TestSubject::TestSubject(std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {
}

/**
 * �f�X�g���N�^
 */
test::TestSubject::~TestSubject() {
}

void test::TestSubject::ExecuteUnitTest() {

    mhl::Subject s;
    test::TestObserver o;
    s.Add(o);
    AssertEquals(o.Get() == 0, "TestSubject::ExecuteUnitTest not 0");
    // �����Update��Call����Ă���Βl��0����1�ɐ؂�ւ��
    s.NotifyObservers();
    AssertEquals(o.Get() == 1, "TestSubject::ExecuteUnitTest not 1");
    s.Remove(o);
}
