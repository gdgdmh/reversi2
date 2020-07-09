#include "Test2Reversi.hpp"

#include "../logic/base/Reversi.h"

/**
 * コンストラクタ
 */
test_code::Test2Reversi::Test2Reversi(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2Reversi::~Test2Reversi() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2Reversi::ExecuteUnitTest() {
  reversi::Reversi reversi;
  reversi::Reversi::PLAYER_SETTING setting;
  setting.playerType[reversi::Reversi::PLAYER_BLACK] =
      reversi::Reversi::PLAYER::CPU1;
  setting.playerType[reversi::Reversi::PLAYER_WHITE] =
      reversi::Reversi::PLAYER::CPU1;

  reversi.Initialize();
  reversi.InitializeGame(setting);
  {
    reversi::Board board;
    board.SetDebugPass();
    reversi.CopyBoard(board);
  }
  // シーンの切り替わりをチェック(黒,白がパスになる -> 終局)
  reversi.Task();  // pass
  AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::PASS,
               "TestReversi::Execute pass test NOT PASS");
  reversi.Task();
  AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::MOVE_SELECT_START,
               "TestReversi::Execute pass test NOT MOVE_SELECT_START");
  reversi.Task();
  AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::PASS,
               "TestReversi::Execute pass test NOT PASS 2");
  reversi.Task();
  AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::MOVE_SELECT_START,
               "TestReversi::Execute pass test NOT MOVE_SELECT_START 2");
  reversi.Task();
  AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::RESULT,
               "TestReversi::Execute pass test NOT RESULT");
  reversi.Task();
  AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::END,
               "TestReversi::Execute pass test NOT END");
  // 石のカウントをチェック(着手不可で終局したので、黒に空白分がカウントされる)
  int black, white, none;
  const int BLACK_CNT = 63;
  const int WHITE_CNT = 1;
  const int NONE_CNT = 34;
  reversi.GetResultStone(black, white, none);
  AssertEquals(black == BLACK_CNT,
               "TestReversi::Execute pass test NOT BLACK_CNT");
  AssertEquals(white == WHITE_CNT,
               "TestReversi::Execute pass test NOT WHITE_CNT");
  AssertEquals(none == NONE_CNT, "TestReversi::Execute pass test NOT NONE_CNT");
}
