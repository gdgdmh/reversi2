#ifndef REVERSI_UTIL_STDRANDOMINT_H_
#define REVERSI_UTIL_STDRANDOMINT_H_

#include "IRandomInt.h"
#include <random>

namespace reversi {

// std::randomを使用した整数乱数生成
class StdRandomInt : public IRandomInt {
public:

	/**
	 * コンストラクタ
	 */
	StdRandomInt();

	/**
	 * デストラクタ
	 */
	virtual ~StdRandomInt();

	/**
	 * 乱数の種設定
	 * @param seed 乱数の種
	 */
	void SetSeed(unsigned int seed);

	/**
	 * 乱数の種を時間から設定
	 */
	void SetSeedByTime();

	/**
	 * 乱数の取得
	 * @param  min 範囲の最小値(この値を含む)
	 * @param  max 範囲の最大値(この値を含む)
	 * @return     生成された乱数
	 */
	int Get(int min, int max);

private:
	std::mt19937 mt; // メルセンヌツイスタ
};

}

#endif  // REVERSI_UTIL_STDRANDOMINT_H_
