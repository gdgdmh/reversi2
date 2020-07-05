#ifndef REVERSI_LOGIC_BASE_REVERSI_H_
#define REVERSI_LOGIC_BASE_REVERSI_H_

#include "ReversiConstant.h"
#include "Board.h"
#include "Move.h"
#include "../player/IPlayer.h"
#include "../../util/IOutputConsole.h"

namespace reversi {

// リバーシクラス
class Reversi {
public:
	static const int PLAYER_COUNT = 2; // プレイヤー数
	static const int PLAYER_BLACK = 0; // 黒のプレイヤー
	static const int PLAYER_WHITE = 1; // 白のプレイヤー
	// シーン
	enum class SCENE {
		INITIALIZE,         // 初期化
		MOVE_SELECT_START,  // 着手選択開始
		MOVE_SELECT,        // 着手選択
		PASS,               // パス
		MOVE_AFTER,         // 着手後
		RESULT,             // 結果設定
		END                 // 終了
	};
	// 結果
	enum class RESULT {
		NONE,   // 勝敗がついていない
		BLACK,  // 黒の勝ち
		WHITE,  // 白の勝ち
		DRAW    // 引き分け
	};
	// プレイヤー
	enum class PLAYER {
		MAN,    // 人間
		CPU1,   // CPU LEVEL1
		CPU2,   // CPU LEVEL2(Lv1に勝率6割)
		CPU3,   // CPU LEVEL3(Lv2に勝率7割)
		CPU4    // CPU LEVEL4(Lv3に勝率9割)
	};
	typedef struct {
		bool passBlack; // 黒がパスしたか
		bool passWhite; // 白がパスしたか
	} PASS_CHECK;
	// 結果データ
	typedef struct {
		RESULT result;          // 結果
		int blackRawCount;      // 純粋な黒石の数
		int whiteRawCount;      // 純粋な白石の数
		int noneRawCount;       // 純粋な空白の数
		int blackResultCount;   // 結果を適用した黒石の数
		int whiteResultCount;   // 結果を適用した黒石の数
		int noneResultCount;    // 結果を適用した空白の数
	} RESULT_DATA;
	// プレイヤーデータ
	typedef struct {
		PLAYER playerType[PLAYER_COUNT];            // プレイヤーのタイプ
		reversi::IPlayer* player[PLAYER_COUNT];     // プレイヤークラス
	} PLAYER_DATA;
	// プレイヤー設定
	typedef struct {
		PLAYER playerType[PLAYER_COUNT];    // プレイヤーのタイプ
	} PLAYER_SETTING;

public:

	/**
	 * コンストラクタ
	 */
	Reversi();

	/**
	 * デストラクタ
	 */
	virtual ~Reversi();

	/**
	 *  初期化
	 */
	void Initialize();

	/**
	 * ゲーム開始のための初期化
	 * @param playerSetting プレイヤー設定
	 */
	void InitializeGame(const reversi::Reversi::PLAYER_SETTING& playerSetting);

	/**
	 * 更新処理
	 */
	void Task();

	/**
	 * シミュレーションによる着手を設定する(思考用)
	 * @param setMoveInfo シミュレーション着手情報
	 */
	void SetMoveSimulation(const reversi::MoveInfo& setMoveInfo);

	/**
	 * 盤面をコピーする(デバッグ用途)
	 * @param source コピー元
	 */
	void CopyBoard(const reversi::Board& source);

	/**
	 * 動的生成インスタンス以外をコピー
	 * @param source コピー元
	 */
	void CopyWithoutDynamicInstance(const reversi::Reversi& source);

	/**
	 * 出力フラグを設定する
	 * @param isOutputEnable trueなら出力する
	 */
	void SetOutputEnable(bool isOutputEnable);

	/**
	 * 現在のシーンを取得する
	 * @return シーン
	 */
	reversi::Reversi::SCENE GetScene() const {
		return scene;
	}

	/**
	 * 盤を取得する
	 * @return 盤クラス
	 */
	const reversi::Board& GetBoard() const {
		return board;
	}

	/**
	 * 結果を取得する
	 * @return 結果
	 */
	reversi::Reversi::RESULT GetResult() const {
		return resultData.result;
	}

	/**
	 * 現在の手番を取得する
	 * @return 手番
	 */
	reversi::ReversiConstant::TURN GetTurn() const {
		return turn;
	}

	/**
	 * 最終結果の石や空白の数を取得する
	 * @param black 黒石
	 * @param white 白石
	 * @param none  空白
	 */
	void GetResultStone(int& black, int& white, int& none);

	/**
	 * プレイヤー設定情報を取得する
	 * @return プレイヤー設定情報
	 */
	reversi::Reversi::PLAYER_SETTING GetPlayerSetting() const;

	/**
	 * 着手チェック処理を行うか
	 * @param isCheckEnableMove trueならチェックする
	 */
	void SetCheckEnableMove(bool isCheckEnableMove);

private:

	/**
	 * 初期化
	 */
	void TaskInitialize();

	/**
	 * 着手選択開始
	 */
	void TaskMoveSelectStart();

	/**
	 * 着手選択
	 */
	void TaskMoveSelect();

	/**
	 * パス
	 */
	void TaskPass();

	/**
	 * 着手後処理
	 */
	void TaskMoveAfter();

	/**
	 * 結果処理
	 */
	void TaskResult();

	/**
	 * 対局終了
	 */
	void TaskEnd();

	/**
	 * プレイヤーをリセットする(NULLクリア)
	 */
	void ResetPlayer();

	/**
	 * プレイヤーを作成する
	 * @param  playerIndex 作成対象のプレイヤーindex
	 * @param  playerType  作成するプレイヤータイプ
	 * @return             作成したプレイヤークラス
	 */
	reversi::IPlayer* CreatePlayer(int playerIndex, reversi::Reversi::PLAYER playerType);

	/**
	 * プレイヤー達のインスタンスを作成する
	 */
	void CreatePlayers();

	/**
	 * プレイヤー設定を適用する
	 * @param playerSetting プレイヤー設定
	 */
	void ApplyPlayerSetting(reversi::Reversi::PLAYER_SETTING playerSetting);

	/**
	 * プレイヤーを削除する(DELETE)
	 */
	void ReleasePlayer();

	/**
	 * シーンをセットする
	 * @param nextScene 次のシーン
	 */
	void SetScene(reversi::Reversi::SCENE nextScene);

	/**
	 * 手番からプレイヤーのindexを取得する
	 * @param  targetTurn 手番
	 * @return            プレイヤーindex
	 */
	int TurnToPlayerIndex(reversi::ReversiConstant::TURN targetTurn);

	/**
	 * 人間の手番か
	 * @param  targetTurn 対象の手番
	 * @return            trueなら人間の手番
	 */
	bool IsCurrentPlayerTurnMan(reversi::ReversiConstant::TURN targetTurn);

	/**
	 * 手番の切り替え
	 * @param targetTurn 現在の手番
	 */
	void ChangeTurn(reversi::ReversiConstant::TURN& targetTurn);

	/**
	 * 着手キャッシュを作成する
	 */
	void CreateMoveCache();

	/**
	 * 着手できるかどうかをチェック
	 * @param  position 着手位置
	 * @return          trueなら着手できる
	 */
	bool CheckEnableMove(const reversi::ReversiConstant::POSITION& position);

	/**
	 * 盤面が埋まっているか
	 * @return trueなら終局している
	 */
	bool IsBoardFull();

	/**
	 * 打つ場所がなくてパスかどうかチェック
	 * @param  targetTurn 現在の手番
	 * @return            trueならパス(打つ場所がない)
	 */
	bool CheckPass(reversi::ReversiConstant::TURN targetTurn);

	/**
	 * パスのチェックフラグをリセットする
	 */
	void ResetPassCheck();

	/**
	 * パスのチェックフラグをセットする
	 * @param targetTurn 現在の手番
	 */
	void SetPassCheck(reversi::ReversiConstant::TURN targetTurn);

	/**
	 * プレイヤー2人ともパスしているか
	 * @return trueなら2人ともパスしている
	 */
	bool IsEveryonePass() const;

	/**
	 * 結果データをリセットする
	 */
	void ResetResultData();

	/**
	 * 結果の石をセットする(空白を勝者の石とする)
	 * @param black  現在の黒石の数
	 * @param white  現在の白石の数
	 * @param none   現在の空白の数
	 * @param result 勝敗結果
	 */
	void SetResultStone(int& black, int& white, int& none, reversi::Reversi::RESULT result);

	/**
	 * 行単位の出力をする
	 * ただし、出力許可フラグがfalseのときは出力しない
	 * @param outputStringLine 出力をする文字列
	 */
	void PrintLine(std::string outputStringLine);

	/**
	 * 盤の出力をする
	 * ただし、出力許可フラグがfalseのときは出力しない
	 */
	void RenderBoard();

	/**
	 * メモリを開放する
	 */
	void Release();

private:
	// コピーメソッドやゲーム初期化に注意すること
	reversi::Board board;                       // 盤
	reversi::ReversiConstant::TURN turn;        // 現在の手番
	reversi::Reversi::PLAYER_DATA playerData;   // プレイヤーデータ
	reversi::Reversi::SCENE scene;              // シーン
	reversi::Move moveCache;                    // 着手キャッシュ
	reversi::IOutputConsole* console;           // コンソール出力クラス
	reversi::Reversi::PASS_CHECK passCheck;     // パス確認用(どっちもパスしかできなかったら終局)
	reversi::Reversi::RESULT_DATA resultData;   // 結果データ
	reversi::MoveInfo simulationMove;           // シミュレーション着手情報(思考用)
	bool isSetSimulationMove;                   // シミュレーション着手情報が設定されているか
	bool outputEnable;                          // 出力許可フラグ
	bool checkEnableMove;                       // 着手できるかチェック(思考のときは遅くなるのでフラグで管理)
};

}

#endif  // REVERSI_LOGIC_BASE_REVERSI_H_
