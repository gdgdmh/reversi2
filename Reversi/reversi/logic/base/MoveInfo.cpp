#include "MoveInfo.h"

#include "../../util/Assert.h"

/**
 * デフォルトコンストラクタ(IPlayer::SelectMove用なのでその他の用途では使わないこと)
 */
reversi::MoveInfo::MoveInfo()
    : reverseInfo(reversi::ReversiConstant::POSITION::A1,
                  reversi::ReversiConstant::TURN::TURN_BLACK) {
  moveInfo.position = reversi::ReversiConstant::POSITION::A1;
  moveInfo.turn = reversi::ReversiConstant::TURN::TURN_BLACK;
  moveInfo.info = reversi::ReversiConstant::BOARD_INFO::BLACK;
}

/**
 * コンストラクタ
 * @param moveInfo    着手情報
 * @param reverseInfo 裏返し情報
 */
reversi::MoveInfo::MoveInfo(MOVE_INFO moveInfo,
                            const reversi::ReverseInfo& reverseInfo)
    : moveInfo(moveInfo), reverseInfo(reverseInfo) {}

/**
 * デストラクタ
 */
reversi::MoveInfo::~MoveInfo() {}

/**
 * コピーする
 * @param source コピー元
 */
void reversi::MoveInfo::Copy(const reversi::MoveInfo& source) {
  moveInfo.position = source.moveInfo.position;
  moveInfo.turn = source.moveInfo.turn;
  moveInfo.info = source.moveInfo.info;
  reverseInfo = source.reverseInfo;
}

/**
 * 情報をクリアする
 */
void reversi::MoveInfo::Clear() {
  moveInfo.position = reversi::ReversiConstant::POSITION::A1;
  moveInfo.info = reversi::ReversiConstant::BOARD_INFO::NONE;
  moveInfo.turn = reversi::ReversiConstant::TURN::TURN_BLACK;
  reverseInfo.Clear();
}
