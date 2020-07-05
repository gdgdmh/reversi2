#include <iostream>
#include <algorithm>
#include "MoveThinkingMan.h"
#include "PlayerKeyboardSelectPosition.h"
#include "../../util/OutputConsole.h"
#include "../../util/Assert.h"
#include "../../util/IInputKeyboard.h"
#include "../../util/ConsoleInputKeyboard.h"

/**
 * コンストラクタ
 */
reversi::MoveThinkingMan::MoveThinkingMan(bool useHint) : playerSelectPosition(NULL), console(NULL), useHint(useHint) {
	playerSelectPosition = new reversi::PlayerKeyboardSelectPosition();
	console = new reversi::OutputConsole();
}

/**
 * デストラクタ
 */
reversi::MoveThinkingMan::~MoveThinkingMan() {
	if (console) {
		delete console;
		console = NULL;
	}
	if (playerSelectPosition) {
		delete playerSelectPosition;
		playerSelectPosition = NULL;
	}
}

/**
 * 思考初期化
 * 手番が来たときに一度だけ呼ばれる
 * @param  board    盤情報
 * @param  turn     手番
 * @return          trueなら思考が完了
 */
void reversi::MoveThinkingMan::InitializeMoveThinking(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::ReversiConstant::TURN turn) {
	// 計算済みのキャッシュをコピー
	reversiMove = moveCache;

	if (!useHint) {
		// ヒントを使わないので何もしない
		return;
	}
	// ヒント
	if (CheckPutEnableCorner(reversiMove)) {
		// 角が取れる
		OutputHintMessageCorner();
	}
	if (CheckGetManyStoneChance(reversiMove, HINT_GET_STONE_COUNT)) {
		// 石が多く獲得できる
		OutputHintMessageManyStoneChance();
	}

}

/**
 * 思考
 * @param  board    盤情報
 * @param  move     着手情報
 * @param  turn     手番
 * @return          trueなら思考が完了
 */
bool reversi::MoveThinkingMan::MoveThinking(const reversi::Reversi& reversi, const reversi::Move& moveCache, const reversi::Board& board, reversi::MoveInfo& move, reversi::ReversiConstant::TURN turn) {
	reversi::ReversiConstant::POSITION position = reversi::ReversiConstant::POSITION::A1;
	// 位置入力取得
	if (GetPositionByInput(position)) {
		// 入力した
		if (reversiMove.CheckEnableMoveByCache(position)) {
			// 打てるので確定
			reversi::MoveInfo::MOVE_INFO moveInfoData;
			moveInfoData.position = position;
			moveInfoData.info = GetTurnToStone(turn);
			moveInfoData.turn = turn;
			reversi::ReverseInfo reverseInfo = reversiMove.GetReverseInfo(position);
			reversi::MoveInfo moveInfo(moveInfoData, reverseInfo);
			// 着手情報を入力
			move.Copy(moveInfo);
			return true;
		}
	}
	return false;
}

/**
 * 入力から位置を取得する
 * @param  position 入力された位置
 * @return          trueなら入力された
 */
bool reversi::MoveThinkingMan::GetPositionByInput(reversi::ReversiConstant::POSITION& position) {
	return playerSelectPosition->GetSelectPosition(position);
}

/**
 * 手番から対応した石情報を取得する
 * @param  turn 手番
 * @return      対応した石
 */
reversi::ReversiConstant::BOARD_INFO reversi::MoveThinkingMan::GetTurnToStone(reversi::ReversiConstant::TURN turn) {
	if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
		return reversi::ReversiConstant::BOARD_INFO::BLACK;
	} else {
		return reversi::ReversiConstant::BOARD_INFO::WHITE;
	}
}

/**
 * 角に置くことができるか
 * @param  move 着手キャッシュ
 * @return      trueなら置くことができる
 */
bool reversi::MoveThinkingMan::CheckPutEnableCorner(const reversi::Move& move) {
	const int CORNER_COUNT = 4;
	// 角の位置
	reversi::ReversiConstant::POSITION cornerPositions[CORNER_COUNT] = {
		reversi::ReversiConstant::POSITION::A1,
		reversi::ReversiConstant::POSITION::H1,
		reversi::ReversiConstant::POSITION::A8,
		reversi::ReversiConstant::POSITION::H8,
	};

	int size = move.GetReverseInfoSize();
	for (int i = 0; i < size; ++i) {
		const reversi::ReverseInfo& reverseInfo = move.GetReverseInfoByIndex(i);
		reversi::ReversiConstant::POSITION position = reverseInfo.GetPosition();
		// 打てるか
		if (!move.CheckEnableMoveByCache(position)) {
			// 打てないなら確認しない
			continue;
		}
		// 角か
		for (int j = 0; j < CORNER_COUNT; ++j) {
			reversi::Assert::AssertArrayRange(j, CORNER_COUNT, "MoveThinkingMan::CheckPutEnableCorner index over");
			if (position == cornerPositions[j]) {
				// 角が取れる
				return true;
			}
		}
	}
	return false;
}

/**
 * 角に置けるヒントメッセージ表示
 */
void reversi::MoveThinkingMan::OutputHintMessageCorner() {
	console->PrintLine("ヒント: 角を取るチャンスです!");
}

/**
 * 多くの石が獲得できるか
 * @param  move       着手キャッシュ
 * @param  stoneCount いくつの石を取得できるならチャンスとみなすか
 * @return            trueなら多くの石の獲得チャンスがある
 */
bool reversi::MoveThinkingMan::CheckGetManyStoneChance(const reversi::Move& move, int stoneCount) {
	// stoneCount以上に取れる箇所を探す
	int size = move.GetReverseInfoSize();
	for (int i = 0; i < size; ++i) {
		const reversi::ReverseInfo& reverseInfo = move.GetReverseInfoByIndex(i);
		// 打てる
		if (!move.CheckEnableMoveByCache(reverseInfo.GetPosition())) {
			// 打てないならスキップ
			continue;
		}
		// 取れる石のトータル
		int total = reverseInfo.GetReversePositionCountTotal();
		if (total >= stoneCount) {
			// stoneCount以上に取れる場所がある
			return true;
		}
	}
	return false;
}

/**
 * 多くの石が置けるヒントメッセージ表示
 */
void reversi::MoveThinkingMan::OutputHintMessageManyStoneChance() {
	console->PrintLine("ヒント: 石の大量獲得チャンスです!");
}
