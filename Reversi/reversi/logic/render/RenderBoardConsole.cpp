#include "RenderBoardConsole.h"

#include "../../../mhl/util/output/output_console.hpp"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::RenderBoardConsole::RenderBoardConsole() {
  outputConsole = new mhl::OutputConsole();
}

/**
 * デストラクタ
 */
reversi::RenderBoardConsole::~RenderBoardConsole() {
  if (outputConsole) {
    delete outputConsole;
    outputConsole = NULL;
  }
}

/**
 * 盤の描画
 * @param board 盤
 */
void reversi::RenderBoardConsole::Render(const Board& board) {
  RenderConsole(board, outputConsole);
}

/**
 * 盤コンソール描画
 * @param board  盤
 * @param output コンソール出力クラス
 */
void reversi::RenderBoardConsole::RenderConsole(
    const Board& board, mhl::IOutputConsole* const output) {
  if (output == NULL) {
    return;
  }
  RenderBoardTop(output);
  for (int i = 0; i < reversi::ReversiConstant::BOARD_SIZE_Y; ++i) {
    RenderBoardLine(output);
    RenderBoardHorizontalCells(output, board, i + 1);
  }
  RenderBoardLine(output);
  // 表示イメージ
  /*
     　　　ａ　　　ｂ　　　ｃ　　　ｄ　　　ｅ　　　ｆ　　　ｇ　　　ｈ　　
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     １｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     ２｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     ３｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     ４｜　　　｜　　　｜　　　｜　○　｜　●　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     ５｜　　　｜　　　｜　　　｜　●　｜　○　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     ６｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     ７｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
     ８｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜
     　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋
   */
}

/**
 * 盤の上部の表示
 * @param console コンソール出力先
 */
void reversi::RenderBoardConsole::RenderBoardTop(
    mhl::IOutputConsole* const console) {
  if (console == NULL) {
    return;
  }
  std::string renderString =
      "　　　ａ　　　ｂ　　　ｃ　　　ｄ　　　ｅ　　　ｆ　　　ｇ　　　ｈ　　";
  console->PrintLine(renderString);
}

/**
 * 盤のラインの表示
 * @param console コンソール出力先
 */
void reversi::RenderBoardConsole::RenderBoardLine(
    mhl::IOutputConsole* const console) {
  if (console == NULL) {
    return;
  }
  std::string renderString =
      "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋";
  console->PrintLine(renderString);
}

/**
 * 盤の横一列マスの表示
 * @param console コンソール出力先
 * @param y       何列目か(1～8)
 */
void reversi::RenderBoardConsole::RenderBoardHorizontalCells(
    mhl::IOutputConsole* const console, const Board& board, int y) {
  if (console == NULL) {
    return;
  }
  reversi::Assert::AssertEqual(
      (y > 0) && (y <= reversi::ReversiConstant::BOARD_SIZE_Y),
      "Board::RenderBoardHorizontalCells() invalid y range");
  // コンパイラ警告対応(index overする可能性があると出てしまうので)
  if ((y <= 0) || (y > reversi::ReversiConstant::BOARD_SIZE_Y)) {
    return;
  }
  std::string out = GetFullWidth1Number(y) + "｜";
  int posY = y - 1;
  const reversi::Board::BOARD rawData = board.GetRawData();
  // 横一列の情報を取得して表示の文字列に変換
  for (int i = 0; i < reversi::ReversiConstant::BOARD_SIZE_X; ++i) {
    // POSITION_HORIZONTALSのindex overチェック
    Assert::AssertArrayRange(
        posY, reversi::ReversiConstant::BOARD_SIZE_Y,
        "Board::RenderBoardHorizontalCells() index over y");
    Assert::AssertArrayRange(
        i, reversi::ReversiConstant::BOARD_SIZE_X,
        "Board::RenderBoardHorizontalCells() index over x");
    // 横一列の位置取得
    int position = (int)reversi::ReversiConstant::POSITION_HORIZONTALS[posY][i];

    // boardのindex overチェック
    Assert::AssertArrayRange(
        position, reversi::ReversiConstant::BOARD_SIZE,
        "Board::RenderBoardHorizontalCells() index over board");
    // 盤の情報から表示文字列を結合
    out +=
        "　" +
        GetBoardInfoString(
            (reversi::ReversiConstant::BOARD_INFO)rawData.boardData[position]) +
        "　｜";
  }
  console->PrintLine(out);
}

/**
 * 盤の下部の表示
 * @param console コンソール出力先
 */
void reversi::RenderBoardConsole::RenderBoardBottom(
    mhl::IOutputConsole* const console) {
  if (console == NULL) {
    return;
  }
  std::string renderString =
      "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋";
  console->PrintLine(renderString);
}

/**
 * 全角数字1桁を取得する
 * @param  number 0～9までの数字
 * @return        全角数字
 */
std::string reversi::RenderBoardConsole::GetFullWidth1Number(int number) {
  switch (number) {
    case 0:
      return "０";
    case 1:
      return "１";
    case 2:
      return "２";
    case 3:
      return "３";
    case 4:
      return "４";
    case 5:
      return "５";
    case 6:
      return "６";
    case 7:
      return "７";
    case 8:
      return "８";
    case 9:
      return "９";
    default:
      return "";
  }
}

std::string reversi::RenderBoardConsole::GetBoardInfoString(
    reversi::ReversiConstant::BOARD_INFO info) {
  switch (info) {
    case reversi::ReversiConstant::BOARD_INFO::NONE:
      return "　";
    case reversi::ReversiConstant::BOARD_INFO::BLACK:
      return "●";
    case reversi::ReversiConstant::BOARD_INFO::WHITE:
      return "○";
    case reversi::ReversiConstant::BOARD_INFO::INVALID:
      return "X";  // 本来表示しない
    default:
      return "";
  }
}
