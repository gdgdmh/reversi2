#ifndef REVERSI_GAME_ISELECTYESNOWATCHING_H_
#define REVERSI_GAME_ISELECTYESNOWATCHING_H_

namespace reversi {

// Yes,No,Watching選択インターフェース
class ISelectYesNoWatching {
 public:
  /**
   * デストラクタ
   */
  virtual ~ISelectYesNoWatching() {}

  /**
   * 初期化
   */
  virtual void Initialize() = 0;

  /**
   * メイン処理
   */
  virtual void Task() = 0;

  /**
   * 選択し終わったか
   * @return trueなら選択し終わっている
   */
  virtual bool IsSelected() = 0;

  /**
   * Yesを選択したか
   * @return trueならyeso
   */
  virtual bool IsSelectYes() = 0;

  /**
   * Noを選択したか
   * @return trueならno
   */
  virtual bool IsSelectNo() = 0;

  /**
   * Watchingを選択したか
   * @return trueならwatching
   */
  virtual bool IsSelectWatching() = 0;

  /**
   * 間違った入力をしたか
   * @return trueなら間違った入力をした
   */
  virtual bool IsWrongInput() = 0;
};

}  // namespace reversi

#endif  // REVERSI_GAME_ISELECTYESNOWATCHING_H_
