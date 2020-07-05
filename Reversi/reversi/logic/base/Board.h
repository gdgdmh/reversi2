#ifndef REVERSI_LOGIC_BASE_BOARD_H_
#define REVERSI_LOGIC_BASE_BOARD_H_

#include <string>
#include <vector>
#include "ReversiConstant.h"
#include "ReverseInfo.h"
#include "MoveInfo.h"
#include "../render/IRenderBoard.h"

// 前方宣言
namespace reversi {
class IOutputConsole;
}

namespace reversi {

//  8x8の盤だが判定を考慮して全体を無効マスで囲う用にしている(Xが無効マス)
// XXXXXXXXXX
// X--------X
// X--------X
// X--------X
// X--------X
// X--------X
// X--------X
// X--------X
// X--------X
// XXXXXXXXXX
// リバーシ盤クラス
class Board {
public:
	typedef struct {
		int boardData[ReversiConstant::BOARD_SIZE]; // 盤
		int boardSizeX;                             // 盤のXサイズ
		int boardSizeY;                             // 盤のYサイズ
	} BOARD;
public:
	/**
	 * コンストラクタ
	 */
	Board();

	/**
	 * デストラクタ
	 */
	virtual ~Board();

	/**
	 * ゲーム開始前の初期化
	 */
	void InitializeGame();

	/**
	 * 着手処理
	 * @param  moveInfo    着手情報
	 * @return             trueなら正常 falseなら何かしらの理由で失敗
	 */
	bool Move(reversi::MoveInfo moveInfo);

	/**
	 * 盤の情報を取得する
	 * @param  position 盤の位置
	 * @return          盤情報
	 */
	ReversiConstant::BOARD_INFO GetBoardInfo(int position);

	/**
	 * 盤の情報をカウントする
	 * @param blackCount 現在の盤の黒石の数
	 * @param whiteCount 現在の盤の白石数
	 * @param noneCount  現在の盤の空白数
	 */
	void GetCount(int& blackCount, int& whiteCount, int& noneCount);

	/**
	 * 盤の表示(コンソール)
	 * @param console コンソール出力先
	 */
	void Render();

	/**
	 * 盤の生データを取得する
	 * @return 盤の生データ
	 */
	const BOARD& GetRawData() const;

	/**
	 * クローンを作成
	 * @return 複製データ
	 */
	Board Clone() const;

	/**
	 * 盤をコピーする
	 * @param source コピー元
	 */
	void Copy(const reversi::Board& source);

	/**
	 * 盤が埋まっているか
	 * @return trueなら埋まっている
	 */
	bool IsFull() const;

	/**
	 * 盤を埋める(デバッグ用)
	 * @param setInfo 埋めるために使う黒石か白石を指定
	 */
	void ExecuteFull(reversi::ReversiConstant::BOARD_INFO setInfo);

	/**
	 * 両者がパスするような盤面を設定する
	 */
	void SetDebugPass();

private:

	/**
	 * 盤のクリア(全て石なしとする)
	 */
	void Clear();

	/**
	 * 空の盤を設定する
	 */
	void SetEmpty();

	/**
	 * ゲーム開始のための初期配置設定
	 */
	void Preset();

	/**
	 * 空マスかどうかチェック
	 * @param  position 位置
	 * @return          trueなら空マス
	 */
	bool CheckEmpty(reversi::ReversiConstant::POSITION position);

	/**
	 * 手番から石を取得する(黒の手番なら黒の石)
	 * @param  turn 手番
	 * @return      手番に対応した石
	 */
	reversi::ReversiConstant::BOARD_INFO GetTurnToStone(reversi::ReversiConstant::TURN turn);

private:

	/**
	 * 盤の情報をセットする
	 * @param info     セットする盤情報
	 * @param position セットする位置
	 */
	void SetBoardInfo(reversi::ReversiConstant::BOARD_INFO info, reversi::ReversiConstant::POSITION position);

	/**
	 * 石をひっくり返す(黒 -> 白, 白 -> 黒)
	 * 石がなかったら何もしない
	 * @param position 位置
	 */
	void ReverseStone(reversi::ReversiConstant::POSITION position);

private:
	BOARD board;                // 盤情報
	IRenderBoard* renderBoard;  // 盤表示インターフェース
};

}

#endif  // REVERSI_LOGIC_BASE_BOARD_H_
