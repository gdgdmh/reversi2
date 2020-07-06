#ifndef REVERSI_LOGIC_BASE_MOVEINFO_H_
#define REVERSI_LOGIC_BASE_MOVEINFO_H_

#include "ReverseInfo.h"
#include "ReversiConstant.h"

namespace reversi {

// 着手情報クラス
class MoveInfo {
 public:
  // 着手情報
  typedef struct {
    reversi::ReversiConstant::POSITION position;  // 位置
    reversi::ReversiConstant::BOARD_INFO info;    // 着手する石
    reversi::ReversiConstant::TURN turn;          // 手番
  } MOVE_INFO;

 public:
  /**
   * デフォルトコンストラクタ(IPlayer::SelectMove用なのでその他の用途では使わないこと)
   */
  MoveInfo();

  /**
   * コンストラクタ
   * @param moveInfo    着手情報
   * @param reverseInfo 裏返し情報
   */
  MoveInfo(MOVE_INFO moveInfo, const reversi::ReverseInfo& reverseInfo);

  /**
   * デストラクタ
   */
  virtual ~MoveInfo();

  /**
   * コピーする
   * @param source コピー元
   */
  void Copy(const MoveInfo& source);

  /**
   * 情報をクリアする
   */
  void Clear();

  /**
   * 着手情報取得
   * @return 着手情報
   */
  MOVE_INFO GetMoveInfo() const { return moveInfo; };

  /**
   * 裏返し情報を取得
   * @return 裏返し情報
   */
  reversi::ReverseInfo GetReverseInfo() const { return reverseInfo; }

 private:
  MOVE_INFO moveInfo;                // 着手情報
  reversi::ReverseInfo reverseInfo;  // 裏返し情報
};

}  // namespace reversi

#endif  // REVERSI_LOGIC_BASE_MOVEINFO_H_
