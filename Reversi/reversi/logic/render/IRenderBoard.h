#ifndef REVERSI_LOGIC_RENDER_IRENDERBOARD_H_
#define REVERSI_LOGIC_RENDER_IRENDERBOARD_H_

// 前方宣言
namespace reversi {
class Board;
}

namespace reversi {

// 盤描画インターフェースクラス
class IRenderBoard {
public:

	/**
	 * デストラクタ
	 */
	virtual ~IRenderBoard() {
	}

	/**
	 * 盤の描画
	 * @param board 盤
	 */
	virtual void Render(const reversi::Board& board) = 0;
};

}

#endif  // REVERSI_LOGIC_RENDER_IRENDERBOARD_H_
