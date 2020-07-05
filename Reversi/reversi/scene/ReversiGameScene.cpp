#include "ReversiGameScene.h"
#include "../../mhl/util/output/OutputConsole.hpp"
#include "../util/Assert.h"
#include "../game/KeyboardSelectYesNoWatching.h"
#include "../game/KeyboardSelectCpuLevel.h"
#include "../game/KeyboardSelectYesNo.h"

/**
 * コンストラクタ
 */
reversi::ReversiGameScene::ReversiGameScene() : console(NULL), scene(reversi::ReversiGameScene::SCENE::INITIALIZE), selectYesNoWatching(NULL),  selectCpuLevel(NULL), selectCpuLevel2(NULL), selectYesNo(NULL) {
}

/**
 * デストラクタ
 */
reversi::ReversiGameScene::~ReversiGameScene() {
	if (selectYesNoWatching) {
		delete selectYesNoWatching;
		selectYesNoWatching = NULL;
	}
	if (selectCpuLevel) {
		delete selectCpuLevel;
		selectCpuLevel = NULL;
	}
	if (selectCpuLevel2) {
		delete selectCpuLevel2;
		selectCpuLevel2 = NULL;
	}
	if (selectYesNo) {
		delete selectYesNo;
		selectYesNo;
	}
	if (console) {
		delete console;
		console = NULL;
	}
}

/**
 * 初期化
 */
void reversi::ReversiGameScene::Initialize() {
	// 一度しか初期化しない
	if (console == NULL) {
		console = new mhl::OutputConsole();
	}
	SetScene(reversi::ReversiGameScene::SCENE::INITIALIZE);
}

/**
 * メイン処理
 * @return falseなら終了
 */
bool reversi::ReversiGameScene::Task() {
	switch (scene) {
	case reversi::ReversiGameScene::SCENE::INITIALIZE:
		TaskInitialize();
		break;
	case reversi::ReversiGameScene::SCENE::REVERSI_ASK_PLAYER_SETTING:
		TaskAskPlayerSetting();
		break;
	case reversi::ReversiGameScene::SCENE::REVERSI_ASK_CPU_SETTING:
		TaskAskCpuSetting();
		break;
	case reversi::ReversiGameScene::SCENE::REVERSI_ASK_CPU2_SETTING:
		TaskAskCpu2Setting();
		break;
	case reversi::ReversiGameScene::SCENE::REVERSI_START:
		TaskReversiStart();
		break;
	case reversi::ReversiGameScene::SCENE::REVERSI_TASK:
		TaskReversiTask();
		break;
	case reversi::ReversiGameScene::SCENE::REVERSI_ASK_CONTINUE:
		TaskReversiAskContinue();
		break;
	case reversi::ReversiGameScene::SCENE::END:
		TaskEnd();
		return false;
	}
	return true;
}

/**
 * 初期化シーン
 */
void reversi::ReversiGameScene::TaskInitialize() {
	// ゲームの初期化に必要なインスタンス作成(再対局する際にも呼ばれる)
	CreateInitializeGameInstance();
	// 初期化
	selectYesNoWatching->Initialize();
	selectCpuLevel->Initialize();
	selectCpuLevel2->Initialize();
	selectYesNo->Initialize();
	console->PrintLine("黒石でプレイする場合はYes 白石でプレイする場合はNo CPU対局観戦する場合はWatching を入力してEnterを押してください");
	SetScene(reversi::ReversiGameScene::SCENE::REVERSI_ASK_PLAYER_SETTING);
}

/**
 * プレイヤー設定確認シーン
 */
void reversi::ReversiGameScene::TaskAskPlayerSetting() {
	selectYesNoWatching->Task();
	if (selectYesNoWatching->IsWrongInput()) {
		console->PrintLine("入力が間違っています、もう一度入力してください");
	}
	if (selectYesNoWatching->IsSelected()) {
		console->PrintLine("CPUの強さを数字で選択してください、数値が高いほど強いです 1 or 2 or 3 or 4");
		SetScene(reversi::ReversiGameScene::SCENE::REVERSI_ASK_CPU_SETTING);
	}
}

/**
 * CPU設定確認シーン
 */
void reversi::ReversiGameScene::TaskAskCpuSetting() {
	selectCpuLevel->Task();
	if (selectCpuLevel->IsWrongInput()) {
		console->PrintLine("入力が間違っています、もう一度入力してください");
	}
	if (selectCpuLevel->IsSelected()) {
		// 観戦を選択したときのみ2人目のCPU選択をする
		if (selectYesNoWatching->IsSelectWatching()) {
			console->PrintLine("2人目のCPUの強さを数字で選択してください、数値が高いほど強いです 1 or 2 or 3 or 4");
			SetScene(reversi::ReversiGameScene::SCENE::REVERSI_ASK_CPU2_SETTING);
			return;
		}
		// 対局開始
		SetScene(reversi::ReversiGameScene::SCENE::REVERSI_START);
	}
}

/**
 * CPU2人目瀬底確認シーン
 */
void reversi::ReversiGameScene::TaskAskCpu2Setting() {
	selectCpuLevel2->Task();
	if (selectCpuLevel2->IsWrongInput()) {
		console->PrintLine("入力が間違っています、もう一度入力してください");
	}
	if (selectCpuLevel2->IsSelected()) {
		// 対局開始
		SetScene(reversi::ReversiGameScene::SCENE::REVERSI_START);
	}
}

/**
 * リバーシ開始シーン
 */
void reversi::ReversiGameScene::TaskReversiStart() {
	// プレイヤー設定
	reversi::Reversi::PLAYER_SETTING setting;
	if (selectYesNoWatching->IsSelectYes()) {
		// プレイヤーが黒
		setting.playerType[reversi::Reversi::PLAYER_BLACK] = reversi::Reversi::PLAYER::MAN;
		setting.playerType[reversi::Reversi::PLAYER_WHITE] = NumberToCpuLevel(selectCpuLevel->GetCpuLevel());
	} else if (selectYesNoWatching->IsSelectNo()) {
		// プレイヤーが白
		setting.playerType[reversi::Reversi::PLAYER_BLACK] = NumberToCpuLevel(selectCpuLevel->GetCpuLevel());
		setting.playerType[reversi::Reversi::PLAYER_WHITE] = reversi::Reversi::PLAYER::MAN;
	} else if (selectYesNoWatching->IsSelectWatching()) {
		// CPU vs CPU
		setting.playerType[reversi::Reversi::PLAYER_BLACK] = NumberToCpuLevel(selectCpuLevel->GetCpuLevel());
		setting.playerType[reversi::Reversi::PLAYER_WHITE] = NumberToCpuLevel(selectCpuLevel2->GetCpuLevel());
	}
	// リバーシロジックの初期化
	reversi.Initialize();
	reversi.InitializeGame(setting);
	SetScene(reversi::ReversiGameScene::SCENE::REVERSI_TASK);
}

/**
 * リバーシメインシーン
 */
void reversi::ReversiGameScene::TaskReversiTask() {
	reversi.Task();
	if (reversi.GetScene() == reversi::Reversi::SCENE::END) {
		if (IsPlayerWin()) {
			// プレイヤーの勝ち
			OutputPlayerWinMessage();
		} else if (IsPlayerLose()) {
			// プレイヤーの負け
			OutputPlayerLoseMessage();
		} else if (IsPlayerDraw()) {
			// プレイヤーの引き分け
			OutputPlayerDrawMessage();
		}
		// 再対局確認
		console->PrintLine("再対局しますか？(入力例 Yes または No)");
		selectYesNo->Initialize();
		SetScene(reversi::ReversiGameScene::SCENE::REVERSI_ASK_CONTINUE);
	}
}

/**
 * リバーシ再対局確認シーン
 */
void reversi::ReversiGameScene::TaskReversiAskContinue() {
	selectYesNo->Task();
	if (selectYesNo->IsWrongInput()) {
		// 正しくない入力
		console->PrintLine("入力が間違っています、もう一度入力してください");
		return;
	}
	if (selectYesNo->IsSelected()) {
		if (selectYesNo->IsSelectYes()) {
			SetScene(reversi::ReversiGameScene::SCENE::INITIALIZE);
			return;
		} else {
			SetScene(reversi::ReversiGameScene::SCENE::END);
			return;
		}
	}
}

/**
 * 終了シーン
 */
void reversi::ReversiGameScene::TaskEnd() {
}

/**
 * シーンの設定
 * @param nextScene 次のシーン
 */
void reversi::ReversiGameScene::SetScene(reversi::ReversiGameScene::SCENE nextScene) {
	scene = nextScene;
}

/**
 * ゲームの初期化に必要なインスタンスの生成
 * ゲームを開始するたびに初期化される
 */
void reversi::ReversiGameScene::CreateInitializeGameInstance() {

	// 既に作成されている可能性もあるので開放してから作成
	if (selectYesNoWatching) {
		delete selectYesNoWatching;
		selectYesNoWatching = NULL;
	}
	selectYesNoWatching = new KeyboardSelectYesNoWatching();

	if (selectCpuLevel) {
		delete selectCpuLevel;
		selectCpuLevel = NULL;
	}
	selectCpuLevel = new KeyboardSelectCpuLevel();

	if (selectCpuLevel2) {
		delete selectCpuLevel2;
		selectCpuLevel2 = NULL;
	}
	selectCpuLevel2 = new KeyboardSelectCpuLevel();

	if (selectYesNo) {
		delete selectYesNo;
		selectYesNo;
	}
	selectYesNo = new KeyboardSelectYesNo();
}

/**
 * int数値からCPUプレイヤーを取得する
 * @param  cpuLevel CPUレベル数値
 * @return          レベルに対応したCPUプレイヤー
 */
reversi::Reversi::PLAYER reversi::ReversiGameScene::NumberToCpuLevel(int cpuLevel) {
	switch (cpuLevel) {
	case 1:
		return reversi::Reversi::PLAYER::CPU1;
	case 2:
		return reversi::Reversi::PLAYER::CPU2;
	case 3:
		return reversi::Reversi::PLAYER::CPU3;
	case 4:
		return reversi::Reversi::PLAYER::CPU4;
	default:
		return reversi::Reversi::PLAYER::CPU1;
	}
}

/**
 * プレイヤーが勝ったか
 * @return trueならプレイヤーの勝ち
 */
bool reversi::ReversiGameScene::IsPlayerWin() {
	// 終了していないときに呼び出してはいけない
	reversi::Assert::AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::END, "ReversiGameScene::IsPlayerWin invalid scene called");
	reversi::Reversi::RESULT result = reversi.GetResult();
	reversi::Reversi::PLAYER_SETTING playerSetting = reversi.GetPlayerSetting();
	if (playerSetting.playerType[reversi::Reversi::PLAYER_BLACK] == reversi::Reversi::PLAYER::MAN) {
		if (result == reversi::Reversi::RESULT::BLACK) {
			// プレイヤーが黒で黒の勝ち
			return true;
		}
	}
	if (playerSetting.playerType[reversi::Reversi::PLAYER_WHITE] == reversi::Reversi::PLAYER::MAN) {
		if (result == reversi::Reversi::RESULT::WHITE) {
			// プレイヤーが白で白の勝ち
			return true;
		}
	}
	return false;
}

/**
 * プレイヤーが負けたか
 * @return trueならプレイヤーの勝ち
 */
bool reversi::ReversiGameScene::IsPlayerLose() {
	// 終了していないときに呼び出してはいけない
	reversi::Assert::AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::END, "ReversiGameScene::IsPlayerWin invalid scene called");
	reversi::Reversi::RESULT result = reversi.GetResult();
	reversi::Reversi::PLAYER_SETTING playerSetting = reversi.GetPlayerSetting();
	if (playerSetting.playerType[reversi::Reversi::PLAYER_BLACK] == reversi::Reversi::PLAYER::MAN) {
		if (result == reversi::Reversi::RESULT::WHITE) {
			// プレイヤーが黒で白の勝ち
			return true;
		}
	}
	if (playerSetting.playerType[reversi::Reversi::PLAYER_WHITE] == reversi::Reversi::PLAYER::MAN) {
		if (result == reversi::Reversi::RESULT::BLACK) {
			// プレイヤーが白で黒の勝ち
			return true;
		}
	}
	return false;
}

/**
 * プレイヤーが引き分けだったか
 * @return trueならプレイヤーが引き分けだった
 */
bool reversi::ReversiGameScene::IsPlayerDraw() {
	// 終了していないときに呼び出してはいけない
	reversi::Assert::AssertEquals(reversi.GetScene() == reversi::Reversi::SCENE::END, "ReversiGameScene::IsPlayerWin invalid scene called");
	reversi::Reversi::RESULT result = reversi.GetResult();
	reversi::Reversi::PLAYER_SETTING playerSetting = reversi.GetPlayerSetting();
	if ((playerSetting.playerType[reversi::Reversi::PLAYER_BLACK] == reversi::Reversi::PLAYER::MAN)
	    || (playerSetting.playerType[reversi::Reversi::PLAYER_WHITE] == reversi::Reversi::PLAYER::MAN)) {
		if (result == reversi::Reversi::RESULT::DRAW) {
			return true;
		}
	}
	return false;
}

/**
 * プレイヤーの勝利メッセージを表示
 */
void reversi::ReversiGameScene::OutputPlayerWinMessage() {
	console->PrintLine("あなたの勝ちです!おめでとうございます!");
}

/**
 * プレイヤーの敗北メッセージを表示
 */
void reversi::ReversiGameScene::OutputPlayerLoseMessage() {
	console->PrintLine("あなたは負けてしまいました、また挑戦してみましょう!");
}

/**
 * プレイヤーの引き分けメッセージを表示
 */
void reversi::ReversiGameScene::OutputPlayerDrawMessage() {
	console->PrintLine("今回は引き分けでした、次は勝ちましょう!");
}
