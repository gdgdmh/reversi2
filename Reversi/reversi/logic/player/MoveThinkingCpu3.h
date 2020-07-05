#ifndef REVERSI_LOGIC_PLAYER_MOVETHINKINGCPU3_H_
#define REVERSI_LOGIC_PLAYER_MOVETHINKINGCPU3_H_

#include "IMoveThinking.h"
#include "../base/ReversiConstant.h"
#include "../base/MoveInfo.h"
#include "../base/Move.h"

// 前方宣言
namespace reversi {
class Board;
}

namespace reversi {

// プレイヤー(CPU)思考クラス LEVEL3
// 静的評価関数を使用する
class MoveThinkingCpu3 : public IMoveThinking {
private:
	// 静的評価位置
	// 石が置いてある場所によって評価をつける(ここの位置はいい、悪いなど)
	static const int STATIC_EVALUATION_POINTS[reversi::ReversiConstant::POSITION_SIZE];
	static const int DEFAULT_POINTS = -99999;   // 評価値チェックするときのデフォルト値
public:
	/**
	 * コンストラクタ
	 */
	MoveThinkingCpu3();

	/**
	 * デストラクタ
	 */
	virtual ~MoveThinkingCpu3();

	/**
	 * 思考初期化
	 * 手番が来たときに一度だけ呼ばれる
	 * @param reversi   リバーシクラス
	 * @param moveCache 着手キャッシュ
	 * @param board     盤情報
	 * @param turn      手番
	 */
	virtual void InitializeMoveThinking(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::ReversiConstant::TURN turn);

	/**
	 * 思考
	 * @param  reversi   リバーシクラス
	 * @param  moveCache 着手キャッシュ
	 * @param  board     盤情報
	 * @param  move      着手情報
	 * @param  turn      手番
	 * @return           trueなら思考が完了
	 */
	virtual bool MoveThinking(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::MoveInfo& move, reversi::ReversiConstant::TURN turn);

private:

	/**
	 * 手番から石を取得
	 * @param  turn 手番
	 * @return      盤情報(石)
	 */
	reversi::ReversiConstant::BOARD_INFO GetTurnToStone(reversi::ReversiConstant::TURN turn);

private:
	reversi::Move reversiMove; // 着手キャッシュ
};

}

#endif  // REVERSI_LOGIC_PLAYER_MOVETHINKINGCPU3_H_
