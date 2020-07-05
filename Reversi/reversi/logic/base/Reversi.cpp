#include "Reversi.h"
#include "../../util/Assert.h"
#include "../../util/OutputConsole.h"
#include "../../util/StdStringFormatter.h"
#include "../../util/PerformanceCounter.h"
#include "../player/PlayerMan.h"
#include "../player/PlayerCpu.h"
#include "../player/PlayerFactory.h"
#include "Move.h"

/**
 * コンストラクタ
 */
reversi::Reversi::Reversi() : turn(reversi::ReversiConstant::TURN::TURN_BLACK), scene(reversi::Reversi::SCENE::INITIALIZE), console(NULL), isSetSimulationMove(false), outputEnable(true), checkEnableMove(true) {
	ResetPlayer();
	ResetPassCheck();
	ResetResultData();
	simulationMove.Clear();
}

/**
 * デストラクタ
 */
reversi::Reversi::~Reversi() {
	Release();
}

/**
 *  初期化
 */
void reversi::Reversi::Initialize() {
	board.InitializeGame();
	turn = reversi::ReversiConstant::TURN::TURN_BLACK;
	SetScene(reversi::Reversi::SCENE::INITIALIZE);
	if (console == NULL) {
		console = new OutputConsole();
	}
	ResetPassCheck();
	ResetResultData();
	simulationMove.Clear();
	isSetSimulationMove = false;
	outputEnable = true;
	checkEnableMove = true;
}

/**
 * ゲーム開始のための初期化
 * @param playerSetting プレイヤー設定
 */
void reversi::Reversi::InitializeGame(const reversi::Reversi::PLAYER_SETTING& playerSetting) {
	board.InitializeGame();
	// プレイヤーインスタンスを開放する
	ReleasePlayer();
	// プレイヤー設定の取り込み
	ApplyPlayerSetting(playerSetting);
	// プレイヤーを作成,初期化
	CreatePlayers();
	for (int i = 0; i < PLAYER_COUNT; ++i) {
		if (playerData.player[i]) {
			playerData.player[i]->Initialize();
		}
	}
	turn = reversi::ReversiConstant::TURN::TURN_BLACK;
	SetScene(reversi::Reversi::SCENE::MOVE_SELECT_START);
	ResetPassCheck();
	ResetResultData();
	simulationMove.Clear();
	isSetSimulationMove = false;
}

/**
 * 更新処理
 */
void reversi::Reversi::Task() {
	if (scene == reversi::Reversi::SCENE::INITIALIZE) {
		TaskInitialize();
	} else if (scene == reversi::Reversi::SCENE::MOVE_SELECT_START) {
		TaskMoveSelectStart();
	} else if (scene == reversi::Reversi::SCENE::MOVE_SELECT) {
		TaskMoveSelect();
	} else if (scene == reversi::Reversi::SCENE::PASS) {
		TaskPass();
	} else if (scene == reversi::Reversi::SCENE::MOVE_AFTER) {
		TaskMoveAfter();
	} else if (scene == reversi::Reversi::SCENE::RESULT) {
		TaskResult();
	} else if (scene == reversi::Reversi::SCENE::END) {
		TaskEnd();
	}
}

/**
 * シミュレーションによる着手を設定する(思考用)
 * @param setMoveInfo シミュレーション着手情報
 */
void reversi::Reversi::SetMoveSimulation(const reversi::MoveInfo& setMoveInfo) {
	// シミュレーション着手フラグとデータを設定
	isSetSimulationMove = true;
	simulationMove.Copy(setMoveInfo);
}

/**
 * 盤面をコピーする(デバッグ用途)
 * @param source コピー元
 */
void reversi::Reversi::CopyBoard(const reversi::Board& source) {
	board.Copy(source);
}

/**
 * 動的生成インスタンス以外をコピー
 * @param source コピー元
 */
void reversi::Reversi::CopyWithoutDynamicInstance(const reversi::Reversi& source) {
	// もしコピー先がメモリ確保していたら開放する
	Release();

	CopyBoard(source.board);
	turn = source.turn;
	for (int i = 0; i < PLAYER_COUNT; ++i) {
		playerData.playerType[i] = source.playerData.playerType[i];
	}
	scene = source.scene;
	moveCache = source.moveCache;
	if (!console) {
		console = new OutputConsole();
	}
	passCheck = source.passCheck;
	resultData = source.resultData;
	simulationMove.Copy(source.simulationMove);
	isSetSimulationMove = source.isSetSimulationMove;
	outputEnable = source.outputEnable;
	checkEnableMove = source.checkEnableMove;
}

/**
 * 出力フラグを設定する
 * @param isOutputEnable trueなら出力する
 */
void reversi::Reversi::SetOutputEnable(bool isOutputEnable) {
	outputEnable = isOutputEnable;
}

/**
 * 最終結果の石や空白の数を取得する
 * @param black 黒石
 * @param white 白石
 * @param none  空白
 */
void reversi::Reversi::GetResultStone(int& black, int& white, int& none) {
	black = resultData.blackResultCount;
	white = resultData.whiteResultCount;
	none = resultData.noneResultCount;
}

/**
 * プレイヤー設定情報を取得する
 * @return プレイヤー設定情報
 */
reversi::Reversi::PLAYER_SETTING reversi::Reversi::GetPlayerSetting() const {
	reversi::Reversi::PLAYER_SETTING setting;
	for (int i = 0; i < PLAYER_COUNT; ++i) {
		setting.playerType[i] = playerData.playerType[i];
	}
	return setting;
}

/**
 * 着手チェック処理を行うか
 * @param isCheckEnableMove trueならチェックする
 */
void reversi::Reversi::SetCheckEnableMove(bool isCheckEnableMove) {
	checkEnableMove = isCheckEnableMove;
}

/**
 * 初期化
 */
void reversi::Reversi::TaskInitialize() {
}

/**
 * 着手選択開始
 */
void reversi::Reversi::TaskMoveSelectStart() {
	RenderBoard();

	if (IsEveryonePass()) {
		// 両者パスしたので終局
		SetScene(reversi::Reversi::SCENE::RESULT);
		if (outputEnable) {
			PrintLine("2人ともパスしたため、対局を終了します");
		}
		return;
	}

	if (CheckPass(turn)) {
		// 打つことができないのでパス
		SetPassCheck(turn);
		SetScene(reversi::Reversi::SCENE::PASS);
		if (outputEnable) {
			if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
				PrintLine("黒が打つことができないのでパスします");
			} else {
				PrintLine("白が打つことができないのでパスします");
			}
		}
		return;
	}
	// パスフラグリセット
	ResetPassCheck();

	// 着手キャッシュ作成
	if (checkEnableMove) {
		CreateMoveCache();
	}

	int playerIndex = TurnToPlayerIndex(turn);
	if (playerData.player[playerIndex]) {
		// プレイヤーの手番開始イベント
		playerData.player[playerIndex]->EventTurnStart((*this), moveCache, board, turn);
	}
	SetScene(reversi::Reversi::SCENE::MOVE_SELECT);
	if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
		PrintLine("黒のターン");
	} else {
		PrintLine("白のターン");
	}
	if (IsCurrentPlayerTurnMan(turn)) {
		PrintLine("石を打つ場所を入力してください(入力例 d3)");
	}
}

/**
 * 着手選択
 */
void reversi::Reversi::TaskMoveSelect() {
	int playerIndex = TurnToPlayerIndex(turn);
	reversi::MoveInfo move;

	// プレイヤーの着手 または シミュレーションの着手があるか
	// シミュレーションは思考のために使用
	bool isDecide = false;
	if (playerData.player[playerIndex]) {
		// プレイヤーによる着手
		isDecide = playerData.player[playerIndex]->SelectMove((*this), moveCache, board, move, turn);
	}

	if ((isSetSimulationMove) && (!isDecide)) {
		// シミュレーションによる着手
		move.Copy(simulationMove);
		isDecide = true;
	}
	if (isDecide) {
		// 正常な着手かチェック
		if (checkEnableMove) {
			reversi::Assert::AssertEquals(CheckEnableMove(move.GetMoveInfo().position), "Reversi::TaskMoveSelect invalid move");
		}

		// 着手処理
		bool isMove = board.Move(move);
		reversi::Assert::AssertEquals(isMove, "Reversi::TaskMoveSelect move task failure");

		if (isSetSimulationMove) {
			// シミュレーション着手を使用した後は情報をクリア
			simulationMove.Clear();
			isSetSimulationMove = false;
		}

		if (outputEnable) {
			if (!IsCurrentPlayerTurnMan(turn)) {
				// CPUなら着手を出力する
				std::string positionString;
				if (reversi::ReversiConstant::GetPositionToString(move.GetMoveInfo().position, positionString)) {
					PrintLine(positionString);
				}
			}
		}
		// 着手後処理へ
		SetScene(reversi::Reversi::SCENE::MOVE_AFTER);
	} else {
		// 人間が着手入力失敗したとき
		if (IsCurrentPlayerTurnMan(turn)) {
			// 盤面表示とメッセージ表示
			RenderBoard();
			PrintLine("その位置には打てないのでもう一度入力してください");
		}
	}
}

/**
 * パス
 */
void reversi::Reversi::TaskPass() {
	// ターン切り替え
	ChangeTurn(turn);
	SetScene(reversi::Reversi::SCENE::MOVE_SELECT_START);
}

/**
 * 着手後処理
 */
void reversi::Reversi::TaskMoveAfter() {

	int playerIndex = TurnToPlayerIndex(turn);
	if (playerData.player[playerIndex]) {
		// 着手後プレイヤーイベント
		playerData.player[playerIndex]->EventMoveAfter();
	}

	// ターン切り替え
	ChangeTurn(turn);

	if (IsBoardFull()) {
		// 盤面が埋まったら終局
		// 結果へ
		SetScene(reversi::Reversi::SCENE::RESULT);
		return;
	}
	SetScene(reversi::Reversi::SCENE::MOVE_SELECT_START);
}

/**
 * 結果処理
 */
void reversi::Reversi::TaskResult() {

	PrintLine("終局しました -----------------------");
	RenderBoard();

	// 石の数を取得
	int black, white, none;
	board.GetCount(black, white, none);

	// 結果
	if (black == white) {
		resultData.result = reversi::Reversi::RESULT::DRAW;
	} else if (black > white) {
		resultData.result = reversi::Reversi::RESULT::BLACK;
	} else if (black < white) {
		resultData.result = reversi::Reversi::RESULT::WHITE;
	}
	// 純粋な数
	resultData.blackRawCount = black;
	resultData.whiteRawCount = white;
	resultData.noneRawCount = none;

	// 最終結果
	// 公式ルールで空白は勝者の石になる
	resultData.blackResultCount = black;
	resultData.whiteResultCount = white;
	resultData.noneResultCount = none;
	SetResultStone(resultData.blackResultCount, resultData.whiteResultCount, resultData.noneResultCount, resultData.result);

	// コンソール結果表示
	PrintLine(reversi::StdStringFormatter::Format("黒石:%d 白石:%d 空白:%d", resultData.blackRawCount, resultData.whiteRawCount, resultData.noneRawCount));
	if (resultData.result == reversi::Reversi::RESULT::DRAW) {
		PrintLine("結果は引き分けです");
	} else if (resultData.result == reversi::Reversi::RESULT::BLACK) {
		PrintLine("結果は黒の勝ちです");
	} else if (resultData.result == reversi::Reversi::RESULT::WHITE) {
		PrintLine("結果は白の勝ちです");
	}
	PrintLine(reversi::StdStringFormatter::Format("最終結果 黒石:%d 白石:%d", resultData.blackResultCount, resultData.whiteResultCount));

	// 終了
	SetScene(reversi::Reversi::SCENE::END);
}

/**
 * 対局終了
 */
void reversi::Reversi::TaskEnd() {
}

/**
 * プレイヤーをリセットする(NULLクリア)
 */
void reversi::Reversi::ResetPlayer() {
	// タイプは暫定
	playerData.playerType[PLAYER_BLACK] = reversi::Reversi::PLAYER::CPU1;
	playerData.playerType[PLAYER_WHITE] = reversi::Reversi::PLAYER::CPU1;
	for (int i = 0; i < PLAYER_COUNT; ++i) {
		playerData.player[i] = NULL;
	}
}

/**
 * プレイヤーを作成する
 * @param  playerIndex 作成対象のプレイヤーindex
 * @param  playerType  作成するプレイヤータイプ
 * @return             作成したプレイヤークラス
 */
reversi::IPlayer* reversi::Reversi::CreatePlayer(int playerIndex, reversi::Reversi::PLAYER playerType) {
	// ファクトリークラスを使用してプレイヤークラスを生成
	reversi::PlayerFactory factory;
	reversi::PlayerFactory::TYPE type = reversi::PlayerFactory::TYPE::PLAYER_MAN;
	switch (playerType) {
	case reversi::Reversi::PLAYER::MAN:
		type = reversi::PlayerFactory::TYPE::PLAYER_MAN;
		break;
	case reversi::Reversi::PLAYER::CPU1:
		type = reversi::PlayerFactory::TYPE::PLAYER_CPU1;
		break;
	case reversi::Reversi::PLAYER::CPU2:
		type = reversi::PlayerFactory::TYPE::PLAYER_CPU2;
		break;
	case reversi::Reversi::PLAYER::CPU3:
		type = reversi::PlayerFactory::TYPE::PLAYER_CPU3;
		break;
	case reversi::Reversi::PLAYER::CPU4:
		type = reversi::PlayerFactory::TYPE::PLAYER_CPU4;
		break;
	default:
		break;
	}
	return factory.Create(type);
}

/**
 * プレイヤー達のインスタンスを作成する
 */
void reversi::Reversi::CreatePlayers() {
	// 2人のプレイヤーを生成
	for (int i = 0; i < PLAYER_COUNT; ++i) {
		reversi::Assert::AssertArrayRange(i, PLAYER_COUNT, "Reversi::CreatePlayers index over");
		playerData.player[i] = CreatePlayer(i, playerData.playerType[i]);
	}
}

/**
 * プレイヤー設定を適用する
 * @param playerSetting プレイヤー設定
 */
void reversi::Reversi::ApplyPlayerSetting(reversi::Reversi::PLAYER_SETTING playerSetting) {
	for (int i = 0; i < PLAYER_COUNT; ++i) {
		reversi::Assert::AssertArrayRange(i, PLAYER_COUNT, "Reversi::ApplyPlayerSetting index over");
		playerData.playerType[i] = playerSetting.playerType[i];
	}
}

/**
 * プレイヤーを削除する(DELETE)
 */
void reversi::Reversi::ReleasePlayer() {
	for (int i = 0; i < PLAYER_COUNT; ++i) {
		if (playerData.player[i]) {
			delete playerData.player[i];
			playerData.player[i] = NULL;
		}
	}
}

/**
 * シーンをセットする
 * @param nextScene 次のシーン
 */
void reversi::Reversi::SetScene(reversi::Reversi::SCENE nextScene) {
	scene = nextScene;
}

/**
 * 手番からプレイヤーのindexを取得する
 * @param  targetTurn 手番
 * @return            プレイヤーindex
 */
int reversi::Reversi::TurnToPlayerIndex(reversi::ReversiConstant::TURN targetTurn) {
	if (targetTurn == reversi::ReversiConstant::TURN::TURN_BLACK) {
		return PLAYER_BLACK;
	} else {
		return PLAYER_WHITE;
	}
}

/**
 * 人間の手番か
 * @param  targetTurn 対象の手番
 * @return            trueなら人間の手番
 */
bool reversi::Reversi::IsCurrentPlayerTurnMan(reversi::ReversiConstant::TURN targetTurn) {
	int playerIndex = TurnToPlayerIndex(targetTurn);
	if (playerData.playerType[playerIndex] == reversi::Reversi::PLAYER::MAN) {
		return true;
	}
	return false;
}

/**
 * 手番の切り替え
 * @param targetTurn 現在の手番
 */
void reversi::Reversi::ChangeTurn(reversi::ReversiConstant::TURN& targetTurn) {
	// 手番切り替え(黒->白, 白->黒)
	if (targetTurn == reversi::ReversiConstant::TURN::TURN_BLACK) {
		targetTurn = reversi::ReversiConstant::TURN::TURN_WHITE;
	} else {
		targetTurn = reversi::ReversiConstant::TURN::TURN_BLACK;
	}
}

/**
 * 着手キャッシュを作成する
 */
void reversi::Reversi::CreateMoveCache() {
	// 空の位置を探す
	reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
	moveCache.FindEmptyPosition(board, emptyPosition);
	// 打てる位置を探す
	moveCache.FindPutEnablePosition(board, emptyPosition, turn);
}

/**
 * 着手できるかどうかをチェック
 * @param  position 着手位置
 * @return          trueなら着手できる
 */
bool reversi::Reversi::CheckEnableMove(const reversi::ReversiConstant::POSITION& position) {
	return moveCache.CheckEnableMoveByCache(position);
}

/**
 * 盤面が埋まっているか
 * @return trueなら終局している
 */
bool reversi::Reversi::IsBoardFull() {
	if (board.IsFull()) {
		// 盤面が全て埋まっている
		return true;
	}
	return false;
}

/**
 * 打つ場所がなくてパスかどうかチェック
 * @param  targetTurn 現在の手番
 * @return            trueならパス(打つ場所がない)
 */
bool reversi::Reversi::CheckPass(reversi::ReversiConstant::TURN targetTurn) {

	reversi::Move move;
	reversi::ReversiConstant::EMPTY_POSITION emptyPosition;
	move.FindEmptyPosition(board, emptyPosition);
	// キャッシュを作成する
	move.FindPutEnablePosition(board, emptyPosition, targetTurn);
	// どこかにうてるか
	return (!move.CheckSomewherePutEnableByCache());
}

/**
 * パスのチェックフラグをリセットする
 */
void reversi::Reversi::ResetPassCheck() {
	passCheck.passBlack = false;
	passCheck.passWhite = false;
}

/**
 * パスのチェックフラグをセットする
 * @param targetTurn 現在の手番
 */
void reversi::Reversi::SetPassCheck(reversi::ReversiConstant::TURN targetTurn) {
	if (targetTurn == reversi::ReversiConstant::TURN::TURN_BLACK) {
		passCheck.passBlack = true;
	} else {
		passCheck.passWhite = true;
	}
}

/**
 * プレイヤー2人ともパスしているか
 * @return trueなら2人ともパスしている
 */
bool reversi::Reversi::IsEveryonePass() const {
	if ((passCheck.passBlack) && (passCheck.passWhite)) {
		return true;
	}
	return false;
}

/**
 * 結果データをリセットする
 */
void reversi::Reversi::ResetResultData() {
	resultData.result = reversi::Reversi::RESULT::NONE;
	resultData.blackRawCount = 0;
	resultData.whiteRawCount = 0;
	resultData.noneRawCount = 0;
	resultData.blackResultCount = 0;
	resultData.whiteResultCount = 0;
	resultData.noneResultCount = 0;
}

/**
 * 結果の石をセットする(空白を勝者の石とする)
 * @param black  現在の黒石の数
 * @param white  現在の白石の数
 * @param none   現在の空白の数
 * @param result 勝敗結果
 */
void reversi::Reversi::SetResultStone(int& black, int& white, int& none, reversi::Reversi::RESULT result) {
	// 日本オセロ連盟競技ルール No.13
	// 終局（対局者双方が石を置けなくなった状態）時に盤面に空きマスが発生した場合、その空きマスは勝者の獲得石に加算される。
	if (result == reversi::Reversi::RESULT::BLACK) {
		black += none;
	} else if (result == reversi::Reversi::RESULT::WHITE) {
		white += none;
	}
}

/**
 * 行単位の出力をする
 * ただし、出力許可フラグがfalseのときは出力しない
 * @param outputStringLine 出力をする文字列
 */
void reversi::Reversi::PrintLine(std::string outputStringLine) {
	if (outputEnable) {
		console->PrintLine(outputStringLine);
	}
}

/**
 * 盤の出力をする
 * ただし、出力許可フラグがfalseのときは出力しない
 */
void reversi::Reversi::RenderBoard() {
	if (outputEnable) {
		board.Render();
	}
}

/**
 * メモリを開放する
 */
void reversi::Reversi::Release() {
	ReleasePlayer();
	if (console) {
		delete console;
		console = NULL;
	}
}
