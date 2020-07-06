#ifndef REVERSI_LOGIC_PLAYER_IPLAYER_H_
#define REVERSI_LOGIC_PLAYER_IPLAYER_H_

#include "../base/MoveInfo.h"
#include "../base/ReversiConstant.h"

// 前方宣言
namespace reversi {
class Reversi;
class Move;
class Board;
}  // namespace reversi

namespace reversi {

// プレイヤーベースクラス
class IPlayer {
 public:
  /**
   * デストラクタ
   */
  virtual ~IPlayer() {}

  /**
   * 初期化
   */
  virtual void Initialize() = 0;

  /**
   * 自分の手番が来たときに一度だけ呼ばれる
   * @param reversi   リバーシクラス
   * @param moveCache 着手キャッシュ
   * @param board     盤情報
   * @param turn      手番
   */
  virtual void EventTurnStart(const reversi::Reversi& reversi,
                              const reversi::Move& moveCache,
                              const reversi::Board& board,
                              reversi::ReversiConstant::TURN turn) = 0;

  /**
   * 着手処理
   * @param  reversi   リバーシクラス
   * @param  moveCache 着手キャッシュ
   * @param  board     盤情報
   * @param  move      着手情報
   * @param  turn      手番
   * @return           trueなら思考が完了
   */
  virtual bool SelectMove(const reversi::Reversi& reversi,
                          const reversi::Move& moveCache,
                          const reversi::Board& board, reversi::MoveInfo& move,
                          reversi::ReversiConstant::TURN turn) = 0;

  /**
   * 着手後に呼ばれる
   */
  virtual void EventMoveAfter() = 0;
};

}  // namespace reversi

#endif  // REVERSI_LOGIC_PLAYER_IPLAYER_H_
