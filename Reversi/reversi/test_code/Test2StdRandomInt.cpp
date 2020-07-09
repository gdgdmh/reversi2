#include "Test2StdRandomInt.hpp"

#include "../util/StdRandomInt.h"

/**
 * コンストラクタ
 */
test_code::Test2StdRandomInt::Test2StdRandomInt(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2StdRandomInt::~Test2StdRandomInt() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2StdRandomInt::ExecuteUnitTest() {
  std::shared_ptr<reversi::IRandomInt> random(new reversi::StdRandomInt());

  const int INITIALIZE_SEED = 0;     // 初期乱数SEED
  const int MIN_RANDOM_VALUE = 0;    // 範囲最低値
  const int MAX_RANDOM_VALUE = 255;  // 範囲最大値

  // 同じ乱数の種を使うと同じ値が返ってくるはず
  {
    random->SetSeed(INITIALIZE_SEED);
    int result = random->Get(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE);
    random->SetSeed(INITIALIZE_SEED);
    int result2 = random->Get(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE);
    AssertEquals(result == result2, "TestStdRandomInt::Execute NOT SAME VALUE");
  }
  // 値の範囲に入っているかチェック(やりすぎても埒が明かないのでひとまず10回)
  const int CHECK_COUNT = 10;
  for (int i = 0; i < CHECK_COUNT; ++i) {
    random->SetSeedByTime();  // 乱数の種は適当に生成
    int result = random->Get(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE);
    // MINとMAXの間で生成されているかチェック
    AssertEquals((result >= MIN_RANDOM_VALUE) && (result <= MAX_RANDOM_VALUE),
                 "TestStdRandomInt::Execute NOT VALUE RANGE");
  }
}
