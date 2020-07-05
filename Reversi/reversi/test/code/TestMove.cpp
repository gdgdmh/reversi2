#include "TestMove.h"
// test
#include "../../logic/base/Move.h"
#include "../../logic/base/Board.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::TestMove::TestMove(mhl::IOutputConsole* outputConsole) : UnitTestBase(outputConsole) {
}

/**
 * デストラクタ
 */
reversi::TestMove::~TestMove() {
}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestMove::Execute() {
	reversi::Board board;
	board.InitializeGame();

	// 初期化した盤に対して空の位置を取得する(初期位置の石には置けない)
	reversi::Move move;
	reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
	move.FindEmptyPosition(board, emptyPosition);

	{
		size_t size = emptyPosition.position.size();
		for (int i = 0; i < size; ++i) {
			reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
			// 初期位置の石のpositionは含まれていないことを確認
			if (!AssertEqual((position != reversi::ReversiConstant::POSITION::D4) && (position != reversi::ReversiConstant::POSITION::E5) && (position != reversi::ReversiConstant::POSITION::E4) && (position != reversi::ReversiConstant::POSITION::D5), "TestMove::Execute invalid findEmptyPosition")) {
				return false;
			}
		}
	}
	// 打つことができるか(黒) CheckEnableMove
	// D3, C4, F5, E6
	{
		// 空いている盤座標
		size_t size = emptyPosition.position.size();
		for (int i = 0; i < size; ++i) {
			reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
			switch (position) {
			// 黒はこの座標に打つことができる
			case reversi::ReversiConstant::POSITION::D3:
			case reversi::ReversiConstant::POSITION::C4:
			case reversi::ReversiConstant::POSITION::F5:
			case reversi::ReversiConstant::POSITION::E6:
			{
				reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(board, (int)position, reversi::ReversiConstant::TURN::TURN_BLACK);
				if (!AssertEqual(reverseInfo.IsEnableMove(), "TestMove::Execute invalid CheckEnableMove black enable")) {
					return false;
				}
			}
			break;
			default:
			{
				reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(board, (int)position, reversi::ReversiConstant::TURN::TURN_BLACK);
				// 打てない
				if (!AssertEqual(!reverseInfo.IsEnableMove(), "TestMove::Execute invalid CheckEnableMove black disable")) {
					return false;
				}
			}
			break;
			}
		}
	}
	// 打つことができるか(白)
	{
		// 空いている盤座標
		size_t size = emptyPosition.position.size();
		for (int i = 0; i < size; ++i) {
			reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
			switch (position) {
			// 白はこの座標に打つことができる
			case reversi::ReversiConstant::POSITION::E3:
			case reversi::ReversiConstant::POSITION::F4:
			case reversi::ReversiConstant::POSITION::C5:
			case reversi::ReversiConstant::POSITION::D6:
			{
				reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(board, (int)position, reversi::ReversiConstant::TURN::TURN_WHITE);
				if (!AssertEqual(reverseInfo.IsEnableMove(), "TestMove::Execute invalid CheckEnableMove white enable")) {
					return false;
				}
			}
			break;
			default:
			{
				reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(board, (int)position, reversi::ReversiConstant::TURN::TURN_WHITE);
				// 打てない
				if (!AssertEqual(!reverseInfo.IsEnableMove(), "TestMove::Execute invalid CheckEnableMove white disable")) {
					return false;
				}
			}
			break;
			}
		}
	}

	// CheckEnableMoveByCache
	{
		reversi::Board board;
		board.InitializeGame();

		// 初期化した盤に対して空の位置を取得する(初期位置の石には置けない)
		reversi::Move move;
		reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
		move.FindEmptyPosition(board, emptyPosition);

		{
			// 黒の打てる位置を探す
			move.FindPutEnablePosition(board, emptyPosition, reversi::ReversiConstant::TURN::TURN_BLACK);

			// 空いている盤座標
			size_t size = emptyPosition.position.size();
			for (int i = 0; i < size; ++i) {
				reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
				switch (position) {
				// 黒はこの座標に打つことができる
				case reversi::ReversiConstant::POSITION::D3:
				case reversi::ReversiConstant::POSITION::C4:
				case reversi::ReversiConstant::POSITION::F5:
				case reversi::ReversiConstant::POSITION::E6:
					if (!AssertEqual(move.CheckEnableMoveByCache(position), "TestMove::Execute invalid CheckEnableMoveByCache black enable")) {
						return false;
					}
					break;
				default:
					// 打てない
					if (!AssertEqual(!move.CheckEnableMoveByCache(position), "TestMove::Execute invalid CheckEnableMoveByCache black disable")) {
						return false;
					}
					break;
				}
			}
		}

		{
			// 白の打てる位置を探す
			move.FindPutEnablePosition(board, emptyPosition, reversi::ReversiConstant::TURN::TURN_WHITE);

			// 空いている盤座標
			size_t size = emptyPosition.position.size();
			for (int i = 0; i < size; ++i) {
				reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
				switch (position) {
				// 白はこの座標に打つことができる
				case reversi::ReversiConstant::POSITION::E3:
				case reversi::ReversiConstant::POSITION::F4:
				case reversi::ReversiConstant::POSITION::C5:
				case reversi::ReversiConstant::POSITION::D6:
					if (!AssertEqual(move.CheckEnableMoveByCache(position), "TestMove::Execute invalid CheckEnableMoveByCache white enable")) {
						return false;
					}
					break;
				default:
					// 打てない
					if (!AssertEqual(!move.CheckEnableMoveByCache(position), "TestMove::Execute invalid CheckEnableMoveByCache white disable")) {
						return false;
					}
					break;
				}
			}
		}
	}
	return true;
}
