#include "SceneStack.hpp"

/**
 * @brief Construct a new Scene Stack object
 *
 */
mhl::SceneStack::SceneStack() {}

/**
 * @brief Destroy the Scene Stack object
 *
 */
mhl::SceneStack::~SceneStack() {}

/**
 * @brief シーンの更新処理
 *
 */
void mhl::SceneStack::Update() {
  if (stack_.empty()) {
    return;
  }
  // 現在のシーン
  auto it = stack_.begin();
  (*it)->Update();
  ++it;
  // 現在より下のシーン(フラグがあるもののみ更新)
  for (; it != stack_.end(); ++it) {
    if ((*it)->IsUnderUpdate()) {
      (*it)->Update();
    }
  }
}

/**
 * @brief シーンの描画処理
 *
 */
void mhl::SceneStack::Draw() {
  if (stack_.empty()) {
    return;
  }
  // 現在のシーン
  auto it = stack_.begin();
  (*it)->Draw();
  ++it;
  // 現在より下のシーン(フラグがあるもののみ更新)
  for (; it != stack_.end(); ++it) {
    if ((*it)->IsUnderDraw()) {
      (*it)->Draw();
    }
  }
}

/**
 * @brief シーンをスタックにプッシュする
 *
 * @param scene プッシュするシーン
 */
void mhl::SceneStack::Push(const std::shared_ptr<mhl::ISceneable>& scene) {
  if (!stack_.empty()) {
    // pushされるときのイベントを通知
    auto it = stack_.begin();
    (*it)->EventPush(scene);
  }
  // pushするシーンの初期化
  InitializeScene(scene);
  // push
  stack_.push_front(scene);
}

/**
 * @brief シーンをスタックからポップする
 *
 */
void mhl::SceneStack::Pop() {
  if (stack_.empty()) {
    return;
  }
  // popイベントを通知
  auto it = stack_.begin();
  (*it)->EventPop();
  // release
  EndScene((*it));
  // pop
  stack_.pop_front();
}

/**
 * @brief シーンをすべてクリアする
 *
 */
void mhl::SceneStack::Clear() {
  // popイベント
  for (auto it = stack_.begin(); it != stack_.end(); ++it) {
    (*it)->EventPop();
    EndScene((*it));
  }
  // clear
  stack_.clear();
}

/**
 * @brief 現在のシーンを指定したシーンを切り替える
 *
 * @param scene 切り替えるシーン
 */
void mhl::SceneStack::Swap(const std::shared_ptr<mhl::ISceneable>& scene) {
  if (stack_.empty()) {
    return;
  }
  // swapイベントを通知
  auto it = stack_.begin();
  (*it)->EventSwap(scene);
  EndScene((*it));
  // init
  InitializeScene(scene);
  // pop
  stack_.pop_front();
  // push
  stack_.push_front(scene);
}

/**
 * @brief シーンの初期化処理
 *
 * @param scene 対象のシーン
 */
void mhl::SceneStack::InitializeScene(
    const std::shared_ptr<mhl::ISceneable>& scene) {
  scene->Initialize();
  scene->Load();
}

/**
 * @brief シーンの終了処理
 *
 * @param scene 対象のシーン
 */
void mhl::SceneStack::EndScene(const std::shared_ptr<mhl::ISceneable>& scene) {
  scene->Release();
}
