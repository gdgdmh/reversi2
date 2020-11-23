#ifndef MHL_SCENE_SCENESTACK_HPP_
#define MHL_SCENE_SCENESTACK_HPP_

#include <list>
#include <memory>

#include "ISceneable.hpp"

namespace mhl {

/**
 * @brief スタック型シーン管理クラス
 *
 */
class SceneStack {
 public:
  /**
   * @brief Construct a new Scene Stack object
   *
   */
  SceneStack();

  /**
   * @brief Destroy the Scene Stack object
   *
   */
  virtual ~SceneStack();

  /**
   * @brief シーンの更新処理
   *
   */
  void Update();

  /**
   * @brief シーンの描画処理
   *
   */
  void Draw();

  /**
   * @brief シーンをスタックにプッシュする
   *
   * @param scene プッシュするシーン
   */
  void Push(const std::shared_ptr<mhl::ISceneable>& scene);

  /**
   * @brief シーンをスタックからポップする
   *
   */
  void Pop();

  /**
   * @brief シーンをすべてクリアする
   *
   */
  void Clear();

  /**
   * @brief 現在のシーンを指定したシーンを切り替える
   *
   * @param scene 切り替えるシーン
   */
  void Swap(const std::shared_ptr<mhl::ISceneable>& scene);

 private:
  /**
   * @brief シーンの初期化処理
   *
   * @param scene 対象のシーン
   */
  void InitializeScene(const std::shared_ptr<mhl::ISceneable>& scene);

  /**
   * @brief シーンの終了処理
   *
   * @param scene 対象のシーン
   */
  void EndScene(const std::shared_ptr<mhl::ISceneable>& scene);

 private:
  std::list<std::shared_ptr<mhl::ISceneable> > stack_;
};

}  // namespace mhl

#endif  // MHL_SCENE_SCENESTACK_HPP_
