#include "Test2ReverseInfo.hpp"
// test
#include "../../reversi/logic/base/ReverseInfo.h"

/**
 * コンストラクタ
 */
test_code::Test2ReverseInfo::Test2ReverseInfo(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2ReverseInfo::~Test2ReverseInfo() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2ReverseInfo::ExecuteUnitTest() {
  // 値がセットできたか
  reversi::ReverseInfo info(reversi::ReversiConstant::POSITION::B4,
                            reversi::ReversiConstant::TURN::TURN_BLACK);
  AssertEquals(reversi::ReversiConstant::POSITION::B4 == info.GetPosition(),
               "TestReverseInfo::Execute invalid position");
  AssertEquals(reversi::ReversiConstant::TURN::TURN_BLACK == info.GetTurn(),
               "TestReverseInfo::Execute invalid turn");
  // テストで情報を追加
  info.AddReversePosition(reversi::ReverseInfo::DIRECTION::UP,
                          reversi::ReversiConstant::POSITION::B3);
  info.AddReversePosition(reversi::ReverseInfo::DIRECTION::UP,
                          reversi::ReversiConstant::POSITION::B2);
  info.AddReversePosition(reversi::ReverseInfo::DIRECTION::DOWN,
                          reversi::ReversiConstant::POSITION::D3);
  info.AddReversePosition(reversi::ReverseInfo::DIRECTION::DOWN_LEFT,
                          reversi::ReversiConstant::POSITION::A3);
  // 方向のデータ数を確認
  AssertEquals(
      info.GetReversePositionCount(reversi::ReverseInfo::DIRECTION::UP) == 2,
      "TestReverseInfo::Execute invalid up count");
  AssertEquals(
      info.GetReversePositionCount(reversi::ReverseInfo::DIRECTION::DOWN) == 1,
      "TestReverseInfo::Execute invalid down count");
  AssertEquals(info.GetReversePositionCount(
                   reversi::ReverseInfo::DIRECTION::DOWN_LEFT) == 1,
               "TestReverseInfo::Execute invalid down left count");

  // indexからデータの中身を確認
  AssertEquals(
      info.GetReversePosition(reversi::ReverseInfo::DIRECTION::UP, 0) ==
          reversi::ReversiConstant::POSITION::B3,
      "TestReverseInfo::Execute invalid get reverse positon 1");
  AssertEquals(
      info.GetReversePosition(reversi::ReverseInfo::DIRECTION::UP, 1) ==
          reversi::ReversiConstant::POSITION::B2,
      "TestReverseInfo::Execute invalid get reverse positon 2");
  AssertEquals(
      info.GetReversePosition(reversi::ReverseInfo::DIRECTION::DOWN, 0) ==
          reversi::ReversiConstant::POSITION::D3,
      "TestReverseInfo::Execute invalid get reverse positon 3");
  AssertEquals(
      info.GetReversePosition(reversi::ReverseInfo::DIRECTION::DOWN_LEFT, 0) ==
          reversi::ReversiConstant::POSITION::A3,
      "TestReverseInfo::Execute invalid get reverse positon 4");
}
