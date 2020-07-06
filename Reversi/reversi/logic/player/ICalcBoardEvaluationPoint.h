#ifndef REVERSI_LOGIC_PLAYER_ICALCBOARDEVALUATIONPOINT_H_
#define REVERSI_LOGIC_PLAYER_ICALCBOARDEVALUATIONPOINT_H_

#include "../base/Board.h"
#include "../base/ReversiConstant.h"

namespace reversi {

// 盤評価値計算インターフェース
class ICalcBoardEvaluationPoint {
 public:
  /**
   * デストラクタ
   */
  virtual ~ICalcBoardEvaluationPoint() {}

  /**
   * 盤評価値を計算する
   * @param  board      盤
   * @param  blackPoint 黒の評価値
   * @param  whitePoint 白の評価値
   * @param  turn       どの手番を評価するか
   */
  virtual void CalcBoardEvaluationPoint(
      const reversi::Board& board, int& blackPoint, int& whitePoint,
      reversi::ReversiConstant::TURN turn) = 0;
};

}  // namespace reversi

#endif  // REVERSI_LOGIC_PLAYER_ICALCBOARDEVALUATIONPOINT_H_
