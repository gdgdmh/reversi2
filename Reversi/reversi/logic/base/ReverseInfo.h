#ifndef REVERSI_LOGIC_BASE_REVERSEINFO_H_
#define REVERSI_LOGIC_BASE_REVERSEINFO_H_

#include "ReversiConstant.h"

namespace reversi {

// 裏返し情報
class ReverseInfo {
public:
	// 方向
	enum class DIRECTION {
		UP,         // 上
		DOWN,       // 下
		LEFT,       // 左
		RIGHT,      // 右
		UP_LEFT,    // 左上
		UP_RIGHT,   // 右上
		DOWN_LEFT,  // 左下
		DOWN_RIGHT  // 右下
	};
	static const int MAX_DIRECTION = 8; // 方向最大数

	// 裏返し情報
	typedef struct {
		reversi::ReversiConstant::POSITION position;            // 打つ位置
		reversi::ReversiConstant::POSITION reversePositions[ReverseInfo::MAX_DIRECTION][reversi::ReversiConstant::ONE_MOVE_MAX_REVERSE_COUNT];  // 打ったことで裏返る位置
		int reversePositionCount[ReverseInfo::MAX_DIRECTION];   // 裏返る位置の数
		reversi::ReversiConstant::TURN turn;                    // 手番情報
	} REVERSE_INFO;
public:

	/**
	 * コンストラクタ
	 * @param position 打つ位置
	 * @param turn     手番
	 */
	ReverseInfo(reversi::ReversiConstant::POSITION position, reversi::ReversiConstant::TURN turn);

	/**
	 * デフォルトコンストラクタ
	 */
	ReverseInfo();

	/**
	 * デストラクタ
	 */
	virtual ~ReverseInfo();

	/**
	 * 情報をクリアする
	 */
	void Clear();

	/**
	 * 裏返る位置を追加登録する
	 * @param direction       方向
	 * @param reversePosition 登録するデータ
	 */
	void AddReversePosition(reversi::ReverseInfo::DIRECTION direction, reversi::ReversiConstant::POSITION reversePosition);

	/**
	 * 裏返る位置をクリアする
	 * @param direction 方向
	 */
	void ClearReversePosition(reversi::ReverseInfo::DIRECTION direction);

	/**
	 * 打つ位置の取得
	 * @return 打つ位置
	 */
	reversi::ReversiConstant::POSITION GetPosition() const {
		return info.position;
	}

	/**
	 * 裏返る位置の取得
	 * @param  direction 方向
	 * @param  index     取得するindex
	 * @return           裏返る位置
	 */
	reversi::ReversiConstant::POSITION GetReversePosition(reversi::ReverseInfo::DIRECTION direction, int index) const;

	/**
	 * 全ての方向の裏返る位置の取得
	 */
	std::vector<reversi::ReversiConstant::POSITION> GetReversePositionAllDirection() const;

	/**
	 * 裏返る位置の数の取得
	 * @param  direction 方向
	 * @return           裏返る位置のデータの数
	 */
	int GetReversePositionCount(reversi::ReverseInfo::DIRECTION direction) const;

	/**
	 * 裏返る数のトータル取得
	 * @return 裏返る数のトータル
	 */
	int GetReversePositionCountTotal() const;

	/**
	 * 手番情報の取得
	 * @return 手番情報
	 */
	reversi::ReversiConstant::TURN GetTurn() const {
		return info.turn;
	}

	/**
	 * どこかの方向に打てば取ることができるか
	 * @return trueなら打つことができる
	 */
	bool IsEnableMove() const;

private:
	REVERSE_INFO info;  // 裏返し情報
};

}

#endif  // REVERSI_LOGIC_BASE_REVERSEINFO_H_
