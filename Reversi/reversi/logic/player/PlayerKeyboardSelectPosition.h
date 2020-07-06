#ifndef REVERSI_LOGIC_PLAYER_PLAYERKEYBOARDSELECTPOSITION_H_
#define REVERSI_LOGIC_PLAYER_PLAYERKEYBOARDSELECTPOSITION_H_

#include "IPlayerSelectPosition.h"

namespace reversi {

// プレイヤーキーボード位置選択クラス
class PlayerKeyboardSelectPosition : public reversi::IPlayerSelectPosition {
 public:
  /**
   * コンストラクタ
   */
  PlayerKeyboardSelectPosition();

  /**
   * デストラクタ
   */
  virtual ~PlayerKeyboardSelectPosition();

  /**
   * 位置選択を取得する
   * @param  position 選択した位置
   * @return          trueなら位置選択した
   */
  bool GetSelectPosition(reversi::ReversiConstant::POSITION& position);

  /**
   * 大文字に変換する
   * @param targetString 変換対象の文字列
   */
  void TransformStringUpper(std::string& targetString);
};

}  // namespace reversi

#endif  // REVERSI_LOGIC_PLAYER_PLAYERKEYBOARDSELECTPOSITION_H_
