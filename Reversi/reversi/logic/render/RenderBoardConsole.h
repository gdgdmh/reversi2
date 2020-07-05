#ifndef REVERSI_LOGIC_RENDER_RENDERBOARDCONSOLE_H_
#define REVERSI_LOGIC_RENDER_RENDERBOARDCONSOLE_H_

#include "IRenderBoard.h"
#include "../../../mhl/util/output/IOutputConsole.hpp"
#include "../base/Board.h"

namespace reversi {

// 盤描画クラス
class RenderBoardConsole : public IRenderBoard {
public:
	/**
	 * コンストラクタ
	 */
	RenderBoardConsole();

	/**
	 * デストラクタ
	 */
	virtual ~RenderBoardConsole();

	/**
	 * 盤の描画
	 * @param board 盤
	 */
	virtual void Render(const Board& board);

private:

	/**
	 * 盤コンソール描画
	 * @param board  盤
	 * @param output コンソール出力クラス
	 */
	void RenderConsole(const Board& board, mhl::IOutputConsole* const output);

	/**
	 * 盤の上部の表示
	 * @param console コンソール出力先
	 */
	void RenderBoardTop(mhl::IOutputConsole* const console);

	/**
	 * 盤のラインの表示
	 * @param console コンソール出力先
	 */
	void RenderBoardLine(mhl::IOutputConsole* const console);

	/**
	 * 盤の横一列マスの表示
	 * @param console コンソール出力先
	 * @param y       何列目か(1～8)
	 */
	void RenderBoardHorizontalCells(mhl::IOutputConsole* const console, const Board& board, int y);

	/**
	 * 盤の下部の表示
	 * @param console コンソール出力先
	 */
	void RenderBoardBottom(mhl::IOutputConsole* const console);

	/**
	 * 全角数字1桁を取得する
	 * @param  number 0～9までの数字
	 * @return        全角数字
	 */
	std::string GetFullWidth1Number(int number);

	/**
	 * 石の表示用の文字列を取得する
	 * @param  info 盤情報
	 * @return      盤情報表示用文字列
	 */
	std::string GetBoardInfoString(ReversiConstant::BOARD_INFO info);


private:
	mhl::IOutputConsole* outputConsole; // コンソール出力
};

}

#endif  // REVERSI_LOGIC_RENDER_RENDERBOARDCONSOLE_H_
