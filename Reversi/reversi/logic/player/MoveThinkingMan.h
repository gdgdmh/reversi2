#ifndef REVERSI_LOGIC_PLAYER_MOVETHINKINGMAN_H_
#define REVERSI_LOGIC_PLAYER_MOVETHINKINGMAN_H_

#include <memory>
#include "../../../mhl/util/output/IOutputConsole.hpp"
#include "../base/Move.h"
#include "../base/MoveInfo.h"
#include "../base/ReversiConstant.h"
#include "IMoveThinking.h"
#include "IPlayerSelectPosition.h"

// 前方宣言
namespace reversi {
class Board;
}

namespace reversi {

// プレイヤー(MAN)思考クラス
// キーボードから着手位置の入力を取って着手を設定する
// また、ヒント機能も搭載(角を取れるか、大量獲得できるか)
class MoveThinkingMan : public IMoveThinking {
 public:
  static const int HINT_GET_STONE_COUNT = 5;  // ヒントが表示される石獲得数
 public:
  /**
   * コンストラクタ
   * @param useHint ヒントを使用するか
   */
  MoveThinkingMan(bool useHint);

  /**
   * デストラクタ
   */
  virtual ~MoveThinkingMan();

  /**
   * 思考初期化
   * 手番が来たときに一度だけ呼ばれる
   * @param reversi   リバーシクラス
   * @param moveCache 着手キャッシュ
   * @param board     盤情報
   * @param turn      手番
   */
  virtual void InitializeMoveThinking(const reversi::Reversi& reversi,
                                      const reversi::Move& moveCache,
                                      const reversi::Board& board,
                                      reversi::ReversiConstant::TURN turn);

  /**
   * 思考
   * @param  reversi   リバーシクラス
   * @param  moveCache 着手キャッシュ
   * @param  board     盤情報
   * @param  move      着手情報
   * @param  turn      手番
   * @return           trueなら思考が完了
   */
  virtual bool MoveThinking(const reversi::Reversi& reversi,
                            const reversi::Move& moveCache,
                            const reversi::Board& board,
                            reversi::MoveInfo& move,
                            reversi::ReversiConstant::TURN turn);

 private:
  /**
   * 入力から位置を取得する
   * @param  position 入力された位置
   * @return          trueなら入力された
   */
  bool GetPositionByInput(reversi::ReversiConstant::POSITION& position);

  /**
   * 手番から対応した石情報を取得する
   * @param  turn 手番
   * @return      対応した石
   */
  reversi::ReversiConstant::BOARD_INFO GetTurnToStone(
      reversi::ReversiConstant::TURN turn);

  /**
   * 角に置くことができるか
   * @param  move 着手キャッシュ
   * @return      trueなら置くことができる
   */
  bool CheckPutEnableCorner(const reversi::Move& move);

  /**
   * 角に置けるヒントメッセージ表示
   */
  void OutputHintMessageCorner();

  /**
   * 多くの石が獲得できるか
   * @param  move       着手キャッシュ
   * @param  stoneCount いくつの石を取得できるならチャンスとみなすか
   * @return            trueなら多くの石の獲得チャンスがある
   */
  bool CheckGetManyStoneChance(const reversi::Move& move, int stoneCount);

  /**
   * 多くの石が置けるヒントメッセージ表示
   */
  void OutputHintMessageManyStoneChance();

 private:
  reversi::Move reversiMove;  // 着手情報
  std::shared_ptr<reversi::IPlayerSelectPosition>
      playerSelectPosition;      // 位置選択インターフェース
  std::shared_ptr<mhl::IOutputConsole> console;  // コンソール出力
  bool useHint;                  // ヒントを使うか
};

}  // namespace reversi

#endif  // REVERSI_LOGIC_PLAYER_MOVETHINKINGMAN_H_
