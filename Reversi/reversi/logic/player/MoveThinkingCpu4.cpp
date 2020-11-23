#include "MoveThinkingCpu4.h"

#include <iostream>

#include "../../../mhl/util/output/output_console.hpp"
#include "../../util/Assert.h"
#include "../../util/StdStringFormatter.h"
#include "CalcBoardEvaluationPointByPosition.h"
#include "ICalcBoardEvaluationPoint.h"

// 定数定義
// 静的評価位置
const int reversi::MoveThinkingCpu4::STATIC_EVALUATION_POINTS
    [reversi::ReversiConstant::POSITION_SIZE] = {
        120, -30, 20, 5,  5,  20, -30, 120, -30, -40, -5, -5, -5, -5, -40, -30,
        20,  -5,  20, 3,  3,  20, -5,  20,  5,   -5,  3,  3,  3,  3,  -5,  5,
        5,   -5,  3,  3,  3,  3,  -5,  5,   20,  -5,  20, 3,  3,  20, -5,  20,
        -30, -40, -5, -5, -5, -5, -40, -30, 120, -30, 20, 5,  20, 20, -30, 120,
};

/**
 * コンストラクタ
 */
reversi::MoveThinkingCpu4::MoveThinkingCpu4() : console(NULL) {
  console.reset(new mhl::OutputConsole());
}

/**
 * デストラクタ
 */
reversi::MoveThinkingCpu4::~MoveThinkingCpu4() {
  console.reset();
}

/**
 * 思考初期化
 * 手番が来たときに一度だけ呼ばれる
 * @param  board    盤情報
 * @param  turn     手番
 * @return          trueなら思考が完了
 */
void reversi::MoveThinkingCpu4::InitializeMoveThinking(
    const reversi::Reversi& reversi, const reversi::Move& moveCache,
    const reversi::Board& board, reversi::ReversiConstant::TURN turn) {}

/**
 * 思考
 * @param  board    盤情報
 * @param  move     着手情報
 * @param  turn     手番
 * @return          trueなら思考が完了
 */
bool reversi::MoveThinkingCpu4::MoveThinking(
    const reversi::Reversi& reversi, const reversi::Move& moveCache,
    const reversi::Board& board, reversi::MoveInfo& move,
    reversi::ReversiConstant::TURN turn) {
  reversi::PerformanceCounter c;  // パフォーマンス計測カウンタ
  // rootノードを作成
  reversi::ThinkingNode root;
  // root設定
  {
    reversi::ReversiConstant::POSITION dummyPosition =
        reversi::ReversiConstant::POSITION::A1;
    root.CopyReversi(reversi);
    root.SetMovePosition(dummyPosition);  // rootにはMovePosition設定は不要
    root.SetTurn(reversi.GetTurn());
    root.SetEvaluationPoint(0);  // 設定不要
    root.SetThinkingDepth(0);    // rootなので0
  }

  c.Start();
  // rootの子ノードを作成(1手読み)
  SetThinkingChildNode(&root, reversi, board, turn);
  c.End();
  PrintTimeDiff("root child node", c);

  // rootノードの下に更に思考ノードを追加する
  // ただ現在は2手読みが現実的(思考時間、使用メモリ的に)
  reversi::ThinkingNode* node = &root;
  int size = node->GetChildSize();
  for (int i = 0; i < size; ++i) {
    reversi::ThinkingNode* child = node->GetChild(i);
    // 2手読み
    SetThinkingChildNode(child, child->GetReversi(),
                         child->GetReversi().GetBoard(), turn);
    // 3手読み以上は全幅検索の都合上非常に重たくなるので現段階では使わない
    // for (int j = 0; j < child->GetChildSize(); ++j) {
    //	reversi::ThinkingNode* child2 = child->GetChild(j);
    //	// 3手読み
    //	SetThinkingChildNode(child2, child2->GetReversi(),
    //child2->GetReversi().GetBoard(), turn); 	for (int k = 0; k <
    //child2->GetChildSize(); ++k) { 		reversi::ThinkingNode* child3 =
    //child2->GetChild(k);
    //		// 4手読み
    //		SetThinkingChildNode(child3, child3->GetReversi(),
    //child3->GetReversi().GetBoard(), turn);
    //	}
    //}
  }

  // 一番評価値が高い着手位置を取得する
  reversi::ReversiConstant::POSITION topHighPosition =
      reversi::ReversiConstant::POSITION::A1;
  {
    // rootの1つ下のノード達に自分の子ノードの中で一番評価値が高いノードを取得してもらう
    const reversi::ThinkingNode* topHighNode = NULL;
    int topHighNodeIndex = -1;
    for (int i = 0; i < root.GetChildSize(); ++i) {
      reversi::ThinkingNode* child = node->GetChild(i);
      const reversi::ThinkingNode* highNode =
          child->FindHighEvaluationPointNode();
      if ((topHighNode == NULL) && (highNode != NULL)) {
        // 初回更新
        topHighNode = highNode;
        topHighNodeIndex = i;
      } else if (highNode != NULL) {
        if (topHighNode->GetEvaluationPoint() <
            highNode->GetEvaluationPoint()) {
          // 更新
          topHighNode = highNode;
          topHighNodeIndex = i;
        }
      }
    }
    reversi::Assert::AssertEqual(
        topHighNodeIndex != -1,
        "MoveThinkingCpu4::MoveThinking topHighNodeIndex -1");
    topHighPosition = root.GetChild(topHighNodeIndex)->GetMovePosition();
  }
  // 子ノードを削除(動的に作成しているので使い終わったら開放する必要がある)
  root.ReleaseChild();

  const reversi::ReverseInfo& reverseInfo =
      moveCache.GetReverseInfo(topHighPosition);
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
reversi::ReversiConstant::BOARD_INFO reversi::MoveThinkingCpu4::GetTurnToStone(
    reversi::ReversiConstant::TURN turn) {
  if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
    return reversi::ReversiConstant::BOARD_INFO::BLACK;
  } else {
    return reversi::ReversiConstant::BOARD_INFO::WHITE;
  }
}

/**
 * 指定されたノードに子の思考ノードを追加する
 * @param node     追加対象ノード
 * @param reversi  リバーシクラス
 * @param board    盤情報
 * @param selfTurn 評価関数設定対象の手番
 */
void reversi::MoveThinkingCpu4::SetThinkingChildNode(
    reversi::ThinkingNode* node, const reversi::Reversi& reversi,
    const reversi::Board& board, reversi::ReversiConstant::TURN selfTurn) {
  reversi::PerformanceCounter c;  // パフォーマンス計測カウンタ

  reversi::ReversiConstant::POSITION moveEnablePositions[MOVE_ENABLE_DATA_SIZE];
  int moveEnableCount = 0;
  // かなりの大きさがあるのでヒープで確保する
  std::shared_ptr<reversi::ReverseInfo[MOVE_ENABLE_DATA_SIZE]> reverseInfos { new reversi::ReverseInfo[MOVE_ENABLE_DATA_SIZE] };

  //reversi::ReverseInfo* reverseInfos =
      //new reversi::ReverseInfo[MOVE_ENABLE_DATA_SIZE];
  int reverseInfoCount = 0;
  // 初期化(reverseInfoは不要)
  for (int i = 0; i < MOVE_ENABLE_DATA_SIZE; ++i) {
    reversi::Assert::AssertArrayRange(
        i, MOVE_ENABLE_DATA_SIZE,
        "MoveThinkingCpu4::SetThinkingChildNode moveEnablePositions index "
        "over(initialize)");
    moveEnablePositions[i] = reversi::ReversiConstant::POSITION::A1;
  }

  // 終局している
  if ((reversi.GetScene() == reversi::Reversi::SCENE::END) ||
      (reversi.GetScene() == reversi::Reversi::SCENE::RESULT)) {
    reverseInfos.reset();
    return;
  }

  // 今の手番
  reversi::ReversiConstant::TURN turn = reversi.GetTurn();

  c.Start();
  // 打てる位置を取得
  GetMoveEnableData(moveEnablePositions, moveEnableCount, MOVE_ENABLE_DATA_SIZE,
                    reverseInfos, reverseInfoCount, board, turn);
  c.End();
  PrintTimeDiff("SetThinkingChildNode GetMoveEnableData", c);

  // どこにも打てない
  if (moveEnableCount == 0) {
    reverseInfos.reset();
    return;
  }

  // 打てる場所分childを作成(全幅検索)
  int size = moveEnableCount;
  for (int i = 0; i < size; ++i) {
    c.Start();
    reversi::Assert::AssertArrayRange(i, size,
                                      "MoveThinkingCpu4::SetThinkingChildNode "
                                      "moveEnablePositions index over");
    reversi::ThinkingNode* child = new reversi::ThinkingNode();
    // リバーシをコピー
    reversi::Reversi childReversi;
    childReversi.CopyWithoutDynamicInstance(reversi);  // コピー
    childReversi.SetOutputEnable(false);               // 出力はoffにする
    c.End();
    PrintTimeDiff("SetThinkingChildNode CopyReversi", c);

    // 着手を作成
    reversi::MoveInfo::MOVE_INFO moveInfoData;
    moveInfoData.position = moveEnablePositions[i];
    moveInfoData.info = GetTurnToStone(turn);
    moveInfoData.turn = childReversi.GetTurn();  // ゲーム上の手番
    reversi::MoveInfo moveInfo(moveInfoData, reverseInfos[i]);

    c.Start();
    // 着手
    childReversi.SetMoveSimulation(moveInfo);
    childReversi.Task();
    c.End();
    PrintTimeDiff("SetThinkingChildNode Move", c);

    c.Start();
    // リバーシを次の着手シーンまで進める
    bool taskLoop = true;
    bool isEnded = false;  // 対局が終わっている
    while (taskLoop) {
      childReversi.Task();
      // 終局してないかチェック
      if ((childReversi.GetScene() == reversi::Reversi::SCENE::RESULT) ||
          (childReversi.GetScene() == reversi::Reversi::SCENE::END)) {
        isEnded = true;
        taskLoop = false;
      }
      if (childReversi.GetScene() ==
          reversi::Reversi::SCENE::MOVE_SELECT_START) {
        // 着手シーンに進んでいるのでタスク進行終了
        taskLoop = false;
      }
    }
    c.End();
    PrintTimeDiff("SetThinkingChildNode Scene", c);
    // childの情報を設定
    c.Start();
    child->CopyReversi(childReversi);
    child->SetMovePosition(moveInfoData.position);
    child->SetTurn(moveInfoData.turn);
    child->SetThinkingDepth(node->GetThinkingDepth() + 1);
    c.End();
    PrintTimeDiff("SetThinkingChildNode Set", c);

    c.Start();
    // 評価値計算
    ICalcBoardEvaluationPoint* calcEval =
        new CalcBoardEvaluationPointByPosition();
    int blackEval = 0, whiteEval = 0;
    calcEval->CalcBoardEvaluationPoint(board, blackEval, whiteEval, turn);
    if (calcEval) {
      delete calcEval;
      calcEval = NULL;
    }
    // selfTurnの人の評価値を取る
    int eval = 0;
    if (selfTurn == reversi::ReversiConstant::TURN::TURN_BLACK) {
      eval = blackEval;
    } else {
      eval = whiteEval;
    }
    child->SetEvaluationPoint(eval);
    c.End();
    PrintTimeDiff("SetThinkingChildNode CalcEval", c);

    // 親のノードにつなげる
    node->AddChild(child);
  }
  reverseInfos.reset();
}

/**
 * 着手可能情報を取得する
 * @param moveEnablePositions     着手可能位置配列
 * @param moveEnablePositionCount 着手可能位置数
 * @param moveEnablePositionSize  着手可能位置配列最大数
 * @param reverseInfos            裏返し情報配列
 * @param reverseInfoCount        裏返し情報数
 * @param board                   盤情報
 * @param turn                    手番
 */
void reversi::MoveThinkingCpu4::GetMoveEnableData(
    reversi::ReversiConstant::POSITION* moveEnablePositions,
    int& moveEnablePositionCount, int moveEnablePositionSize,
    std::shared_ptr<reversi::ReverseInfo[MOVE_ENABLE_DATA_SIZE]>& reverseInfos, int& reverseInfoCount,
    const reversi::Board& board, reversi::ReversiConstant::TURN turn) {
  moveEnablePositionCount = 0;
  reverseInfoCount = 0;
  // 着手キャッシュを作成
  reversi::Move moveCache;
  {
    // 空の位置を探す
    reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
    moveCache.FindEmptyPosition(board, emptyPosition);
    // 打てる位置を探す
    moveCache.FindPutEnablePosition(board, emptyPosition, turn);
  }

  int size = moveCache.GetReverseInfoSize();
  for (int i = 0; i < size; ++i) {
    reversi::Assert::AssertArrayRange(
        i, size,
        "MoveThinkingCpu4::GetMoveEnablePosition reverseInfo index over");
    const reversi::ReverseInfo& reverseInfo =
        moveCache.GetReverseInfoByIndex(i);
    // 打てる
    if (moveCache.CheckEnableMoveByCache(reverseInfo.GetPosition())) {
      reversi::Assert::AssertArrayRange(
          moveEnablePositionCount, moveEnablePositionSize,
          "MoveThinkingCpu4::GetMoveEnablePosition moveEnablePositionSize "
          "index over");
      // 打てる位置を保存
      moveEnablePositions[moveEnablePositionCount] = reverseInfo.GetPosition();
      ++moveEnablePositionCount;
      // 裏返し情報も取得
      reverseInfos[reverseInfoCount] = reverseInfo;
      ++reverseInfoCount;
    }
  }
}

/**
 * 処理時関出力
 * @param prefix  処理時間の前に出す出力文字列
 * @param counter 処理時間計測カウンタ
 */
void reversi::MoveThinkingCpu4::PrintTimeDiff(
    std::string prefix, const reversi::PerformanceCounter& counter) {
  // reversi::StdStringFormatter formatter;
  // console->PrintLine(prefix + formatter.Format(" %lf", counter.GetDiff()));
}
