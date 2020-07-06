#include "TestCalcBoardEvaluationPointByPosition.h"
// test
#include "../../logic/base/Board.h"
#include "../../logic/base/Move.h"
#include "../../logic/player/CalcBoardEvaluationPointByPosition.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::TestCalcBoardEvaluationPointByPosition::
    TestCalcBoardEvaluationPointByPosition(mhl::IOutputConsole* outputConsole)
    : UnitTestBase(outputConsole) {}

/**
 * デストラクタ
 */
reversi::TestCalcBoardEvaluationPointByPosition::
    ~TestCalcBoardEvaluationPointByPosition() {}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestCalcBoardEvaluationPointByPosition::Execute() {
  {
    reversi::Board board;
    board.InitializeGame();

    reversi::CalcBoardEvaluationPointByPosition calcEval;
    int black = 0, white = 0;
    calcEval.CalcBoardEvaluationPoint(
        board, black, white, reversi::ReversiConstant::TURN::TURN_BLACK);
    // 初期配置では現在の評価値ではイコールになる(将来的に評価値の基準が変わったら前提を変更しても可)
    if (!AssertEqual((black == white),
                     "TestCalcBoardEvaluationPointByPosition::Execute NOT "
                     "initialize position equal")) {
      return false;
    }
  }
  {
    reversi::Board board;
    board.InitializeGame();

    reversi::Move move;
    reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
    move.FindEmptyPosition(board, emptyPosition);
    move.FindPutEnablePosition(board, emptyPosition,
                               reversi::ReversiConstant::TURN::TURN_BLACK);

    reversi::ReversiConstant::POSITION position =
        reversi::ReversiConstant::POSITION::D3;
    if (move.CheckEnableMoveByCache(position)) {
      // 着手準備
      const reversi::ReverseInfo reverseInfo = move.GetReverseInfo(position);
      reversi::MoveInfo::MOVE_INFO moveInfo;
      moveInfo.position = reversi::ReversiConstant::POSITION::D3;
      moveInfo.info = reversi::ReversiConstant::BOARD_INFO::BLACK;
      moveInfo.turn = reversi::ReversiConstant::TURN::TURN_BLACK;
      reversi::MoveInfo moveInfoClass(moveInfo, reverseInfo);
      // 着手
      board.Move(moveInfoClass);

      reversi::CalcBoardEvaluationPointByPosition calcEval;
      int black = 0, white = 0;
      calcEval.CalcBoardEvaluationPoint(
          board, black, white, reversi::ReversiConstant::TURN::TURN_BLACK);
      // 着手することで現在の評価値では黒の評価値が少し上がる(将来的に評価値の基準が変わったら前提を変更しても可)
      if (!AssertEqual(
              (black > white),
              "TestCalcBoardEvaluationPointByPosition::Execute NOT eval up")) {
        return false;
      }
    } else {
      // 本来はこれはMoveのテストで検出されるべきだが一応
      if (!AssertEqual(
              0, "TestCalcBoardEvaluationPointByPosition::Execute NOT move")) {
        return false;
      }
    }
  }
  return true;
}
