#ifndef REVERSI_GAME_KEYBOARDSELECTCPULEVEL_H_
#define REVERSI_GAME_KEYBOARDSELECTCPULEVEL_H_

#include "../util/IInputKeyboard.h"
#include "ISelectCpuLevel.h"

namespace reversi {

// キーボードによるCPUレベル選択クラス
class KeyboardSelectCpuLevel : public ISelectCpuLevel {
 private:
  static const int LEVEL_PATTERN_COUNT = 4;  // CPULEVELのパターン
  static const std::string
      LEVEL_STRINGS[LEVEL_PATTERN_COUNT];  // CPULEVELとみなす文字列パターン
  static const int DEFAULT_CPU_LEVEL = 1;  // デフォルトのCPULEVEL
 public:
  /**
   * コンストラクタ
   */
  KeyboardSelectCpuLevel();

  /**
   * デストラクタ
   */
  virtual ~KeyboardSelectCpuLevel();

  /**
   * 初期化
   */
  void Initialize();

  /**
   * メイン処理
   */
  void Task();

  /**
   * 選択し終わったか
   * @return trueなら選択し終わっている
   */
  bool IsSelected();

  /**
   * Cpuレベルを取得する
   * @return cpuレベル
   */
  int GetCpuLevel();

  /**
   * 間違った入力をしたか
   * @return trueなら間違った入力をした
   */
  bool IsWrongInput();

 private:
  /**
   * 入力された文字列のCPUレベルをチェック
   * @param  checkString    チェックする文字列
   * @param  selectCpuLevel 戻り値がtrueだった場合CPUレベルが入る
   * @return                trueならCPUレベルが入力された
   */
  bool CheckInputStringLevel(const std::string& checkString,
                             int& selectCpuLevel);

 private:
  reversi::IInputKeyboard* inputKeyboard;  // キーボード入力クラス
  bool isSelected;                         // 選択し終わったか
  bool isWrongInput;                       // 間違った入力をしたか
  int cpuLevel;                            // CPUレベル
};

}  // namespace reversi

#endif  // REVERSI_GAME_KEYBOARDSELECTCPULEVEL_H_
