#ifndef REVERSI_UTIL_IRANDOMINT_H_
#define REVERSI_UTIL_IRANDOMINT_H_

namespace reversi {

// 乱数生成クラス
class IRandomInt {
public:

	/**
	 * デストラクタ
	 */
	virtual ~IRandomInt() {
	}

	/**
	 * 乱数の種設定
	 * @param seed 乱数の種
	 */
	virtual void SetSeed(unsigned int seed) = 0;

	/**
	 * 乱数の種を時間から設定
	 */
	virtual void SetSeedByTime() = 0;

	/**
	 * 乱数の取得
	 * @param  min 範囲の最小値(この値を含む)
	 * @param  max 範囲の最大値(この値を含む)
	 * @return     生成された乱数
	 */
	virtual int Get(int min, int max) = 0;
};

}

#endif  // REVERSI_UTIL_IRANDOMINT_H_
