#ifndef REVERSI_GAME_ISELECTCPULEVEL_H_
#define REVERSI_GAME_ISELECTCPULEVEL_H_

namespace reversi {

// CPUレベル選択インターフェース
class ISelectCpuLevel {
 public:
  /**
   * デストラクタ
   */
  virtual ~ISelectCpuLevel() {}

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
   * Cpuレベルを取得する
   * @return cpuレベル
   */
  virtual int GetCpuLevel() = 0;

  /**
   * 間違った入力をしたか
   * @return trueなら間違った入力をした
   */
  virtual bool IsWrongInput() = 0;
};

}  // namespace reversi

#endif  // REVERSI_GAME_ISELECTCPULEVEL_H_
