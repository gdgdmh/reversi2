#include "TestCppNewFunctionTest.hpp"

/**
 * コンストラクタ
 */
test::TestCppNewFunctionTest::TestCppNewFunctionTest(std::shared_ptr<mhl::IOutputConsole> output_console)
  : UnitTestBase(output_console) {
}

/**
 * デストラクタ
 */
test::TestCppNewFunctionTest::~TestCppNewFunctionTest() {
}

void test::TestCppNewFunctionTest::ExecuteUnitTest() {
  TestCpp11Nullptr();
  TestUniformInitialization001();
  TestUniformInitialization002();
  TestUniformInitialization003();
  TestUniformInitialization004();
  TestEmplace();
  TestSmartPointer();
  TestTypeAlias();
}

/**
 * C++11のnullptrテスト
 */
void test::TestCppNewFunctionTest::TestCpp11Nullptr() {
  char* p = nullptr;
  AssertEquals(p == nullptr, "TestCppNewFunctionTest::TestCpp11Nullptr() not nullptr");
}

/**
 * 統一初期化記法
 */
void test::TestCppNewFunctionTest::TestUniformInitialization001() {
  const int VALUE = 3;
  int x { VALUE };
  AssertEquals(x == VALUE, "TestCppNewFunctionTest::TestUniformInitialization001 x not 3");
}

/**
 * 統一初期化記法case002
 */
void test::TestCppNewFunctionTest::TestUniformInitialization002() {
  const int VALUE1 = 10;
  const int VALUE2 = 11;
  const int VALUE3 = 12;
  const int VALUE4 = 13;
  int x[] { VALUE1, VALUE2, VALUE3, VALUE4 };
  AssertEquals(x[0] == VALUE1, "TestCppNewFunctionTest::TestUniformInitialization002 x[0] not VALUE1");
  AssertEquals(x[1] == VALUE2, "TestCppNewFunctionTest::TestUniformInitialization002 x[1] not VALUE2");
  AssertEquals(x[2] == VALUE3, "TestCppNewFunctionTest::TestUniformInitialization002 x[2] not VALUE3");
  AssertEquals(x[3] == VALUE4, "TestCppNewFunctionTest::TestUniformInitialization002 x[3] not VALUE4");
}

/**
 * 統一初期化記法case003
 */
void test::TestCppNewFunctionTest::TestUniformInitialization003() {
  struct Struct {
    int a;
    int b;
  };
  const int VALUE_A = 11;
  const int VALUE_B = 12;
  Struct x { VALUE_A, VALUE_B };
  AssertEquals(x.a == VALUE_A, "TestCppNewFunctionTest::TestUniformInitialization003 x.a not VALUE_A");
  AssertEquals(x.b == VALUE_B, "TestCppNewFunctionTest::TestUniformInitialization003 x.b not VALUE_B");
}

/**
 * 統一初期化記法case004
 */
void test::TestCppNewFunctionTest::TestUniformInitialization004() {
  const int VALUE1 = 101;
  const int VALUE2 = 102;
  std::vector<int> x = { VALUE1, VALUE2 };
  AssertEquals(x[0] == VALUE1, "TestCppNewFunctionTest::TestUniformInitialization003 x[0] not VALUE1");
  AssertEquals(x[1] == VALUE2, "TestCppNewFunctionTest::TestUniformInitialization003 x[1] not VALUE2");
}

/**
 * emplaceメソッドテスト
 */
void test::TestCppNewFunctionTest::TestEmplace() {
  const int VALUE1 = 1000;
  const int VALUE2 = 2000;
  std::vector<test::TestEmplace> vec;
  vec.emplace_back(test::TestEmplace(VALUE1, VALUE2));
  int a = 0, b = 0;
  vec.at(0).Get(a, b);
  AssertEquals(a == VALUE1, "TestCppNewFunctionTest::TestEmplace a not VALUE1");
  AssertEquals(b == VALUE2, "TestCppNewFunctionTest::TestEmplace b not VALUE2");
}

/**
 * スマートポインタ
 */
void test::TestCppNewFunctionTest::TestSmartPointer() {
  const int VALUE1 = 10;
  std::shared_ptr<int> smart_pointer(new int(VALUE1));
  AssertEquals(smart_pointer.use_count() == 1, "TestCppNewFunctionTest::TestSmartPointer smart_pointer count not 1");
  AssertEquals((*smart_pointer) == VALUE1, "TestCppNewFunctionTest::TestSmartPointer smart_pointer not VALUE1");

  std::shared_ptr<int> smart_pointer2 = smart_pointer;
  AssertEquals(smart_pointer.use_count() == 2, "TestCppNewFunctionTest::TestSmartPointer smart_pointer count not 2");
  AssertEquals(smart_pointer2.use_count() == 2, "TestCppNewFunctionTest::TestSmartPointer smart_pointer2 count not 2");

  AssertEquals((*smart_pointer) == VALUE1, "TestCppNewFunctionTest::TestSmartPointer smart_pointer not VALUE1");
  AssertEquals((*smart_pointer2) == VALUE1, "TestCppNewFunctionTest::TestSmartPointer smart_pointer2 not VALUE1");
}

/**
 * 型エイリアス
 */
void test::TestCppNewFunctionTest::TestTypeAlias() {
  using SmartPointerInt = std::shared_ptr<int>;
  SmartPointerInt si(new int(0));
  AssertEquals((*si) == 0, "TestCppNewFunctionTest::TestTypeAlias si not 0");
}
