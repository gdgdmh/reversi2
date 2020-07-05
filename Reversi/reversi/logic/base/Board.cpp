#include "Board.h"
#include "../../util/IOutputConsole.h"
#include "../../util/Assert.h"
#include "../render/RenderBoardConsole.h"

/**
 * コンストラクタ
 */
reversi::Board::Board() {
	Clear();
	board.boardSizeX = reversi::ReversiConstant::BOARD_SIZE_X;
	board.boardSizeY = reversi::ReversiConstant::BOARD_SIZE_Y;
	renderBoard = NULL;
}

/**
 * デストラクタ
 */
reversi::Board::~Board() {
	if (renderBoard) {
		delete renderBoard;
		renderBoard = NULL;
	}
}

/**
 * ゲーム開始前の初期化
 */
void reversi::Board::InitializeGame() {
	Clear();
	SetEmpty();
	Preset();
}

/**
 * 着手処理
 * @param  moveInfo    着手情報
 * @return             trueなら正常 falseなら何かしらの理由で失敗
 */
bool reversi::Board::Move(reversi::MoveInfo moveInfo) {
	reversi::MoveInfo::MOVE_INFO info = moveInfo.GetMoveInfo();
	reversi::ReverseInfo reverseInfo = moveInfo.GetReverseInfo();
	reversi::Assert::AssertEquals(info.position == reverseInfo.GetPosition(), "Board::Move position not same");

	// 着手位置のマスをチェック
	if (!CheckEmpty(info.position)) {
		// 空マスではない
		return false;
	}

	// 着手位置に石を置く
	reversi::ReversiConstant::BOARD_INFO boardInfo = GetTurnToStone(info.turn);
	SetBoardInfo(boardInfo, info.position);

	// 裏返し情報キャッシュから裏返す位置を取得
	for (int i = 0; i < reversi::ReverseInfo::MAX_DIRECTION; ++i) {
		reversi::Assert::AssertArrayRange(i, reversi::ReverseInfo::MAX_DIRECTION, "Board::Move index over i");
		int reverseCount = reverseInfo.GetReversePositionCount((reversi::ReverseInfo::DIRECTION)i);
		for (int j = 0; j < reverseCount; ++j) {
			reversi::Assert::AssertArrayRange(j, reverseCount, "Board::Move index over j");
			// 裏返す
			reversi::ReversiConstant::POSITION position = reverseInfo.GetReversePosition((reversi::ReverseInfo::DIRECTION)i, j);
			ReverseStone(position);
		}
	}
	return true;
}

/**
 * 盤の情報を取得する
 * @param  position 盤の位置
 * @return          盤情報
 */
reversi::ReversiConstant::BOARD_INFO reversi::Board::GetBoardInfo(int position) {
	reversi::Assert::AssertArrayRange((int)position, reversi::ReversiConstant::BOARD_SIZE, "Board::GetBoardInfo index over");
	return (reversi::ReversiConstant::BOARD_INFO)board.boardData[(int)position];
}

/**
 * 盤の情報をカウントする
 * @param blackCount 現在の盤の黒石の数
 * @param whiteCount 現在の盤の白石数
 * @param noneCount  現在の盤の空白数
 */
void reversi::Board::GetCount(int& blackCount, int& whiteCount, int& noneCount) {
	blackCount = 0;
	whiteCount = 0;
	noneCount = 0;
	int size = reversi::ReversiConstant::POSITION_SIZE;
	for (int i = 0; i < size; ++i) {
		reversi::Assert::AssertArrayRange(i, size, "Board::GetCount() position index over");
		// 位置を取得
		reversi::ReversiConstant::POSITION position = (reversi::ReversiConstant::POSITION)reversi::ReversiConstant::POSITIONS[i];
		// 位置から盤情報を取得
		reversi::Assert::AssertArrayRange((int)position, reversi::ReversiConstant::BOARD_SIZE, "Board::GetCount() board index over");
		reversi::ReversiConstant::BOARD_INFO info = (reversi::ReversiConstant::BOARD_INFO)board.boardData[(int)position];
		// それぞれの情報をカウント
		if (info == reversi::ReversiConstant::BOARD_INFO::BLACK) {
			++blackCount;
		} else if (info == reversi::ReversiConstant::BOARD_INFO::WHITE) {
			++whiteCount;
		} else if (info == reversi::ReversiConstant::BOARD_INFO::NONE) {
			++noneCount;
		}
	}
}

/**
 * 盤の表示(コンソール)
 * @param console コンソール出力先
 */
void reversi::Board::Render() {
	if (renderBoard == NULL) {
		renderBoard = new RenderBoardConsole();
	}
	renderBoard->Render(*this);
}

/**
 * 盤の生データを取得する
 * @return 盤の生データ
 */
const reversi::Board::BOARD& reversi::Board::GetRawData() const {
	return board;
}

/**
 * クローンを作成
 * @return 複製データ
 */
reversi::Board reversi::Board::Clone() const {
	Board dest;

	for (int i = 0; i < ReversiConstant::BOARD_SIZE; ++i) {
		reversi::Assert::AssertArrayRange(i, reversi::ReversiConstant::BOARD_SIZE, "Board::Clone() index over");
		dest.SetBoardInfo((reversi::ReversiConstant::BOARD_INFO)board.boardData[i], (reversi::ReversiConstant::POSITION)i);
	}
	dest.board.boardSizeX = board.boardSizeX;
	dest.board.boardSizeY = board.boardSizeY;
	if (dest.renderBoard) {
		delete dest.renderBoard;
		dest.renderBoard = NULL;
	}
	dest.renderBoard = NULL;
	return dest;
}

/**
 * 盤をコピーする
 * @param source コピー元
 */
void reversi::Board::Copy(const reversi::Board& source) {
	for (int i = 0; i < ReversiConstant::BOARD_SIZE; ++i) {
		reversi::Assert::AssertArrayRange(i, reversi::ReversiConstant::BOARD_SIZE, "Board::Clone() index over");
		SetBoardInfo((reversi::ReversiConstant::BOARD_INFO)source.board.boardData[i], (reversi::ReversiConstant::POSITION)i);
	}
	board.boardSizeX = source.board.boardSizeX;
	board.boardSizeY = source.board.boardSizeY;
	// renderBoardはコピーしない
}

/**
 * 盤が埋まっているか
 * @return trueなら埋まっている
 */
bool reversi::Board::IsFull() const {

	int size = reversi::ReversiConstant::POSITION_SIZE;
	for (int i = 0; i < size; ++i) {
		reversi::Assert::AssertArrayRange(i, size, "Board::IsFull() position index over");
		// 位置を取得
		reversi::ReversiConstant::POSITION position = (reversi::ReversiConstant::POSITION)reversi::ReversiConstant::POSITIONS[i];
		reversi::Assert::AssertArrayRange((int)position, reversi::ReversiConstant::BOARD_SIZE, "Board::IsFull() board index over");
		reversi::ReversiConstant::BOARD_INFO info = (reversi::ReversiConstant::BOARD_INFO)board.boardData[(int)position];
		if (info == reversi::ReversiConstant::BOARD_INFO::NONE) {
			// 空マスが1つでもあったら埋まってない
			return false;
		}
	}
	return true;
}

/**
 * 盤を埋める(デバッグ用)
 * @param setInfo 埋めるために使う黒石か白石を指定
 */
void reversi::Board::ExecuteFull(reversi::ReversiConstant::BOARD_INFO setInfo) {
	// 黒か白しか指定してはいけない
	reversi::Assert::AssertEquals((setInfo == reversi::ReversiConstant::BOARD_INFO::BLACK) || (setInfo == reversi::ReversiConstant::BOARD_INFO::WHITE), "Board::ExecuteFull() info not black or white");

	int size = reversi::ReversiConstant::POSITION_SIZE;
	for (int i = 0; i < size; ++i) {
		reversi::Assert::AssertArrayRange(i, size, "Board::ExecuteFull() position index over");
		// 位置を取得
		reversi::ReversiConstant::POSITION position = (reversi::ReversiConstant::POSITION)reversi::ReversiConstant::POSITIONS[i];
		reversi::Assert::AssertArrayRange((int)position, reversi::ReversiConstant::BOARD_SIZE, "Board::ExecuteFull() board index over");
		reversi::ReversiConstant::BOARD_INFO info = (reversi::ReversiConstant::BOARD_INFO)board.boardData[(int)position];
		if (info == reversi::ReversiConstant::BOARD_INFO::NONE) {
			// 空マスを埋める
			SetBoardInfo(setInfo, position);
		}
	}
}

/**
 * 両者がパスするような盤面を設定する
 */
void reversi::Board::SetDebugPass() {
	// 空の盤面
	Clear();
	SetEmpty();

	using namespace reversi;
	// パスしかできないような盤面を作る
	const int BLACK_COUNT = 29;
	ReversiConstant::POSITION blackPositions[BLACK_COUNT] = {
		ReversiConstant::POSITION::B1, ReversiConstant::POSITION::F1,
		ReversiConstant::POSITION::C2, ReversiConstant::POSITION::F2,
		ReversiConstant::POSITION::D3, ReversiConstant::POSITION::F3,
		ReversiConstant::POSITION::D4, ReversiConstant::POSITION::E4,
		ReversiConstant::POSITION::F4, ReversiConstant::POSITION::G4,
		ReversiConstant::POSITION::A5, ReversiConstant::POSITION::B5,
		ReversiConstant::POSITION::C5, ReversiConstant::POSITION::D5,
		ReversiConstant::POSITION::E5, ReversiConstant::POSITION::F5,
		ReversiConstant::POSITION::G5, ReversiConstant::POSITION::H5,
		ReversiConstant::POSITION::C6, ReversiConstant::POSITION::D6,
		ReversiConstant::POSITION::E6, ReversiConstant::POSITION::C7,
		ReversiConstant::POSITION::D7, ReversiConstant::POSITION::E7,
		ReversiConstant::POSITION::C8, ReversiConstant::POSITION::D8,
		ReversiConstant::POSITION::E8, ReversiConstant::POSITION::F8,
		ReversiConstant::POSITION::G8,
	};
	for (int i = 0; i < BLACK_COUNT; ++i) {
		reversi::Assert::AssertArrayRange(i, BLACK_COUNT, "Board::SetDebugPass index over");
		SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::BLACK, blackPositions[i]);
	}
	SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::WHITE, ReversiConstant::POSITION::H3);
}

/**
 * 盤のクリア(全て石なしとする)
 */
void reversi::Board::Clear() {
	for (int i = 0; i < reversi::ReversiConstant::BOARD_SIZE; ++i) {
		reversi::Assert::AssertArrayRange(i, reversi::ReversiConstant::BOARD_SIZE, "Board::Clear() index over");
		SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::INVALID, (reversi::ReversiConstant::POSITION)i);
	}
}

/**
 * 空の盤を設定する
 */
void reversi::Board::SetEmpty() {
	for (int i = 0; i < reversi::ReversiConstant::POSITION_SIZE; ++i) {
		reversi::Assert::AssertArrayRange(i, reversi::ReversiConstant::POSITION_SIZE, "Board::SetEmpty() index over positions");
		reversi::Assert::AssertArrayRange((int)reversi::ReversiConstant::POSITIONS[i], reversi::ReversiConstant::BOARD_SIZE, "Board::SetEmpty() index over board");
		SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::NONE, reversi::ReversiConstant::POSITIONS[i]);
	}
}

/**
 * ゲーム開始のための初期配置設定
 */
void reversi::Board::Preset() {
	SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::WHITE, reversi::ReversiConstant::POSITION::D4);
	SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::WHITE, reversi::ReversiConstant::POSITION::E5);
	SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::BLACK, reversi::ReversiConstant::POSITION::E4);
	SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::BLACK, reversi::ReversiConstant::POSITION::D5);
}

/**
 * 空マスかどうかチェック
 * @param  position 位置
 * @return          trueなら空マス
 */
bool reversi::Board::CheckEmpty(reversi::ReversiConstant::POSITION position) {
	reversi::Assert::AssertArrayRange((int)position, reversi::ReversiConstant::BOARD_SIZE, "Board::CheckEmpty index over");
	if ((reversi::ReversiConstant::BOARD_INFO)board.boardData[(int)position] == reversi::ReversiConstant::BOARD_INFO::NONE) {
		return true;
	}
	return false;
}

/**
 * 手番から石を取得する(黒の手番なら黒の石)
 * @param  turn 手番
 * @return      手番に対応した石
 */
reversi::ReversiConstant::BOARD_INFO reversi::Board::GetTurnToStone(reversi::ReversiConstant::TURN turn) {
	switch (turn) {
	case reversi::ReversiConstant::TURN::TURN_BLACK:
		return reversi::ReversiConstant::BOARD_INFO::BLACK;
	case reversi::ReversiConstant::TURN::TURN_WHITE:
		return reversi::ReversiConstant::BOARD_INFO::WHITE;
	default:
		return reversi::ReversiConstant::BOARD_INFO::BLACK;
	}
}

/**
 * 盤の情報をセットする
 * @param info     セットする盤情報
 * @param position セットする位置
 */
void reversi::Board::SetBoardInfo(reversi::ReversiConstant::BOARD_INFO info, reversi::ReversiConstant::POSITION position) {
	reversi::Assert::AssertArrayRange((int)position, reversi::ReversiConstant::BOARD_SIZE, "Board::SetBoardInfo index over");
	board.boardData[(int)position] = (int)info;
}

/**
 * 石をひっくり返す(黒 -> 白, 白 -> 黒)
 * 石がなかったら何もしない
 * @param position 位置
 */
void reversi::Board::ReverseStone(reversi::ReversiConstant::POSITION position) {
	reversi::Assert::AssertArrayRange((int)position, reversi::ReversiConstant::BOARD_SIZE, "Board::SetBoardInfo index over");
	reversi::ReversiConstant::BOARD_INFO info = (reversi::ReversiConstant::BOARD_INFO)board.boardData[(int)position];

	// ひっくり返す
	switch (info) {
	case reversi::ReversiConstant::BOARD_INFO::BLACK:
		SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::WHITE, position);
		break;
	case reversi::ReversiConstant::BOARD_INFO::WHITE:
		SetBoardInfo(reversi::ReversiConstant::BOARD_INFO::BLACK, position);
		break;
	// 石でない場所を指定したら何もしない
	default:
		reversi::Assert::AssertEquals(0, "Board::ReverseStone not info black or white");
		break;
	}
}
