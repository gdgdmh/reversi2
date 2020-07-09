#include "Test2ThinkingNode.hpp"

#include "../logic/base/ThinkingNode.h"

/**
 * コンストラクタ
 */
test_code::Test2ThinkingNode::Test2ThinkingNode(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test_code::Test2ThinkingNode::~Test2ThinkingNode() {}

/**
 * @brief テストの実行
 *
 */
void test_code::Test2ThinkingNode::ExecuteUnitTest() {
  reversi::Reversi reversi;
  {
    reversi::Reversi::PLAYER_SETTING setting;
    setting.playerType[reversi::Reversi::PLAYER_BLACK] =
        reversi::Reversi::PLAYER::CPU1;
    setting.playerType[reversi::Reversi::PLAYER_WHITE] =
        reversi::Reversi::PLAYER::CPU1;
    reversi.Initialize();
    reversi.InitializeGame(setting);
    reversi.SetOutputEnable(false);

    // 着手後まで進める
    reversi.Task();
    reversi.Task();
    reversi.Task();
  }

  // root set
  reversi::ThinkingNode root;
  {
    reversi::ThinkingNode* parent = NULL;
    reversi::ReversiConstant::POSITION position =
        reversi::ReversiConstant::POSITION::A2;
    reversi::ReversiConstant::TURN turn =
        reversi::ReversiConstant::TURN::TURN_WHITE;
    int evalPoint = 10;
    int thinkDepth = 0;
    bool visited = true;

    root.CopyReversi(reversi);
    // root.SetParent(parent);
    root.SetMovePosition(position);
    root.SetTurn(turn);
    root.SetEvaluationPoint(evalPoint);
    root.SetThinkingDepth(thinkDepth);
    root.SetVisited(visited);

    AssertEquals(parent == root.GetParent(),
                 "TestThinkingNode::Execute invalid parent");
    AssertEquals(position == root.GetMovePosition(),
                 "TestThinkingNode::Execute invalid movePositon");
    AssertEquals(turn == root.GetTurn(),
                 "TestThinkingNode::Execute invalid turn");
    AssertEquals(evalPoint == root.GetEvaluationPoint(),
                 "TestThinkingNode::Execute invalid eval point");
    AssertEquals(thinkDepth == root.GetThinkingDepth(),
                 "TestThinkingNode::Execute invalid thinking depth");
    AssertEquals(visited == root.GetVisited(),
                 "TestThinkingNode::Execute invalid visited");
  }

  // child(rootの一つ下)を登録
  {
    reversi::ThinkingNode* child = new reversi::ThinkingNode();
    child->CopyReversi(reversi);
    child->SetMovePosition(reversi::ReversiConstant::POSITION::B1);
    child->SetTurn(reversi::ReversiConstant::TURN::TURN_BLACK);
    child->SetEvaluationPoint(11);
    child->SetThinkingDepth(1);

    root.AddChild(child);
  }
  // child(rootの一つ下 2つ目)を登録
  {
    reversi::ThinkingNode* child = new reversi::ThinkingNode();
    child->CopyReversi(reversi);
    child->SetMovePosition(reversi::ReversiConstant::POSITION::C1);
    child->SetTurn(reversi::ReversiConstant::TURN::TURN_BLACK);
    child->SetEvaluationPoint(12);
    child->SetThinkingDepth(1);

    root.AddChild(child);
  }
  // 最初のchildの下にchildを登録
  {
    reversi::ThinkingNode* child = new reversi::ThinkingNode();
    child->CopyReversi(reversi);
    // rootの下にchildが2つ登録している
    AssertEquals(root.GetChildSize() == 2,
                 "TestThinkingNode::Execute child size != 2");
    child->SetMovePosition(reversi::ReversiConstant::POSITION::D1);
    child->SetTurn(reversi::ReversiConstant::TURN::TURN_BLACK);
    child->SetEvaluationPoint(13);
    child->SetThinkingDepth(2);
    // 追加
    root.GetChild(0)->AddChild(child);
    AssertEquals(root.GetChild(0)->GetChildSize() == 1,
                 "TestThinkingNode::Execute root under child size failure");
  }
  // 評価値検索
  {
    // テストのためにfalseにする
    root.SetVisited(false);
    reversi::ThinkingNode* highNode = root.FindHighEvaluationPointNode();
    AssertEquals(highNode != NULL,
                 "TestThinkingNode::Execute highNode NULL failure");
    if (highNode == NULL) {
      // コンパイル警告対策
      return;
    }
    AssertEquals(highNode->GetEvaluationPoint() == 13,
                 "TestThinkingNode::Execute highNode value failure");
  }
  // 評価値検索(rootの1つ下のNodeの中で一番評価値が高いノードを探す)
  {
    reversi::ThinkingNode* highNode =
        root.FindHighEvaluationPointOneUnderNode();
    // 2つめのchildが選ばれるはず
    AssertEquals(highNode == root.GetChild(1),
                 "TestThinkingNode::Execute "
                 "FindHighEvaluationPointOneUnderNode failure");
  }

  // ノードのメモリ解放(デバッガでは確認済みなのでハングアップしなければ良しとする)
  root.ReleaseChild();
}
