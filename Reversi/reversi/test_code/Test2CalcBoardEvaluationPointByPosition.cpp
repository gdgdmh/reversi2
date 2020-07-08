#include "Test2CalcBoardEvaluationPointByPosition.h"

// test
#include "../logic/base/Board.h"
#include "../logic/base/Move.h"
#include "../logic/player/CalcBoardEvaluationPointByPosition.h"

/**
 * @brief コンストラクタ
 *
 * @param output_console 出力クラス
 */
test_code::Test2CalcBoardEvaluationPointByPosition::
    Test2CalcBoardEvaluationPointByPosition(
        std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * @brief デストラクタ
 *
 */
test_code::Test2CalcBoardEvaluationPointByPosition::
    ~Test2CalcBoardEvaluationPointByPosition() {}

/**
 * @brief ユニットテストの実行
 *
 */
void test_code::Test2CalcBoardEvaluationPointByPosition::ExecuteUnitTest() {
  {
    reversi::Board board;
    board.InitializeGame();

    reversi::CalcBoardEvaluationPointByPosition calcEval;
    int black = 0, white = 0;
    calcEval.CalcBoardEvaluationPoint(
        board, black, white, reversi::ReversiConstant::TURN::TURN_BLACK);
    // 初期配置では現在の評価値ではイコールになる(将来的に評価値の基準が変わったら前提を変更しても可)
    AssertEquals((black == white),
                 "TestCalcBoardEvaluationPointByPosition::Execute NOT "
                 "initialize position equal");
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
      AssertEquals(
          black > white,
          "TestCalcBoardEvaluationPointByPosition::Execute NOT eval up");
    } else {
      // 本来はこれはMoveのテストで検出されるべきだが一応
      AssertEquals(0, TestCalcBoardEvaluationPointByPosition::Execute NOT move);
    }
  }
}
