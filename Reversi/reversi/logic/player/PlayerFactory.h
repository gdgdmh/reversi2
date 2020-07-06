#ifndef REVERSI_LOGIC_PLAYER_PLAYERFACTORY_H_
#define REVERSI_LOGIC_PLAYER_PLAYERFACTORY_H_

#include "IPlayer.h"

namespace reversi {

// プレイヤー生成クラス
class PlayerFactory {
 public:
  enum class TYPE {
    PLAYER_MAN,   // 人間プレイヤー
    PLAYER_CPU1,  // CPU LEVEL1
    PLAYER_CPU2,  // CPU LEVEL2
    PLAYER_CPU3,  // CPU LEVEL3
    PLAYER_CPU4   // CPU LEVEL4
  };

 public:
  /**
   * コンストラクタ
   */
  PlayerFactory();

  /**
   * デストラクタ
   */
  virtual ~PlayerFactory();

  /**
   * プレイヤーの生成
   * @param  type プレイヤーのタイプ
   * @return      生成されたプレイヤー
   */
  reversi::IPlayer* Create(reversi::PlayerFactory::TYPE type);
};

}  // namespace reversi

#endif  // REVERSI_LOGIC_PLAYER_PLAYERFACTORY_H_
