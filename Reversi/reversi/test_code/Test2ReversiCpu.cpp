#include "Test2ReversiCpu.hpp"

#include "../../mhl/util/string/StdStringFormatter.hpp"
#include "../logic/base/Reversi.h"

/**
 * コンストラクタ
 */
test_code::Test2ReversiCpu::Test2ReversiCpu(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2ReversiCpu::~Test2ReversiCpu() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2ReversiCpu::ExecuteUnitTest() {
  // 基本的にはAssertEqualでチェックはせず、連続対局させる
  reversi::Reversi reversi;
  reversi::Reversi::PLAYER_SETTING setting;
  setting.playerType[reversi::Reversi::PLAYER_BLACK] =
      reversi::Reversi::PLAYER::CPU1;  // 黒
  setting.playerType[reversi::Reversi::PLAYER_WHITE] =
      reversi::Reversi::PLAYER::CPU2;  // 白

  reversi.Initialize();
  reversi.InitializeGame(setting);
  reversi.SetOutputEnable(false);

  const int TEST_COUNT = 1;  // CPUが対戦を行う回数
  const int MAX_STEP =
      200;  // ゲームのtaskコール回数の上限(これ以上長引くのは不自然)
  int testCount = 0;
  int blackWinCount = 0;
  int whiteWinCount = 0;
  int drawCount = 0;
  int stepCount = 0;

  while (testCount < TEST_COUNT) {
    reversi.Task();
    ++stepCount;
    AssertEquals(stepCount < MAX_STEP,
                 "Test2ReversiCpu::ExecuteUnitTest step over");
    if (reversi.GetScene() == reversi::Reversi::SCENE::END) {
      reversi::Reversi::RESULT result = reversi.GetResult();
      switch (result) {
        case reversi::Reversi::RESULT::BLACK:
          ++blackWinCount;
          break;
        case reversi::Reversi::RESULT::WHITE:
          ++whiteWinCount;
          break;
        case reversi::Reversi::RESULT::DRAW:
          ++drawCount;
          break;
        default:
          break;
      }
      reversi.InitializeGame(setting);
      ++testCount;
    }
  }
}

/*
bool reversi::TestReversiCpu::Execute() {
  // 基本的にはAssertEqualでチェックはせず、連続対局させる
  reversi::Reversi reversi;
  reversi::Reversi::PLAYER_SETTING setting;
  setting.playerType[reversi::Reversi::PLAYER_BLACK] =
      reversi::Reversi::PLAYER::CPU4;  // 黒
  setting.playerType[reversi::Reversi::PLAYER_WHITE] =
      reversi::Reversi::PLAYER::CPU3;  // 白

  reversi.Initialize();
  reversi.InitializeGame(setting);

  const int TEST_COUNT = 0;  // CPUが対戦を行う回数
  int testCount = 0;
  int blackWinCount = 0;
  int whiteWinCount = 0;
  int drawCount = 0;

  while (testCount < TEST_COUNT) {
    reversi.Task();
    if (reversi.GetScene() == reversi::Reversi::SCENE::END) {
      reversi::Reversi::RESULT result = reversi.GetResult();
      switch (result) {
        case reversi::Reversi::RESULT::BLACK:
          ++blackWinCount;
          break;
        case reversi::Reversi::RESULT::WHITE:
          ++whiteWinCount;
          break;
        case reversi::Reversi::RESULT::DRAW:
          ++drawCount;
          break;
        default:
          break;
      }
      reversi.InitializeGame(setting);
      ++testCount;
    }
  }
  std::string resultMessage = reversi::StdStringFormatter::Format(
      "black %d whilte %d draw %d", blackWinCount, whiteWinCount, drawCount);
  outputConsole->PrintLine(resultMessage);

  return true;
}
*/
