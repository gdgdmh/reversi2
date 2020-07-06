#include "StdRandomInt.h"

#include <time.h>

/**
 * コンストラクタ
 */
reversi::StdRandomInt::StdRandomInt() : mt(0) {}

/**
 * デストラクタ
 */
reversi::StdRandomInt::~StdRandomInt() {}

/**
 * 乱数の種設定
 * @param seed 乱数の種
 */
void reversi::StdRandomInt::SetSeed(unsigned int seed) { mt.seed(seed); }

/**
 * 乱数の種を時間から設定
 */
void reversi::StdRandomInt::SetSeedByTime() { mt.seed((int)time(NULL)); }

/**
 * 乱数の取得
 * @param  min 範囲の最小値(この値を含む)
 * @param  max 範囲の最大値(この値を含む)
 * @return     生成された乱数
 */
int reversi::StdRandomInt::Get(int min, int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(mt);
}
