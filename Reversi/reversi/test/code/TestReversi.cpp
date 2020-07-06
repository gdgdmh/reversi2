#include "TestReversi.h"
// test
#include "../../logic/base/Reversi.h"
//#include "../../logic/base/Board.h"
//#include "../../logic/base/Move.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::TestReversi::TestReversi(mhl::IOutputConsole* outputConsole)
    : UnitTestBase(outputConsole) {}

/**
 * デストラクタ
 */
reversi::TestReversi::~TestReversi() {}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestReversi::Execute() {
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
  if (!AssertEqual(reversi.GetScene() == reversi::Reversi::SCENE::PASS,
                   "TestReversi::Execute pass test NOT PASS")) {
    return false;
  }
  reversi.Task();
  if (!AssertEqual(
          reversi.GetScene() == reversi::Reversi::SCENE::MOVE_SELECT_START,
          "TestReversi::Execute pass test NOT MOVE_SELECT_START")) {
    return false;
  }
  reversi.Task();
  if (!AssertEqual(reversi.GetScene() == reversi::Reversi::SCENE::PASS,
                   "TestReversi::Execute pass test NOT PASS 2")) {
    return false;
  }
  reversi.Task();
  if (!AssertEqual(
          reversi.GetScene() == reversi::Reversi::SCENE::MOVE_SELECT_START,
          "TestReversi::Execute pass test NOT MOVE_SELECT_START 2")) {
    return false;
  }
  reversi.Task();
  if (!AssertEqual(reversi.GetScene() == reversi::Reversi::SCENE::RESULT,
                   "TestReversi::Execute pass test NOT RESULT")) {
    return false;
  }
  reversi.Task();
  if (!AssertEqual(reversi.GetScene() == reversi::Reversi::SCENE::END,
                   "TestReversi::Execute pass test NOT END")) {
    return false;
  }
  // 石のカウントをチェック(着手不可で終局したので、黒に空白分がカウントされる)
  int black, white, none;
  const int BLACK_CNT = 63;
  const int WHITE_CNT = 1;
  const int NONE_CNT = 34;
  reversi.GetResultStone(black, white, none);
  if (!AssertEqual(black == BLACK_CNT,
                   "TestReversi::Execute pass test NOT BLACK_CNT")) {
    return false;
  }
  if (!AssertEqual(white == WHITE_CNT,
                   "TestReversi::Execute pass test NOT WHITE_CNT")) {
    return false;
  }
  if (!AssertEqual(none == NONE_CNT,
                   "TestReversi::Execute pass test NOT NONE_CNT")) {
    return false;
  }

  return true;
}
