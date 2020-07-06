#include "CalcBoardEvaluationPointByPosition.h"

#include "../../util/Assert.h"

// 定数定義
// 静的評価(位置によるポイント)
const int reversi::CalcBoardEvaluationPointByPosition::STATIC_EVALUATION_POINTS
    [reversi::ReversiConstant::POSITION_SIZE] = {
        60,  -30, 20, 5,  5,  20, -30, 60,  -30, -40, -5, -5, -5, -5, -40, -30,
        20,  -5,  20, 3,  3,  20, -5,  20,  5,   -5,  3,  3,  3,  3,  -5,  5,
        5,   -5,  3,  3,  3,  3,  -5,  5,   20,  -5,  20, 3,  3,  20, -5,  20,
        -30, -40, -5, -5, -5, -5, -40, -30, 60,  -30, 20, 5,  20, 20, -30, 60,
};

/**
 * コンストラクタ
 */
reversi::CalcBoardEvaluationPointByPosition::
    CalcBoardEvaluationPointByPosition() {}

/**
 * デストラクタ
 */
reversi::CalcBoardEvaluationPointByPosition::
    ~CalcBoardEvaluationPointByPosition() {}

/**
 * 盤評価値を計算する
 * @param  board      盤
 * @param  blackPoint 黒の評価値
 * @param  whitePoint 白の評価値
 * @param  turn       どの手番を評価するか
 */
void reversi::CalcBoardEvaluationPointByPosition::CalcBoardEvaluationPoint(
    const reversi::Board& board, int& blackPoint, int& whitePoint,
    reversi::ReversiConstant::TURN turn) {
  blackPoint = 0;
  whitePoint = 0;
  reversi::Board::BOARD rawBoard = board.GetRawData();
  int size = reversi::ReversiConstant::BOARD_SIZE;
  // 盤面全体
  for (int i = 0; i < size; ++i) {
    reversi::Assert::AssertArrayRange(i, size,
                                      "CalcBoardEvaluationPointByPosition::"
                                      "CalcBoardEvaluationPoint() index over");
    // 石の置いてある位置に対して評価値を加算
    if (rawBoard.boardData[i] ==
        (int)reversi::ReversiConstant::BOARD_INFO::BLACK) {
      blackPoint += PositionToPoint((reversi::ReversiConstant::POSITION)i);
    } else if (rawBoard.boardData[i] ==
               (int)reversi::ReversiConstant::BOARD_INFO::WHITE) {
      whitePoint += PositionToPoint((reversi::ReversiConstant::POSITION)i);
    }
  }
}
