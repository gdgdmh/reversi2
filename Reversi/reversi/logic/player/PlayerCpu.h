#ifndef REVERSI_LOGIC_PLAYER_PLAYERCPU_H_
#define REVERSI_LOGIC_PLAYER_PLAYERCPU_H_

#include "IPlayer.h"
#include "IMoveThinking.h"
#include "../base/ReversiConstant.h"
#include "../base/MoveInfo.h"

// 前方宣言
namespace reversi {
class Board;
}

namespace reversi {

// プレイヤー(CPU)クラス
class PlayerCpu : public IPlayer {
public:
	// CPUレベル
	enum class LEVEL {
		LEVEL1, // CPU LEVEL1
		LEVEL2, // CPU LEVEL2(Lv1に勝率6割)
		LEVEL3, // CPU LEVEL3(Lv2に勝率7割)
		LEVEL4  // CPU LEVEL4(Lv3に勝率9割)
	};
public:
	/**
	 * コンストラクタ
	 */
	PlayerCpu(reversi::PlayerCpu::LEVEL level);

	/**
	 * デストラクタ
	 */
	virtual ~PlayerCpu();

	/**
	 * 初期化
	 */
	void Initialize();

	/**
	 * 自分の手番が来たときに一度だけ呼ばれる
	 * @param reversi   リバーシクラス
	 * @param moveCache 着手キャッシュ
	 * @param board     盤情報
	 * @param turn      手番
	 */
	void EventTurnStart(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::ReversiConstant::TURN turn);

	/**
	 * 着手処理
	 * @param  reversi   リバーシクラス
	 * @param  moveCache 着手キャッシュ
	 * @param  board     盤情報
	 * @param  move      着手情報
	 * @param  turn      手番
	 * @return           trueなら思考が完了
	 */
	bool SelectMove(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::MoveInfo& move, reversi::ReversiConstant::TURN turn);

	/**
	 * 着手後に呼ばれる
	 */
	void EventMoveAfter();

private:
	IMoveThinking* moveThinking; // 思考インターフェース
};

}

#endif  // REVERSI_LOGIC_PLAYER_PLAYERCPU_H_
