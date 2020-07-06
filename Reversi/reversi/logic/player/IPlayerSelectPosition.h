#ifndef REVERSI_LOGIC_PLAYER_IPLAYERSELECTPOSITION_H_
#define REVERSI_LOGIC_PLAYER_IPLAYERSELECTPOSITION_H_

#include "../base/ReversiConstant.h"

namespace reversi {

// プレイヤー位置選択インターフェース
class IPlayerSelectPosition {
 public:
  /**
   * デストラクタ
   */
  virtual ~IPlayerSelectPosition() {}

  /**
   * 位置選択を取得する
   * @param  position 選択した位置
   * @return          trueなら位置選択した
   */
  virtual bool GetSelectPosition(
      reversi::ReversiConstant::POSITION& position) = 0;
};

}  // namespace reversi

#endif  // REVERSI_LOGIC_PLAYER_IPLAYERSELECTPOSITION_H_
