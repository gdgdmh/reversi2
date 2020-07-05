#ifndef REVERSI_LOGIC_PLAYER_CALCBOARDEVALUATIONPOINTBYPOSITION_H_
#define REVERSI_LOGIC_PLAYER_CALCBOARDEVALUATIONPOINTBYPOSITION_H_

#include "ICalcBoardEvaluationPoint.h"
#include "../../util/Assert.h"

namespace reversi {

// 位置から盤の評価値を計算する
class CalcBoardEvaluationPointByPosition : public ICalcBoardEvaluationPoint {
public:
	// 静的評価位置
	// 石が置いてある場所によって評価をつける(ここの位置はいい、悪いなど)
	static const int STATIC_EVALUATION_POINTS[reversi::ReversiConstant::POSITION_SIZE];
public:
	/**
	 * コンストラクタ
	 */
	CalcBoardEvaluationPointByPosition();

	/**
	 * デストラクタ
	 */
	virtual ~CalcBoardEvaluationPointByPosition();

	/**
	 * 盤評価値を計算する
	 * @param  board      盤
	 * @param  blackPoint 黒の評価値
	 * @param  whitePoint 白の評価値
	 * @param  turn       どの手番を評価するか
	 */
	virtual void CalcBoardEvaluationPoint(const reversi::Board& board, int& blackPoint, int& whitePoint, reversi::ReversiConstant::TURN turn);

private:

	/**
	 * 位置情報から評価値テーブルを参照して評価値に変換
	 * このメソッドは参照回数が多いはずなのでインラインにする
	 * @param  position 対象位置
	 * @return          評価値
	 */
	int PositionToPoint(const reversi::ReversiConstant::POSITION& position) {
		int positionIndex = reversi::ReversiConstant::GetPositionToIndex(position);
		reversi::Assert::AssertArrayRange(positionIndex, reversi::ReversiConstant::POSITION_SIZE, "CalcBoardEvaluationPointByPosition::PositionToPoint index over");
		return STATIC_EVALUATION_POINTS[positionIndex];
	}
};

}

#endif  // REVERSI_LOGIC_PLAYER_CALCBOARDEVALUATIONPOINTBYPOSITION_H_
