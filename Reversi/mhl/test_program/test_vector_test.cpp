#include "test_vector_test.hpp"

#include <vector>
#include <iterator>

test_program::TestVectorData::TestVectorData(int a, int b, int c)
    : a_(a), b_(b), c_(c) {

}

/**
 * コンストラクタ
 */
test_program::TestVectorTest::TestVectorTest(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_program::TestVectorTest::~TestVectorTest() {}

void test_program::TestVectorTest::ExecuteUnitTest() {
  /*
  std::vector<int> v1;
  std::vector<int*> v2;
  SetVector(v1, v2);
  //CopyVector(v2);
  CopyVector2(v2);
  v_;
  */
  std::vector<TestVectorData> v1;
  std::vector<TestVectorData*> v2;
  SetVector(v1, v2);
  // CopyVector(v2);
  CopyVector2(v2);
  v_;
}

/*
void test_program::TestVectorTest::SetVector(std::vector<int>& v1,
                                             std::vector<int*>& v2) {
  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);
  v1.push_back(5);

  for (int i = 0; i < v1.size(); ++i) {
    v2.push_back(&v1[i]);
  }
}

void test_program::TestVectorTest::CopyVector(std::vector<int*>& v) {
  v_.emplace_back(v);
}

void test_program::TestVectorTest::CopyVector2(std::vector<int*>& v) {
  v_.emplace_back(v);
}
*/

void test_program::TestVectorTest::SetVector(std::vector<TestVectorData>& v1, std::vector<TestVectorData*>& v2) {
  v1.push_back(TestVectorData(1, 2, 3));
  v1.push_back(TestVectorData(4, 5, 6));
  v1.push_back(TestVectorData(7, 8, 9));
  v1.push_back(TestVectorData(10, 11, 12));
  v1.push_back(TestVectorData(13, 14, 15));

  for (int i = 0; i < v1.size(); ++i) {
    v2.push_back(&v1[i]);
  }
}

void test_program::TestVectorTest::CopyVector(std::vector<TestVectorData*>& v) {
  v_.emplace_back(v);
}

void test_program::TestVectorTest::CopyVector2(std::vector<TestVectorData*>& v) {
  v_.emplace_back(v);
}
