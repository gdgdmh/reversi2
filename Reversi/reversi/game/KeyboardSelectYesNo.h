#ifndef REVERSI_GAME_KEYBOARDSELECTYESNO_H_
#define REVERSI_GAME_KEYBOARDSELECTYESNO_H_

#include "../util/IInputKeyboard.h"
#include "ISelectYesNo.h"

namespace reversi {

// キーボードによるYesNo選択クラス
class KeyboardSelectYesNo : public ISelectYesNo {
 private:
  static const int YES_UPPER_PATTERN_COUNT = 2;  // Yesのパターン
  static const std::string YES_UPPER_STRINGS
      [YES_UPPER_PATTERN_COUNT];  // Yesとみなす大文字文字列パターン
  static const int NO_UPPER_PATTERN_COUNT = 2;  // Noのパターン
  static const std::string NO_UPPER_STRINGS
      [NO_UPPER_PATTERN_COUNT];  // Noとみなす大文字文字列パターン
 public:
  /**
   * コンストラクタ
   */
  KeyboardSelectYesNo();

  /**
   * デストラクタ
   */
  virtual ~KeyboardSelectYesNo();

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
   * Yesを選択したか
   * @return trueならyes falseならno
   */
  bool IsSelectYes();

  /**
   * 間違った入力をしたか
   * @return trueなら間違った入力をした
   */
  bool IsWrongInput();

 private:
  /**
   * YesかNoと解釈できる文字列が指定されたかチェックする
   * @param  checkString チェックする文字列
   * @return             trueなら正しい文字列が指定された
   */
  bool CheckValidString(const std::string& checkString);

  /**
   * 文字列を大文字に変換する
   * @param targetString 対象の文字列
   */
  void TransformStringUpper(std::string& targetString);

  /**
   * 文字列がYesと解釈できるか
   * @param  checkString チェックスル文字列
   * @return             trueならYesと解釈できる文字列
   */
  bool IsStringYes(const std::string& checkString);

 private:
  reversi::IInputKeyboard* inputKeyboard;  // キーボード入力クラス
  bool isSelected;  // 入力が完了したか(isWrongInputの場合にはフラグが立たない)
  bool isYes;         // Yesを入力したか
  bool isWrongInput;  // 間違った入力をしたか
};

}  // namespace reversi

#endif  // REVERSI_GAME_KEYBOARDSELECTYESNO_H_
