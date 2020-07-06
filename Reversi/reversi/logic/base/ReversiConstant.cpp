#include "ReversiConstant.h"

#include "../../util/Assert.h"

// 全ての有効な座標の定義
const reversi::ReversiConstant::POSITION reversi::ReversiConstant::POSITIONS
    [reversi::ReversiConstant::POSITION_SIZE] = {
        reversi::ReversiConstant::POSITION::A1,
        reversi::ReversiConstant::POSITION::B1,
        reversi::ReversiConstant::POSITION::C1,
        reversi::ReversiConstant::POSITION::D1,
        reversi::ReversiConstant::POSITION::E1,
        reversi::ReversiConstant::POSITION::F1,
        reversi::ReversiConstant::POSITION::G1,
        reversi::ReversiConstant::POSITION::H1,
        reversi::ReversiConstant::POSITION::A2,
        reversi::ReversiConstant::POSITION::B2,
        reversi::ReversiConstant::POSITION::C2,
        reversi::ReversiConstant::POSITION::D2,
        reversi::ReversiConstant::POSITION::E2,
        reversi::ReversiConstant::POSITION::F2,
        reversi::ReversiConstant::POSITION::G2,
        reversi::ReversiConstant::POSITION::H2,
        reversi::ReversiConstant::POSITION::A3,
        reversi::ReversiConstant::POSITION::B3,
        reversi::ReversiConstant::POSITION::C3,
        reversi::ReversiConstant::POSITION::D3,
        reversi::ReversiConstant::POSITION::E3,
        reversi::ReversiConstant::POSITION::F3,
        reversi::ReversiConstant::POSITION::G3,
        reversi::ReversiConstant::POSITION::H3,
        reversi::ReversiConstant::POSITION::A4,
        reversi::ReversiConstant::POSITION::B4,
        reversi::ReversiConstant::POSITION::C4,
        reversi::ReversiConstant::POSITION::D4,
        reversi::ReversiConstant::POSITION::E4,
        reversi::ReversiConstant::POSITION::F4,
        reversi::ReversiConstant::POSITION::G4,
        reversi::ReversiConstant::POSITION::H4,
        reversi::ReversiConstant::POSITION::A5,
        reversi::ReversiConstant::POSITION::B5,
        reversi::ReversiConstant::POSITION::C5,
        reversi::ReversiConstant::POSITION::D5,
        reversi::ReversiConstant::POSITION::E5,
        reversi::ReversiConstant::POSITION::F5,
        reversi::ReversiConstant::POSITION::G5,
        reversi::ReversiConstant::POSITION::H5,
        reversi::ReversiConstant::POSITION::A6,
        reversi::ReversiConstant::POSITION::B6,
        reversi::ReversiConstant::POSITION::C6,
        reversi::ReversiConstant::POSITION::D6,
        reversi::ReversiConstant::POSITION::E6,
        reversi::ReversiConstant::POSITION::F6,
        reversi::ReversiConstant::POSITION::G6,
        reversi::ReversiConstant::POSITION::H6,
        reversi::ReversiConstant::POSITION::A7,
        reversi::ReversiConstant::POSITION::B7,
        reversi::ReversiConstant::POSITION::C7,
        reversi::ReversiConstant::POSITION::D7,
        reversi::ReversiConstant::POSITION::E7,
        reversi::ReversiConstant::POSITION::F7,
        reversi::ReversiConstant::POSITION::G7,
        reversi::ReversiConstant::POSITION::H7,
        reversi::ReversiConstant::POSITION::A8,
        reversi::ReversiConstant::POSITION::B8,
        reversi::ReversiConstant::POSITION::C8,
        reversi::ReversiConstant::POSITION::D8,
        reversi::ReversiConstant::POSITION::E8,
        reversi::ReversiConstant::POSITION::F8,
        reversi::ReversiConstant::POSITION::G8,
        reversi::ReversiConstant::POSITION::H8};
// 横方向の座標
const reversi::ReversiConstant::POSITION reversi::ReversiConstant::
    POSITION_HORIZONTALS[reversi::ReversiConstant::BOARD_SIZE_Y]
                        [reversi::ReversiConstant::BOARD_SIZE_X] = {
                            {reversi::ReversiConstant::POSITION::A1,
                             reversi::ReversiConstant::POSITION::B1,
                             reversi::ReversiConstant::POSITION::C1,
                             reversi::ReversiConstant::POSITION::D1,
                             reversi::ReversiConstant::POSITION::E1,
                             reversi::ReversiConstant::POSITION::F1,
                             reversi::ReversiConstant::POSITION::G1,
                             reversi::ReversiConstant::POSITION::H1},
                            {reversi::ReversiConstant::POSITION::A2,
                             reversi::ReversiConstant::POSITION::B2,
                             reversi::ReversiConstant::POSITION::C2,
                             reversi::ReversiConstant::POSITION::D2,
                             reversi::ReversiConstant::POSITION::E2,
                             reversi::ReversiConstant::POSITION::F2,
                             reversi::ReversiConstant::POSITION::G2,
                             reversi::ReversiConstant::POSITION::H2},
                            {reversi::ReversiConstant::POSITION::A3,
                             reversi::ReversiConstant::POSITION::B3,
                             reversi::ReversiConstant::POSITION::C3,
                             reversi::ReversiConstant::POSITION::D3,
                             reversi::ReversiConstant::POSITION::E3,
                             reversi::ReversiConstant::POSITION::F3,
                             reversi::ReversiConstant::POSITION::G3,
                             reversi::ReversiConstant::POSITION::H3},
                            {reversi::ReversiConstant::POSITION::A4,
                             reversi::ReversiConstant::POSITION::B4,
                             reversi::ReversiConstant::POSITION::C4,
                             reversi::ReversiConstant::POSITION::D4,
                             reversi::ReversiConstant::POSITION::E4,
                             reversi::ReversiConstant::POSITION::F4,
                             reversi::ReversiConstant::POSITION::G4,
                             reversi::ReversiConstant::POSITION::H4},
                            {reversi::ReversiConstant::POSITION::A5,
                             reversi::ReversiConstant::POSITION::B5,
                             reversi::ReversiConstant::POSITION::C5,
                             reversi::ReversiConstant::POSITION::D5,
                             reversi::ReversiConstant::POSITION::E5,
                             reversi::ReversiConstant::POSITION::F5,
                             reversi::ReversiConstant::POSITION::G5,
                             reversi::ReversiConstant::POSITION::H5},
                            {reversi::ReversiConstant::POSITION::A6,
                             reversi::ReversiConstant::POSITION::B6,
                             reversi::ReversiConstant::POSITION::C6,
                             reversi::ReversiConstant::POSITION::D6,
                             reversi::ReversiConstant::POSITION::E6,
                             reversi::ReversiConstant::POSITION::F6,
                             reversi::ReversiConstant::POSITION::G6,
                             reversi::ReversiConstant::POSITION::H6},
                            {reversi::ReversiConstant::POSITION::A7,
                             reversi::ReversiConstant::POSITION::B7,
                             reversi::ReversiConstant::POSITION::C7,
                             reversi::ReversiConstant::POSITION::D7,
                             reversi::ReversiConstant::POSITION::E7,
                             reversi::ReversiConstant::POSITION::F7,
                             reversi::ReversiConstant::POSITION::G7,
                             reversi::ReversiConstant::POSITION::H7},
                            {reversi::ReversiConstant::POSITION::A8,
                             reversi::ReversiConstant::POSITION::B8,
                             reversi::ReversiConstant::POSITION::C8,
                             reversi::ReversiConstant::POSITION::D8,
                             reversi::ReversiConstant::POSITION::E8,
                             reversi::ReversiConstant::POSITION::F8,
                             reversi::ReversiConstant::POSITION::G8,
                             reversi::ReversiConstant::POSITION::H8}};
// 位置の文字列テーブル(POSITIONSのindexに対応)
const std::string
    reversi::ReversiConstant::POSITION_STRINGS[ReversiConstant::POSITION_SIZE] =
        {"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "A2", "B2", "C2",
         "D2", "E2", "F2", "G2", "H2", "A3", "B3", "C3", "D3", "E3", "F3",
         "G3", "H3", "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4", "A5",
         "B5", "C5", "D5", "E5", "F5", "G5", "H5", "A6", "B6", "C6", "D6",
         "E6", "F6", "G6", "H6", "A7", "B7", "C7", "D7", "E7", "F7", "G7",
         "H7", "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"};

/**
 * 文字列から位置へ変換する
 * @param  positionString 変換する文字列
 * @param  position       変換された位置
 * @return                trueなら変換できた
 */
bool reversi::ReversiConstant::GetStringToPosition(
    const std::string& positionString,
    reversi::ReversiConstant::POSITION& position) {
  for (int i = 0; i < reversi::ReversiConstant::POSITION_SIZE; ++i) {
    reversi::Assert::AssertArrayRange(
        i, reversi::ReversiConstant::POSITION_SIZE,
        "ReversiConstant::GetStringToPosition index over POSITION_STRINGS");
    if (positionString == POSITION_STRINGS[i]) {
      reversi::Assert::AssertArrayRange(
          i, reversi::ReversiConstant::POSITION_SIZE,
          "ReversiConstant::GetStringToPosition index over POSITIONS");
      position = POSITIONS[i];
      return true;
    }
  }
  return false;
}

/**
 * 位置から文字列へ変換する
 * @param  position       変換する位置
 * @param  positionString 変換された文字列
 * @return                trueなら変換できた
 */
bool reversi::ReversiConstant::GetPositionToString(
    const reversi::ReversiConstant::POSITION& position,
    std::string& positionString) {
  // POSITONSとPOSITION_STRINGSのindexは対応している
  for (int i = 0; i < reversi::ReversiConstant::POSITION_SIZE; ++i) {
    reversi::Assert::AssertArrayRange(
        i, reversi::ReversiConstant::POSITION_SIZE,
        "ReversiConstant::GetPositionToString index over");
    if (position == POSITIONS[i]) {
      positionString = POSITION_STRINGS[i];
      return true;
    }
  }
  return false;
}

/**
 * POSITIONからindexへ変換する
 * @param  position 変換するposition
 * @return          変換されたindex(不正なindexのときは-1を返す)
 */
int reversi::ReversiConstant::GetPositionToIndex(
    const reversi::ReversiConstant::POSITION& position) {
  // POSITONSからindexを探す
  for (int i = 0; i < reversi::ReversiConstant::POSITION_SIZE; ++i) {
    reversi::Assert::AssertArrayRange(
        i, reversi::ReversiConstant::POSITION_SIZE,
        "ReversiConstant::GetPositionToIndex index over");
    if (position == POSITIONS[i]) {
      return i;
    }
  }
  // 見つからなかった
  return -1;
}

/**
 * 手番の切り替えをする
 * @param  turn 切り替えする手番
 * @return      切り替えされた手番
 */
reversi::ReversiConstant::TURN reversi::ReversiConstant::InvertTurn(
    const reversi::ReversiConstant::TURN& turn) {
  if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
    return reversi::ReversiConstant::TURN::TURN_WHITE;
  }
  return reversi::ReversiConstant::TURN::TURN_BLACK;
}
