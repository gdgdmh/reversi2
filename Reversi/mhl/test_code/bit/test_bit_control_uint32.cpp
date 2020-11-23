#include "test_bit_control_uint32.hpp"

#include "../../bit/bit_control_uint32.hpp"

/**
 * コンストラクタ
 */
test_code::TestBitControlUint32::TestBitControlUint32(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::TestBitControlUint32::~TestBitControlUint32() {}

void test_code::TestBitControlUint32::ExecuteUnitTest() {
  TestConstructorDefault();
  TestConstructorZero();
  TestConstructor100();
  TestSetZero();
  TestSet9999();
  TestBitOn0Bit();
  TestBitOn1Bit();
  TestBitOn31Bit();
  TestBitOn12BitMulti();
  TestBitOff0Bit();
  TestBitOff1Bit();
  TestBitOff31Bit();
  TestBitOff11BitMulti();
  TestBitToggle0Bit();
  TestBitToggle1Bit();
  TestBitToggle8Bit();
  TestBitToggle31Bit();
  TestGetZero();
  TestGet122();
  TestGet12345();
  TestGetUint32Max();
  TestGetBitOnZero();
  TestGetBitOffZero();
  TestGetBitOn7();
  TestGetBitOff7();
  // AssertEquals(instanceOf<Enemy>(&le), "TestInstanceOfTest not EnemyBase 2");
}

void test_code::TestBitControlUint32::TestConstructorDefault() {
  mhl::BitControlUint32 b;
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestConstructorZero() {
  mhl::BitControlUint32 b(0);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestConstructor100() {
  const uint32_t VALUE = 100;
  mhl::BitControlUint32 b(VALUE);
  AssertEquals(b.Get() == VALUE, "");
}

void test_code::TestBitControlUint32::TestSetZero() {
  const uint32_t VALUE = 0;
  mhl::BitControlUint32 b;
  b.Set(VALUE);
  AssertEquals(b.Get() == VALUE, "");
}

void test_code::TestBitControlUint32::TestSet9999() {
  const uint32_t VALUE = 9999;
  mhl::BitControlUint32 b;
  b.Set(VALUE);
  AssertEquals(b.Get() == VALUE, "");
}

void test_code::TestBitControlUint32::TestBitOn0Bit() {
  mhl::BitControlUint32 b;
  b.BitOn(0);
  AssertEquals(b.Get() == 0x01, "");
}

void test_code::TestBitControlUint32::TestBitOn1Bit() {
  mhl::BitControlUint32 b;
  b.BitOn(1);
  AssertEquals(b.Get() == 0x02, "");
}

void test_code::TestBitControlUint32::TestBitOn31Bit() {
  mhl::BitControlUint32 b;
  b.BitOn(31);
  const uint32_t VALUE = 2147483648;
  AssertEquals(b.Get() == VALUE, "");
}

void test_code::TestBitControlUint32::TestBitOn12BitMulti() {}

void test_code::TestBitControlUint32::TestBitOff0Bit() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 0;
  b.BitOn(BIT);
  AssertEquals(b.Get() == 0x01, "");
  b.BitOff(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestBitOff1Bit() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 1;
  b.BitOn(BIT);
  AssertEquals(b.Get() == 0x02, "");
  b.BitOff(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestBitOff31Bit() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 31;
  b.BitOn(BIT);
  AssertEquals(b.Get() == 0x80000000, "");
  b.BitOff(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestBitOff11BitMulti() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 11;
  b.BitOn(BIT);
  AssertEquals(b.Get() == 0x800, "");
  b.BitOff(BIT);
  AssertEquals(b.Get() == 0, "");
  b.BitOff(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestBitToggle0Bit() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 0;
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0x01, "");
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestBitToggle1Bit() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 1;
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0x02, "");
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestBitToggle8Bit() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 8;
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0x100, "");
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestBitToggle31Bit() {
  mhl::BitControlUint32 b;
  const uint32_t BIT = 31;
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0x80000000, "");
  b.BitToggle(BIT);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestGetZero() {
  mhl::BitControlUint32 b(0);
  AssertEquals(b.Get() == 0, "");
}

void test_code::TestBitControlUint32::TestGet122() {
  const uint32_t VALUE = 122;
  mhl::BitControlUint32 b(VALUE);
  AssertEquals(b.Get() == VALUE, "");
}

void test_code::TestBitControlUint32::TestGet12345() {
  const uint32_t VALUE = 12345;
  mhl::BitControlUint32 b(VALUE);
  AssertEquals(b.Get() == VALUE, "");
}

void test_code::TestBitControlUint32::TestGetUint32Max() {
  const uint32_t VALUE = 0xffffffffui32;
  mhl::BitControlUint32 b(VALUE);
  AssertEquals(b.Get() == VALUE, "");
}

void test_code::TestBitControlUint32::TestGetBitOnZero() {
  const uint32_t BIT = 0;
  mhl::BitControlUint32 b;
  b.BitOn(BIT);
  AssertEquals((b.GetBit(0) == true), "");
}

void test_code::TestBitControlUint32::TestGetBitOffZero() {
  const uint32_t BIT = 0;
  mhl::BitControlUint32 b;
  b.BitOff(BIT);
  AssertEquals((b.GetBit(0) == false), "");
}

void test_code::TestBitControlUint32::TestGetBitOn7() {
  const uint32_t BIT = 7;
  mhl::BitControlUint32 b;
  b.BitOn(BIT);
  AssertEquals((b.GetBit(BIT) == true), "");
}

void test_code::TestBitControlUint32::TestGetBitOff7() {
  const uint32_t BIT = 7;
  mhl::BitControlUint32 b;
  b.BitOff(7);
  AssertEquals((b.GetBit(BIT) == false), "");
}
