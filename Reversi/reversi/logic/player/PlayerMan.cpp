#include "PLayerMan.h"
#include "MoveThinkingMan.h"
#include "../../util/OutputConsole.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::PlayerMan::PlayerMan() : moveThinking(NULL), console(NULL) {
}

/**
 * デストラクタ
 */
reversi::PlayerMan::~PlayerMan() {
	if (moveThinking) {
		delete moveThinking;
		moveThinking = NULL;
	}
	if (console) {
		delete console;
		console = NULL;
	}
}

/**
 * 初期化
 */
void reversi::PlayerMan::Initialize() {
	if (moveThinking == NULL) {
		moveThinking = new MoveThinkingMan(true);
	}
	if (console == NULL) {
		console = new OutputConsole();
	}
}

/**
 * 自分の手番が来たときに一度だけ呼ばれる
 * @param reversi   リバーシクラス
 * @param moveCache 着手キャッシュ
 * @param board     盤情報
 * @param turn      手番
 */
void reversi::PlayerMan::EventTurnStart(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::ReversiConstant::TURN turn) {
	moveThinking->InitializeMoveThinking(reversi, moveCache, board, turn);
}

/**
 * 着手処理
 * @param  reversi   リバーシクラス
 * @param  moveCache 着手キャッシュ
 * @param  board     盤情報
 * @param  move      着手情報
 * @param  turn      手番
 * @return           trueなら思考が完了
 */
bool reversi::PlayerMan::SelectMove(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::MoveInfo& move, reversi::ReversiConstant::TURN turn) {
	return moveThinking->MoveThinking(reversi, moveCache, board, move, turn);
}

/**
 * 着手後に呼ばれる
 */
void reversi::PlayerMan::EventMoveAfter() {
}
