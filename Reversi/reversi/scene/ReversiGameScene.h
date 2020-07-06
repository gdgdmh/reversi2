#ifndef REVERSI_SCENE_REVERSIGAMESCENE_H_
#define REVERSI_SCENE_REVERSIGAMESCENE_H_

#include "../../mhl/util/output/IOutputConsole.hpp"
#include "../game/ISelectCpuLevel.h"
#include "../game/ISelectYesNo.h"
#include "../game/ISelectYesNoWatching.h"
#include "../logic/base/Reversi.h"

namespace reversi {

// リバーシゲームシーン
class ReversiGameScene {
 public:
  enum class SCENE {
    INITIALIZE,                  // 初期化
    REVERSI_ASK_PLAYER_SETTING,  // 黒、白、観戦の選択
    REVERSI_ASK_CPU_SETTING,     // CPUレベル設定
    REVERSI_ASK_CPU2_SETTING,    // CPU2人目のレベル設定
    REVERSI_START,               // リバーシ開始
    REVERSI_TASK,                // リバーシ処理
    REVERSI_ASK_CONTINUE,        // 再戦するかの選択
    END                          // 終了
  };

 public:
  /**
   * コンストラクタ
   */
  ReversiGameScene();

  /**
   * デストラクタ
   */
  virtual ~ReversiGameScene();

  /**
   * 初期化
   */
  void Initialize();

  /**
   * メイン処理
   * @return falseなら終了
   */
  bool Task();

 private:
  /**
   * 初期化シーン
   */
  void TaskInitialize();

  /**
   * プレイヤー設定確認シーン
   */
  void TaskAskPlayerSetting();

  /**
   * CPU設定確認シーン
   */
  void TaskAskCpuSetting();

  /**
   * CPU2人目瀬底確認シーン
   */
  void TaskAskCpu2Setting();

  /**
   * リバーシ開始シーン
   */
  void TaskReversiStart();

  /**
   * リバーシメインシーン
   */
  void TaskReversiTask();

  /**
   * リバーシ再対局確認シーン
   */
  void TaskReversiAskContinue();

  /**
   * 終了シーン
   */
  void TaskEnd();

  /**
   * シーンの設定
   * @param nextScene 次のシーン
   */
  void SetScene(reversi::ReversiGameScene::SCENE nextScene);

  /**
   * ゲームの初期化に必要なインスタンスの生成
   * ゲームを開始するたびに初期化される
   */
  void CreateInitializeGameInstance();

  /**
   * int数値からCPUプレイヤーを取得する
   * @param  cpuLevel CPUレベル数値
   * @return          レベルに対応したCPUプレイヤー
   */
  reversi::Reversi::PLAYER NumberToCpuLevel(int cpuLevel);

  /**
   * プレイヤーが勝ったか
   * @return trueならプレイヤーの勝ち
   */
  bool IsPlayerWin();

  /**
   * プレイヤーが負けたか
   * @return trueならプレイヤーの勝ち
   */
  bool IsPlayerLose();

  /**
   * プレイヤーが引き分けだったか
   * @return trueならプレイヤーが引き分けだった
   */
  bool IsPlayerDraw();

  /**
   * プレイヤーの勝利メッセージを表示
   */
  void OutputPlayerWinMessage();

  /**
   * プレイヤーの敗北メッセージを表示
   */
  void OutputPlayerLoseMessage();

  /**
   * プレイヤーの引き分けメッセージを表示
   */
  void OutputPlayerDrawMessage();

 private:
  mhl::IOutputConsole* console;  // コンソール出力
  SCENE scene;                   // シーン変数
  reversi::Reversi reversi;      // リバーシクラス
  reversi::ISelectYesNoWatching*
      selectYesNoWatching;  // 黒、白、観戦の選択インターフェース
  reversi::ISelectCpuLevel* selectCpuLevel;  // CPUレベル設定インターフェース
  reversi::ISelectCpuLevel*
      selectCpuLevel2;  // CPU2人目のレベル設定インターフェース
  reversi::ISelectYesNo* selectYesNo;  // 再戦するかの選択インターフェース
};

}  // namespace reversi

#endif  // REVERSI_SCENE_REVERSIGAMESCENE_H_
