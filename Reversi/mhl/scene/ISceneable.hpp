#ifndef MHL_SCENE_ISCENEABLE_HPP_
#define MHL_SCENE_ISCENEABLE_HPP_

#include <memory>

namespace mhl {

// シーンインターフェースクラス
class ISceneable {
 public:
  /**
   * @brief Destroy the ISceneable object
   *
   */
  virtual ~ISceneable() {}

  /**
   * @brief シーンの初期化
   *
   */
  virtual void Initialize() = 0;

  /**
   * @brief シーンの開放処理
   *
   */
  virtual void Release() = 0;

  /**
   * @brief シーンのロード
   * 時間のかかる処理はここで行う
   */
  virtual void Load() = 0;

  /**
   * @brief シーンの更新処理
   *
   */
  virtual void Update() = 0;

  /**
   * @brief シーンの描画処理
   *
   */
  virtual void Draw() = 0;

  /**
   * @brief シーンがトップより下に積まれているときにシーンの更新を行うか設定する
   *
   * @param under_update trueなら更新処理を行う
   */
  virtual void SetUnderUpdate(bool under_update) = 0;

  /**
   * @brief シーンがトップより下に積まれているときにシーンの更新を行うか
   *
   * @return true シーンの更新を行う
   * @return false シーンの更新をしない
   */
  virtual bool IsUnderUpdate() = 0;

  /**
   * @brief シーンがトップより下に積まれているときにシーンの描画を行うか設定する
   *
   * @param under_draw trueなら描画処理を行う
   */
  virtual void SetUnderDraw(bool under_draw) = 0;

  /**
   * @brief シーンがトップより下に積まれているときにシーンの描画を行うか
   *
   * @return true シーンの描画を行う
   * @return false シーンの描画をしない
   */
  virtual bool IsUnderDraw() = 0;

  /**
   * @brief このシーンがポップ処理をされる前に呼び出される
   *
   */
  virtual void EventPop() = 0;

  /**
   * @brief このシーンの上にプッシュ処理をされる前に呼び出される
   * ただし、このシーンが現在のシーンであるときのみ
   * @param next このシーンの上にプッシュされるシーン
   */
  virtual void EventPush(std::shared_ptr<ISceneable> next) = 0;

  /**
   * @brief シーンのスワップ処理をされる前に呼び出される
   * ただし、このシーンが現在のシーンであるときのみ
   * @param next このシーンの代わりにスワップされるシーン
   */
  virtual void EventSwap(std::shared_ptr<ISceneable> next) = 0;
};

}  // namespace mhl

#endif  // MHL_SCENE_ISCENEABLE_HPP_
