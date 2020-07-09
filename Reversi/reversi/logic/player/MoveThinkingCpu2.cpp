#include "MoveThinkingCpu2.h"

#include <iostream>

#include "../../../mhl/util/output/IOutputConsole.hpp"
#include "../../util/Assert.h"
#include "../../util/IRandomInt.h"
#include "../../util/StdRandomInt.h"

/**
 * コンストラクタ
 */
reversi::MoveThinkingCpu2::MoveThinkingCpu2() {}

/**
 * デストラクタ
 */
reversi::MoveThinkingCpu2::~MoveThinkingCpu2() {}

/**
 * 思考初期化
 * 手番が来たときに一度だけ呼ばれる
 * @param  board    盤情報
 * @param  turn     手番
 * @return          trueなら思考が完了
 */
void reversi::MoveThinkingCpu2::InitializeMoveThinking(
    const reversi::Reversi& reversi, const reversi::Move& moveCache,
    const reversi::Board& board, reversi::ReversiConstant::TURN turn) {
  // 計算済みのキャッシュをコピー
  reversiMove = moveCache;
}

/**
 * 思考
 * @param  board    盤情報
 * @param  move     着手情報
 * @param  turn     手番
 * @return          trueなら思考が完了
 */
bool reversi::MoveThinkingCpu2::MoveThinking(
    const reversi::Reversi& reversi, const reversi::Move& moveCache,
    const reversi::Board& board, reversi::MoveInfo& move,
    reversi::ReversiConstant::TURN turn) {
  int index = 0;
  if (CheckPutEnableCornerIndex(index, reversiMove)) {
    // 角における(indexを設定)
  } else {
    index = 0;
    // 着手候補indexを取得する
    std::vector<int> candidate;
    GetMaxReverseCountCandidateIndex(candidate, reversiMove);
    // 候補0はおかしい
    reversi::Assert::AssertEqual(
        candidate.size() > 0,
        "MoveThinkingCpu2::MoveThinking candidate index size 0");

    // 着手候補が複数あるときはランダムで選択
    {
      IRandomInt* random = new StdRandomInt();
      random->SetSeedByTime();
      // 使うindexをランダムで取得
      int randomIndex = random->Get(0, (int)candidate.size() - 1);
      if (random) {
        delete random;
        random = NULL;
      }
      reversi::Assert::AssertArrayRange(
          randomIndex, (int)candidate.size(),
          "MoveThinkingCpu2::MoveThinking index over candidate");
      index = candidate[randomIndex];
      reversi::Assert::AssertArrayRange(
          index, reversiMove.GetReverseInfoSize(),
          "MoveThinkingCpu2::MoveThinking index over reverseInfo");
    }
  }
  const reversi::ReverseInfo& reverseInfo =
      reversiMove.GetReverseInfoByIndex(index);
  // 着手情報を確定
  reversi::MoveInfo::MOVE_INFO moveInfoData;
  moveInfoData.position = reverseInfo.GetPosition();
  moveInfoData.info = GetTurnToStone(turn);
  moveInfoData.turn = turn;
  reversi::MoveInfo moveInfo(moveInfoData, reverseInfo);
  // 着手情報を入力
  move.Copy(moveInfo);
  return true;
}

/**
 * 手番から石を取得
 * @param  turn 手番
 * @return      盤情報(石)
 */
reversi::ReversiConstant::BOARD_INFO reversi::MoveThinkingCpu2::GetTurnToStone(
    reversi::ReversiConstant::TURN turn) {
  if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
    return reversi::ReversiConstant::BOARD_INFO::BLACK;
  } else {
    return reversi::ReversiConstant::BOARD_INFO::WHITE;
  }
}

/**
 * ひっくり返せる最大数の候補indexを取得する
 * @param candidate 候補
 * @param move      着手キャッシュ
 */
void reversi::MoveThinkingCpu2::GetMaxReverseCountCandidateIndex(
    std::vector<int>& candidate, const reversi::Move& move) {
  candidate.clear();
  // 取れる箇所が最大値の場所を探す
  int maxCount = MAX_COUNT_DEFAULT;

  int size = move.GetReverseInfoSize();
  for (int i = 0; i < size; ++i) {
    const reversi::ReverseInfo& reverseInfo = move.GetReverseInfoByIndex(i);
    // 打てる
    if (move.CheckEnableMoveByCache(reverseInfo.GetPosition())) {
      // 取れる石のトータル
      int total = reverseInfo.GetReversePositionCountTotal();
      if ((total == maxCount) && (maxCount > 0)) {
        // 今までに見つかった最大値と同じなので候補に追加する
        candidate.push_back(i);
      } else if (total > maxCount) {
        // 更に低い最小値が見つかったので今までのデータを消して候補に追加する
        candidate.clear();
        maxCount = total;
        candidate.push_back(i);
      }
    }
  }
  // 1つでも打てる箇所があれば引っかかるはず
  reversi::Assert::AssertEqual(
      candidate.size() > 0,
      "MoveThinkingCpu2::GetMaxReverseCountCandidateIndex ReverseInfo not hit");
}

/**
 * 取れる角があるかチェック
 * @param  cornerIndex 角のindex(ReverseInfo)
 * @param  move        着手キャッシュ
 * @return             trueなら見つかった
 */
bool reversi::MoveThinkingCpu2::CheckPutEnableCornerIndex(
    int& cornerIndex, const reversi::Move& move) {
  int size = move.GetReverseInfoSize();
  for (int i = 0; i < size; ++i) {
    const reversi::ReverseInfo& reverseInfo = move.GetReverseInfoByIndex(i);
    reversi::ReversiConstant::POSITION position = reverseInfo.GetPosition();
    // 打てるか
    if (!move.CheckEnableMoveByCache(position)) {
      continue;
    }
    // 角か
    if ((position == reversi::ReversiConstant::POSITION::A1) ||
        (position == reversi::ReversiConstant::POSITION::H1) ||
        (position == reversi::ReversiConstant::POSITION::A8) ||
        (position == reversi::ReversiConstant::POSITION::H8)) {
      cornerIndex = i;
      return true;
    }
  }
  return false;
}
