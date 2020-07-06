#include "MoveThinkingCpu1.h"

#include <iostream>

#include "../../../mhl/util/output/IOutputConsole.hpp"
#include "../../util/Assert.h"
#include "../../util/IRandomInt.h"
#include "../../util/StdRandomInt.h"

/**
 * コンストラクタ
 */
reversi::MoveThinkingCpu1::MoveThinkingCpu1() {}

/**
 * デストラクタ
 */
reversi::MoveThinkingCpu1::~MoveThinkingCpu1() {}

/**
 * 思考初期化
 * 手番が来たときに一度だけ呼ばれる
 * @param  board    盤情報
 * @param  turn     手番
 * @return          trueなら思考が完了
 */
void reversi::MoveThinkingCpu1::InitializeMoveThinking(
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
bool reversi::MoveThinkingCpu1::MoveThinking(
    const reversi::Reversi& reversi, const reversi::Move& moveCache,
    const reversi::Board& board, reversi::MoveInfo& move,
    reversi::ReversiConstant::TURN turn) {
  return MoveThinkingMinRandom(board, move, turn);
}

/**
 * 手番から石を取得する
 * @param  turn 手番
 * @return      手番の石
 */
reversi::ReversiConstant::BOARD_INFO reversi::MoveThinkingCpu1::GetTurnToStone(
    reversi::ReversiConstant::TURN turn) {
  if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
    return reversi::ReversiConstant::BOARD_INFO::BLACK;
  } else {
    return reversi::ReversiConstant::BOARD_INFO::WHITE;
  }
}

/**
 * 最小の着手をする
 * @param  board 盤情報
 * @param  move  着手情報
 * @param  turn  手番
 * @return       trueなら思考が完了
 */
bool reversi::MoveThinkingCpu1::MoveThinkingMin(
    const reversi::Board& board, reversi::MoveInfo& move,
    reversi::ReversiConstant::TURN turn) {
  // 取れる箇所が最小値の場所を探す
  reversi::ReversiConstant::POSITION minPosition =
      reversi::ReversiConstant::POSITION::A1;  // 仮
  int minCount = MIN_COUNT_DEFAULT;
  int minIndex = 0;
  int size = reversiMove.GetReverseInfoSize();
  bool isUpdate = false;
  for (int i = 0; i < size; ++i) {
    const reversi::ReverseInfo& reverseInfo =
        reversiMove.GetReverseInfoByIndex(i);
    int total = reverseInfo.GetReversePositionCountTotal();
    // 取れる数が少ない + 打てる
    if ((total < minCount) &&
        (reversiMove.CheckEnableMoveByCache(reverseInfo.GetPosition()))) {
      minPosition = reverseInfo.GetPosition();
      minCount = total;
      minIndex = i;
      isUpdate = true;
    }
  }
  // 1つでも打てる箇所があれば引っかかるはず
  reversi::Assert::AssertEquals(
      isUpdate, "MoveThinkingCpu1::MoveThinkingMin ReverseInfo not hit");

  // 着手情報を確定
  reversi::MoveInfo::MOVE_INFO moveInfoData;
  moveInfoData.position = minPosition;
  moveInfoData.info = GetTurnToStone(turn);
  moveInfoData.turn = turn;
  reversi::MoveInfo moveInfo(moveInfoData,
                             reversiMove.GetReverseInfoByIndex(minIndex));
  // 着手情報を入力
  move.Copy(moveInfo);
  return true;
}

/**
 * 最小の着手をする
 * 複数最小値がある場合、ランダム性あり
 * @param  board 盤情報
 * @param  move  着手情報
 * @param  turn  手番
 * @return       trueなら思考が完了
 */
bool reversi::MoveThinkingCpu1::MoveThinkingMinRandom(
    const reversi::Board& board, reversi::MoveInfo& move,
    reversi::ReversiConstant::TURN turn) {
  // 取れる箇所が最小値の場所を探す
  std::vector<int> minCandidateIndex;
  int minCount = MIN_COUNT_DEFAULT;

  {
    int size = reversiMove.GetReverseInfoSize();
    for (int i = 0; i < size; ++i) {
      const reversi::ReverseInfo& reverseInfo =
          reversiMove.GetReverseInfoByIndex(i);
      // 打てる
      if (reversiMove.CheckEnableMoveByCache(reverseInfo.GetPosition())) {
        // 取れる石のトータル
        int total = reverseInfo.GetReversePositionCountTotal();
        if (total == minCount) {
          // 今までに見つかった最小値と同じなので候補に追加する
          minCandidateIndex.push_back(i);
        } else if (total < minCount) {
          // 更に低い最小値が見つかったので今までのデータを消して候補に追加する
          minCandidateIndex.clear();
          minCount = total;
          minCandidateIndex.push_back(i);
        }
      }
    }
  }

  // 1つでも打てる箇所があれば引っかかるはず
  reversi::Assert::AssertEquals(
      minCandidateIndex.size() > 0,
      "MoveThinkingCpu1::MoveThinkingMinRandom ReverseInfo not hit");

  int useIndex = 0;  // 着手として使用するindex
  // 着手候補が複数あるときはランダムで選択
  {
    IRandomInt* random = new StdRandomInt();
    random->SetSeedByTime();
    // 使うindexをランダムで取得
    int randomIndex = random->Get(0, (int)minCandidateIndex.size() - 1);
    if (random) {
      delete random;
      random = NULL;
    }

    reversi::Assert::AssertArrayRange(
        randomIndex, (int)minCandidateIndex.size(),
        "MoveThinkingCpu1::MoveThinkingMinRandom index over minCandidateIndex");
    useIndex = minCandidateIndex[randomIndex];
    reversi::Assert::AssertArrayRange(useIndex,
                                      reversiMove.GetReverseInfoSize(),
                                      "MoveThinkingCpu1::MoveThinkingMinRandom "
                                      "index over reversiMove reverseInfo");
    const reversi::ReverseInfo& reverseInfo =
        reversiMove.GetReverseInfoByIndex(useIndex);
    // 着手情報を確定
    reversi::MoveInfo::MOVE_INFO moveInfoData;
    moveInfoData.position = reverseInfo.GetPosition();
    moveInfoData.info = GetTurnToStone(turn);
    moveInfoData.turn = turn;
    reversi::MoveInfo moveInfo(moveInfoData, reverseInfo);
    // 着手情報を入力
    move.Copy(moveInfo);
  }
  return true;
}
