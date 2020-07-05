#include "TestThinkingNode.h"
// test
#include "../../logic/base/ThinkingNode.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::TestThinkingNode::TestThinkingNode(reversi::IOutputConsole* outputConsole) : UnitTestBase(outputConsole) {
}

/**
 * デストラクタ
 */
reversi::TestThinkingNode::~TestThinkingNode() {
}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestThinkingNode::Execute() {

	reversi::Reversi reversi;
	{
		reversi::Reversi::PLAYER_SETTING setting;
		setting.playerType[reversi::Reversi::PLAYER_BLACK] = reversi::Reversi::PLAYER::CPU1;
		setting.playerType[reversi::Reversi::PLAYER_WHITE] = reversi::Reversi::PLAYER::CPU1;
		reversi.Initialize();
		reversi.InitializeGame(setting);

		// 着手後まで進める
		reversi.Task();
		reversi.Task();
		reversi.Task(); 
	}

	// root set
	reversi::ThinkingNode root;
	{
		reversi::ThinkingNode* parent = NULL;
		reversi::ReversiConstant::POSITION position = reversi::ReversiConstant::POSITION::A2;
		reversi::ReversiConstant::TURN turn = reversi::ReversiConstant::TURN::TURN_WHITE;
		int evalPoint = 10;
		int thinkDepth = 0;
		bool visited = true;

		root.CopyReversi(reversi);
		//root.SetParent(parent);
		root.SetMovePosition(position);
		root.SetTurn(turn);
		root.SetEvaluationPoint(evalPoint);
		root.SetThinkingDepth(thinkDepth);
		root.SetVisited(visited);

		if (!AssertEqual(parent == root.GetParent(), "TestThinkingNode::Execute invalid parent")) {
			return false;
		}
		if (!AssertEqual(position == root.GetMovePosition(), "TestThinkingNode::Execute invalid movePositon")) {
			return false;
		}
		if (!AssertEqual(turn == root.GetTurn(), "TestThinkingNode::Execute invalid turn")) {
			return false;
		}
		if (!AssertEqual(evalPoint == root.GetEvaluationPoint(), "TestThinkingNode::Execute invalid eval point")) {
			return false;
		}
		if (!AssertEqual(thinkDepth == root.GetThinkingDepth(), "TestThinkingNode::Execute invalid thinking depth")) {
			return false;
		}
		if (!AssertEqual(visited == root.GetVisited(), "TestThinkingNode::Execute invalid visited")) {
			return false;
		}
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
		if (!AssertEqual(root.GetChildSize() == 2, "TestThinkingNode::Execute child size != 2")) {
			return false;
		}
		child->SetMovePosition(reversi::ReversiConstant::POSITION::D1);
		child->SetTurn(reversi::ReversiConstant::TURN::TURN_BLACK);
		child->SetEvaluationPoint(13);
		child->SetThinkingDepth(2);
		// 追加
		root.GetChild(0)->AddChild(child);
		if (!AssertEqual(root.GetChild(0)->GetChildSize() == 1, "TestThinkingNode::Execute root under child size failure")) {
			return false;
		}
	}
	// 評価値検索
	{
		// テストのためにfalseにする
		root.SetVisited(false);
		reversi::ThinkingNode* highNode = root.FindHighEvaluationPointNode();
		if (!AssertEqual(highNode != NULL, "TestThinkingNode::Execute highNode NULL failure")) {
			return false;
		}
		if (highNode == NULL) {
			// コンパイル警告対策
			return false;
		}
		if (!AssertEqual(highNode->GetEvaluationPoint() == 13, "TestThinkingNode::Execute highNode value failure")) {
			return false;
		}
	}
	// 評価値検索(rootの1つ下のNodeの中で一番評価値が高いノードを探す)
	{
		reversi::ThinkingNode* highNode = root.FindHighEvaluationPointOneUnderNode();
		// 2つめのchildが選ばれるはず
		if (!AssertEqual(highNode == root.GetChild(1), "TestThinkingNode::Execute FindHighEvaluationPointOneUnderNode failure")) {
			return false;
		}
	}

	// ノードのメモリ解放(デバッガでは確認済みなのでハングアップしなければ良しとする)
	root.ReleaseChild();

	return true;
}

