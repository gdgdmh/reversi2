#include "Test2Move.hpp"

#include "../logic/base/Board.h"
#include "../logic/base/Move.h"

/**
 * コンストラクタ
 */
test_code::Test2Move::Test2Move(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2Move::~Test2Move() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2Move::ExecuteUnitTest() {
  reversi::Board board;
  board.InitializeGame();

  // 初期化した盤に対して空の位置を取得する(初期位置の石には置けない)
  reversi::Move move;
  reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
  move.FindEmptyPosition(board, emptyPosition);

  {
    size_t size = emptyPosition.position.size();
    for (int i = 0; i < size; ++i) {
      reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
      // 初期位置の石のpositionは含まれていないことを確認
      AssertEquals((position != reversi::ReversiConstant::POSITION::D4) &&
                       (position != reversi::ReversiConstant::POSITION::E5) &&
                       (position != reversi::ReversiConstant::POSITION::E4) &&
                       (position != reversi::ReversiConstant::POSITION::D5),
                   "TestMove::Execute invalid findEmptyPosition");
    }
  }
  // 打つことができるか(黒) CheckEnableMove
  // D3, C4, F5, E6
  {
    // 空いている盤座標
    size_t size = emptyPosition.position.size();
    for (int i = 0; i < size; ++i) {
      reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
      switch (position) {
        // 黒はこの座標に打つことができる
        case reversi::ReversiConstant::POSITION::D3:
        case reversi::ReversiConstant::POSITION::C4:
        case reversi::ReversiConstant::POSITION::F5:
        case reversi::ReversiConstant::POSITION::E6: {
          reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(
              board, (int)position, reversi::ReversiConstant::TURN::TURN_BLACK);
          AssertEquals(
              reverseInfo.IsEnableMove(),
              "TestMove::Execute invalid CheckEnableMove black enable");
        } break;
        default: {
          reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(
              board, (int)position, reversi::ReversiConstant::TURN::TURN_BLACK);
          // 打てない
          AssertEquals(
              !reverseInfo.IsEnableMove(),
              "TestMove::Execute invalid CheckEnableMove black disable");
        } break;
      }
    }
  }
  // 打つことができるか(白)
  {
    // 空いている盤座標
    size_t size = emptyPosition.position.size();
    for (int i = 0; i < size; ++i) {
      reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
      switch (position) {
        // 白はこの座標に打つことができる
        case reversi::ReversiConstant::POSITION::E3:
        case reversi::ReversiConstant::POSITION::F4:
        case reversi::ReversiConstant::POSITION::C5:
        case reversi::ReversiConstant::POSITION::D6: {
          reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(
              board, (int)position, reversi::ReversiConstant::TURN::TURN_WHITE);
          AssertEquals(
              reverseInfo.IsEnableMove(),
              "TestMove::Execute invalid CheckEnableMove white enable");
        } break;
        default: {
          reversi::ReverseInfo reverseInfo = move.GetEnableMoveInfo(
              board, (int)position, reversi::ReversiConstant::TURN::TURN_WHITE);
          // 打てない
          AssertEquals(
              !reverseInfo.IsEnableMove(),
              "TestMove::Execute invalid CheckEnableMove white disable");
        } break;
      }
    }
  }

  // CheckEnableMoveByCache
  {
    reversi::Board board;
    board.InitializeGame();

    // 初期化した盤に対して空の位置を取得する(初期位置の石には置けない)
    reversi::Move move;
    reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
    move.FindEmptyPosition(board, emptyPosition);

    {
      // 黒の打てる位置を探す
      move.FindPutEnablePosition(board, emptyPosition,
                                 reversi::ReversiConstant::TURN::TURN_BLACK);

      // 空いている盤座標
      size_t size = emptyPosition.position.size();
      for (int i = 0; i < size; ++i) {
        reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
        switch (position) {
          // 黒はこの座標に打つことができる
          case reversi::ReversiConstant::POSITION::D3:
          case reversi::ReversiConstant::POSITION::C4:
          case reversi::ReversiConstant::POSITION::F5:
          case reversi::ReversiConstant::POSITION::E6:
            AssertEquals(move.CheckEnableMoveByCache(position),
                         "TestMove::Execute invalid CheckEnableMoveByCache "
                         "black enable");
            break;
          default:
            // 打てない
            AssertEquals(!move.CheckEnableMoveByCache(position),
                         "TestMove::Execute invalid CheckEnableMoveByCache "
                         "black disable");
            break;
        }
      }
    }

    {
      // 白の打てる位置を探す
      move.FindPutEnablePosition(board, emptyPosition,
                                 reversi::ReversiConstant::TURN::TURN_WHITE);

      // 空いている盤座標
      size_t size = emptyPosition.position.size();
      for (int i = 0; i < size; ++i) {
        reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
        switch (position) {
          // 白はこの座標に打つことができる
          case reversi::ReversiConstant::POSITION::E3:
          case reversi::ReversiConstant::POSITION::F4:
          case reversi::ReversiConstant::POSITION::C5:
          case reversi::ReversiConstant::POSITION::D6:
            AssertEquals(move.CheckEnableMoveByCache(position),
                         "TestMove::Execute invalid CheckEnableMoveByCache "
                         "white enable");
            break;
          default:
            // 打てない
            AssertEquals(!move.CheckEnableMoveByCache(position),
                         "TestMove::Execute invalid CheckEnableMoveByCache "
                         "white disable");
            break;
        }
      }
    }
  }
}
