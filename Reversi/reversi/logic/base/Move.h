#ifndef REVERSI_LOGIC_BASE_MOVE_H_
#define REVERSI_LOGIC_BASE_MOVE_H_

#include <vector>
#include "ReversiConstant.h"
#include "ReverseInfo.h"

// 前方宣言
namespace reversi {
class Board;
}

namespace reversi {

// 着手クラス
class Move {
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
	// 挟まれチェックの状態
	enum class SANDWICH_STATUS {
		SANDWICH_OK,            // 挟み状態になっている
		SANDWICH_CONTINUE,      // まだ挟み状態になっているかわからない
		SANDWICH_NG_INVALID,    // 無効マスで挟みにならない
		SANDWICH_NG_EMPTY,      // 空マスで挟みにならない
		SANDWICH_NG_SELF,       // 自分の石で挟みにならない
		SANDWICH_NG_UNKNOWN     // それ以外
	};
	// キャッシュデータ
	typedef struct {
		std::vector<reversi::ReverseInfo> reverseInfo; // 裏返し情報
	} MOVE_CACHE;

public:
	/**
	 * コンストラクタ
	 */
	Move();

	/**
	 * デストラクタ
	 */
	virtual ~Move();

	/**
	 * 石の置かれていない場所を探す
	 * @param board          盤データ
	 * @param emptyPositions 結果をいれるための参照渡しオブジェクト
	 */
	void FindEmptyPosition(const reversi::Board& board, reversi::ReversiConstant::EMPTY_POSITION& emptyPosition);

	/**
	 * 打てる場所を探す
	 * このデータはキャッシュされる
	 * @param board          盤データ
	 * @param emptyPositions 石の置かれてない場所が入ったデータ
	 * @param turn           手番(黒,白)
	 */
	void FindPutEnablePosition(const reversi::Board& board, const reversi::ReversiConstant::EMPTY_POSITION& emptyPosition, reversi::ReversiConstant::TURN turn);

	/**
	 * 打つことができるか
	 * 予めキャッシュを作成しておくこと
	 * @param  position チェックする位置
	 * @return          trueならその位置に打つことができる
	 */
	bool CheckEnableMoveByCache(reversi::ReversiConstant::POSITION position) const;

	/**
	 * どこかに打てるか
	 * 予めキャッシュを作成しておくこと
	 * @return trueならどこかに打てる
	 */
	bool CheckSomewherePutEnableByCache();

	/**
	 * 裏返し情報の取得
	 * 予めキャッシュを作成しておくこと
	 * @param  position 位置
	 * @return          裏返し情報
	 */
	const reversi::ReverseInfo GetReverseInfo(reversi::ReversiConstant::POSITION position) const;

	/**
	 * 裏返し情報の取得(index)
	 * 予めキャッシュを作成しておくこと
	 * @param  index 裏返し情報のindex
	 * @return       [description]
	 */
	const reversi::ReverseInfo& GetReverseInfoByIndex(int index) const;

	/**
	 * 裏返し情報のデータ数取得
	 * @return 裏返し情報データ数
	 */
	int GetReverseInfoSize() const;

public:

	/**
	 * その場所に打つことができるか情報を取得する
	 * @param  board    盤データ
	 * @param  position 打とうとする盤の位置
	 * @param  turn     手番(黒,白)
	 * @return          trueならその位置に打つことができる
	 */
	reversi::ReverseInfo GetEnableMoveInfo(const reversi::Board& board, int position, reversi::ReversiConstant::TURN turn);

	/**
	 * その位置の指定方向に打つことができるか、情報を取得する
	 * @param  board       盤データ
	 * @param  reverseInfo 裏返し情報
	 * @param  position    打とうとする盤の位置
	 * @param  direction   チェックする方向
	 * @param  turn        手番(黒,白)
	 * @return             trueならその方向に打つことができる
	 */
	bool CheckMoveInfoDirection(const reversi::Board& board, reversi::ReverseInfo& reverseInfo, int position, DIRECTION direction, reversi::ReversiConstant::TURN turn);

	/**
	 * 位置から盤のオフセットを取得する
	 * @param  direction 方向
	 * @return           盤のオフセット
	 */
	int ToDirectionOffset(DIRECTION direction);

	/**
	 * 挟まれている情報の取得
	 * @param  isSandwichStarted 挟まれているか
	 * @param  sandwichCount     いくつ挟まれているか
	 * @param  turn              手番(黒,白)
	 * @param  info              盤の情報
	 * @return                   状態
	 */
	reversi::Move::SANDWICH_STATUS GetSandwichInfo(bool& isSandwichStarted, int& sandwichCount, reversi::ReversiConstant::TURN turn, reversi::ReversiConstant::BOARD_INFO info);

private:

	/**
	 * DIRECTON型をReverseInfoのDIRECTION型に変換する
	 * @param  direction 方向
	 * @return           ReverseInfoのDIRECTION
	 */
	reversi::ReverseInfo::DIRECTION ToReverseInfoDirection(reversi::Move::DIRECTION direction);

private:
	MOVE_CACHE moveCacheEnableMove; // 着手のキャッシュデータ(打てる場所だけ)
};

}

#endif  // REVERSI_LOGIC_BASE_MOVE_H_
