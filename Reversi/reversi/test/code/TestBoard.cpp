#include "TestBoard.h"
// test
#include "../../logic/base/Board.h"
#include "../../logic/base/Move.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::TestBoard::TestBoard(mhl::IOutputConsole* outputConsole)
    : UnitTestBase(outputConsole) {}

/**
 * デストラクタ
 */
reversi::TestBoard::~TestBoard() {}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestBoard::Execute() {
  {
    reversi::Board board;
    board.InitializeGame();

    // 盤が初期位置になっているかチェック
    int size = reversi::ReversiConstant::POSITION_SIZE;
    const reversi::Board::BOARD boardData = board.GetRawData();
    for (int i = 0; i < size; ++i) {
      reversi::Assert::AssertArrayRange(
          i, size, "TestBoard::Execute() position index over");

      reversi::ReversiConstant::POSITION position =
          (reversi::ReversiConstant::POSITION)
              reversi::ReversiConstant::POSITIONS[i];

      reversi::Assert::AssertArrayRange(
          (int)position, reversi::ReversiConstant::BOARD_SIZE,
          "TestBoard::Execute() board index over");

      reversi::ReversiConstant::BOARD_INFO info =
          (reversi::ReversiConstant::BOARD_INFO)
              boardData.boardData[(int)position];

      if ((position == reversi::ReversiConstant::POSITION::D4) ||
          (position == reversi::ReversiConstant::POSITION::E5)) {
        // 白の初期位置
        if (!AssertEqual(info == reversi::ReversiConstant::BOARD_INFO::WHITE,
                         "TestBoard::Execute() NOT WHITE")) {
          return false;
        }
      } else if ((position == reversi::ReversiConstant::POSITION::E4) ||
                 (position == reversi::ReversiConstant::POSITION::D5)) {
        // 黒の初期位置
        if (!AssertEqual(info == reversi::ReversiConstant::BOARD_INFO::BLACK,
                         "TestBoard::Execute() NOT BLACK")) {
          return false;
        }
      } else {
        // 空白
        if (!AssertEqual(info == reversi::ReversiConstant::BOARD_INFO::NONE,
                         "TestBoard::Execute() NOT NONE")) {
          return false;
        }
      }
    }
  }
  // 裏返し処理のチェック
  {
    reversi::Board board;
    board.InitializeGame();

    reversi::Move move;
    reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
    // 空マスの取得
    move.FindEmptyPosition(board, emptyPosition);
    // 黒のおける位置の取得
    move.FindPutEnablePosition(board, emptyPosition,
                               reversi::ReversiConstant::TURN::TURN_BLACK);

    // 打てるか(D3)
    reversi::ReversiConstant::POSITION position =
        reversi::ReversiConstant::POSITION::D3;
    AssertEqual(move.CheckEnableMoveByCache(position),
                "TestBoard::Execute() check not move");

    // 着手処理
    const reversi::ReverseInfo reverseInfo = move.GetReverseInfo(position);
    reversi::MoveInfo::MOVE_INFO moveInfo;
    moveInfo.position = reversi::ReversiConstant::POSITION::D3;
    moveInfo.info = reversi::ReversiConstant::BOARD_INFO::BLACK;
    moveInfo.turn = reversi::ReversiConstant::TURN::TURN_BLACK;
    reversi::MoveInfo moveInfoClass(moveInfo, reverseInfo);

    AssertEqual(board.Move(moveInfoClass), "TestBoard::Execute() not move");

    // 盤の状態のチェック(裏返しがちゃんとできているか)
    {
      int size = reversi::ReversiConstant::POSITION_SIZE;
      const reversi::Board::BOARD boardData = board.GetRawData();
      for (int i = 0; i < size; ++i) {
        reversi::Assert::AssertArrayRange(
            i, size, "TestBoard::Execute() position index over");
        reversi::ReversiConstant::POSITION position =
            (reversi::ReversiConstant::POSITION)
                reversi::ReversiConstant::POSITIONS[i];
        reversi::Assert::AssertArrayRange(
            (int)position, reversi::ReversiConstant::BOARD_SIZE,
            "TestBoard::Execute() board index over");
        reversi::ReversiConstant::BOARD_INFO info =
            (reversi::ReversiConstant::BOARD_INFO)
                boardData.boardData[(int)position];

        switch (position) {
          case reversi::ReversiConstant::POSITION::E5:
            // 白
            if (!AssertEqual(
                    info == reversi::ReversiConstant::BOARD_INFO::WHITE,
                    "TestBoard::Execute() NOT WHITE")) {
              return false;
            }
            break;
          case reversi::ReversiConstant::POSITION::D3:
          case reversi::ReversiConstant::POSITION::D4:
          case reversi::ReversiConstant::POSITION::E4:
          case reversi::ReversiConstant::POSITION::D5:
            // 黒
            if (!AssertEqual(
                    info == reversi::ReversiConstant::BOARD_INFO::BLACK,
                    "TestBoard::Execute() NOT BLACK")) {
              return false;
            }
            break;
          default:
            if (!AssertEqual(info == reversi::ReversiConstant::BOARD_INFO::NONE,
                             "TestBoard::Execute() NOT NONE")) {
              return false;
            }
            break;
        }
      }
    }
  }
  // 盤面Fullチェック
  {
    reversi::Board board;
    board.InitializeGame();

    board.ExecuteFull(reversi::ReversiConstant::BOARD_INFO::BLACK);
    // board.Render();

    int size = reversi::ReversiConstant::POSITION_SIZE;
    const reversi::Board::BOARD boardData = board.GetRawData();
    for (int i = 0; i < size; ++i) {
      reversi::Assert::AssertArrayRange(
          i, size, "TestBoard::Execute() position index over");
      reversi::ReversiConstant::POSITION position =
          (reversi::ReversiConstant::POSITION)
              reversi::ReversiConstant::POSITIONS[i];
      reversi::Assert::AssertArrayRange(
          (int)position, reversi::ReversiConstant::BOARD_SIZE,
          "TestBoard::Execute() board index over");
      reversi::ReversiConstant::BOARD_INFO info =
          (reversi::ReversiConstant::BOARD_INFO)
              boardData.boardData[(int)position];

      if (!AssertEqual(
              (info == reversi::ReversiConstant::BOARD_INFO::BLACK) ||
                  (info == reversi::ReversiConstant::BOARD_INFO::WHITE),
              "TestBoard::Execute() NOT FULL")) {
        return false;
      }
    }

    // 盤面が埋まったか
    if (!AssertEqual(board.IsFull(), "TestBoard::Execute() NOT FULL 2")) {
      return false;
    }
  }
  // カウント
  {
    reversi::Board board;
    board.InitializeGame();

    int black, white, none;
    board.GetCount(black, white, none);
    const int BLACK_CNT = 2;
    const int WHITE_CNT = 2;
    const int NONE_CNT =
        reversi::ReversiConstant::POSITION_SIZE - BLACK_CNT - WHITE_CNT;
    if (!AssertEqual(
            (black == BLACK_CNT) && (white == WHITE_CNT) && (none == NONE_CNT),
            "TestBoard::Execute() not count")) {
      return false;
    }
  }
  return true;
}
