#include "test_scene_stack.hpp"

#include "../scene/scene_stack.hpp"

test_code::TestScene::TestScene()
    : under_update_(false),
      under_draw_(false),
      call_initialize_(0),
      call_release_(0),
      call_load_(0),
      call_update_(0),
      call_draw_(0),
      call_event_pop_(0),
      call_event_push_(0),
      call_event_swap_(0) {}

test_code::TestScene::~TestScene() {}

/**
 * @brief シーンの初期化
 *
 */
void test_code::TestScene::Initialize() { ++call_initialize_; }

/**
 * @brief シーンの開放処理
 *
 */
void test_code::TestScene::Release() { ++call_release_; }

/**
 * @brief シーンのロード
 * 時間のかかる処理はここで行う
 */
void test_code::TestScene::Load() { ++call_load_; }

/**
 * @brief シーンの更新処理
 *
 */
void test_code::TestScene::Update() { ++call_update_; }

/**
 * @brief シーンの描画処理
 *
 */
void test_code::TestScene::Draw() { ++call_draw_; }

/**
 * @brief シーンがトップより下に積まれているときにシーンの更新を行うか設定する
 *
 * @param under_update trueなら更新処理を行う
 */
void test_code::TestScene::SetUnderUpdate(bool under_update) {
  under_update_ = under_update;
}

/**
 * @brief シーンがトップより下に積まれているときにシーンの更新を行うか
 *
 * @return true シーンの更新を行う
 * @return false シーンの更新をしない
 */
bool test_code::TestScene::IsUnderUpdate() { return under_update_; }

/**
 * @brief シーンがトップより下に積まれているときにシーンの描画を行うか設定する
 *
 * @param under_draw trueなら描画処理を行う
 */
void test_code::TestScene::SetUnderDraw(bool under_draw) {
  under_draw_ = under_draw;
}

/**
 * @brief シーンがトップより下に積まれているときにシーンの描画を行うか
 *
 * @return true シーンの描画を行う
 * @return false シーンの描画をしない
 */
bool test_code::TestScene::IsUnderDraw() { return under_draw_; }

/**
 * @brief このシーンがポップ処理をされる前に呼び出される
 *
 */
void test_code::TestScene::EventPop() { ++call_event_pop_; }

/**
 * @brief このシーンの上にプッシュ処理をされる前に呼び出される
 * ただし、このシーンが現在のシーンであるときのみ
 * @param next このシーンの上にプッシュされるシーン
 */
void test_code::TestScene::EventPush(std::shared_ptr<ISceneable> next) {
  ++call_event_push_;
}

/**
 * @brief シーンのスワップ処理をされる前に呼び出される
 * ただし、このシーンが現在のシーンであるときのみ
 * @param next このシーンの代わりにスワップされるシーン
 */
void test_code::TestScene::EventSwap(std::shared_ptr<ISceneable> next) {
  ++call_event_swap_;
}

/**
 * @brief Initializeコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetInitializeCall() { return call_initialize_; }

/**
 * @brief Releaseコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetReleaseCall() { return call_release_; }

/**
 * @brief Loadコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetLoadCall() { return call_load_; }

/**
 * @brief Updateコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetUpdateCall() { return call_update_; }

/**
 * @brief Drawコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetDrawCall() { return call_draw_; }

/**
 * @brief EventPopコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetEventPopCall() { return call_event_pop_; }

/**
 * @brief EventPushコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetEventPushCall() { return call_event_push_; }

/**
 * @brief EventSwapコールの取得
 *
 * @return int コールされた回数
 */
int test_code::TestScene::GetEventSwapCall() { return call_event_swap_; }

/**
 * @brief Construct a new Test Scene Stack object
 *
 * @param output_console 出力クラス
 */
test_code::TestSceneStack::TestSceneStack(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : mhl::UnitTestBase(output_console) {}

/**
 * @brief Destroy the Test Scene Stack object
 *
 */
test_code::TestSceneStack::~TestSceneStack() {}

/**
 * @brief ユニットテスト実行
 *
 */
void test_code::TestSceneStack::ExecuteUnitTest() {
  TestInitializeCall();
  TestReleaseCall();
  TestLoadCall();
  TestUpdateCall();
  TestDrawCall();
  TestEventPushCall();
  TestEventPopCall();
  TestEventSwapCall();
}

/**
 * @brief Initializeコールのテスト
 *
 */
void test_code::TestSceneStack::TestInitializeCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test->GetInitializeCall() == 0, "");
  stack.Push(test);
  AssertEquals(test->GetInitializeCall() == 1, "");
  stack.Pop();
  AssertEquals(test->GetInitializeCall() == 1, "");
}

/**
 * @brief Releaseコールのテスト
 *
 */
void test_code::TestSceneStack::TestReleaseCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test->GetReleaseCall() == 0, "");
  stack.Push(test);
  AssertEquals(test->GetReleaseCall() == 0, "");
  stack.Pop();
  AssertEquals(test->GetReleaseCall() == 1, "");
}

/**
 * @brief Loadコールのテスト
 *
 */
void test_code::TestSceneStack::TestLoadCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test->GetLoadCall() == 0, "");
  stack.Push(test);
  AssertEquals(test->GetLoadCall() == 1, "");
  stack.Pop();
  AssertEquals(test->GetLoadCall() == 1, "");
}

/**
 * @brief Updateコールのテスト
 *
 */
void test_code::TestSceneStack::TestUpdateCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test->GetUpdateCall() == 0, "");
  stack.Push(test);
  AssertEquals(test->GetUpdateCall() == 0, "");
  stack.Update();
  AssertEquals(test->GetUpdateCall() == 1, "");
  stack.Pop();
  AssertEquals(test->GetUpdateCall() == 1, "");
}

/**
 * @brief Drawコールのテスト
 *
 */
void test_code::TestSceneStack::TestDrawCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test->GetDrawCall() == 0, "");
  stack.Push(test);
  AssertEquals(test->GetDrawCall() == 0, "");
  stack.Draw();
  AssertEquals(test->GetDrawCall() == 1, "");
  stack.Pop();
  AssertEquals(test->GetDrawCall() == 1, "");
}

/**
 * @brief EventPushコールのテスト
 *
 */
void test_code::TestSceneStack::TestEventPushCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test_first(new test_code::TestScene());
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test_first->GetEventPushCall() == 0, "");
  AssertEquals(test->GetEventPushCall() == 0, "");
  stack.Push(test_first);
  AssertEquals(test_first->GetEventPushCall() == 0, "");
  AssertEquals(test->GetEventPushCall() == 0, "");
  stack.Push(test);
  AssertEquals(test_first->GetEventPushCall() == 1, "");
  AssertEquals(test->GetEventPushCall() == 0, "");
  stack.Update();
  stack.Draw();
  AssertEquals(test_first->GetEventPushCall() == 1, "");
  AssertEquals(test->GetEventPushCall() == 0, "");
  stack.Pop();
  AssertEquals(test_first->GetEventPushCall() == 1, "");
  AssertEquals(test->GetEventPushCall() == 0, "");
  stack.Pop();
  AssertEquals(test_first->GetEventPushCall() == 1, "");
  AssertEquals(test->GetEventPushCall() == 0, "");
}

/**
 * @brief EventPopコールのテスト
 *
 */
void test_code::TestSceneStack::TestEventPopCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test_first(new test_code::TestScene());
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test_first->GetEventPopCall() == 0, "");
  AssertEquals(test->GetEventPopCall() == 0, "");
  stack.Push(test_first);
  AssertEquals(test_first->GetEventPopCall() == 0, "");
  AssertEquals(test->GetEventPopCall() == 0, "");
  stack.Push(test);
  AssertEquals(test_first->GetEventPopCall() == 0, "");
  AssertEquals(test->GetEventPopCall() == 0, "");
  stack.Update();
  stack.Draw();
  AssertEquals(test_first->GetEventPopCall() == 0, "");
  AssertEquals(test->GetEventPopCall() == 0, "");
  stack.Pop();
  AssertEquals(test_first->GetEventPopCall() == 0, "");
  AssertEquals(test->GetEventPopCall() == 1, "");
  stack.Pop();
  AssertEquals(test_first->GetEventPopCall() == 1, "");
  AssertEquals(test->GetEventPopCall() == 1, "");
}

/**
 * @brief EventSwapコールのテスト
 *
 */
void test_code::TestSceneStack::TestEventSwapCall() {
  mhl::SceneStack stack;
  std::shared_ptr<test_code::TestScene> test_first(new test_code::TestScene());
  std::shared_ptr<test_code::TestScene> test(new test_code::TestScene());
  AssertEquals(test_first->GetEventSwapCall() == 0, "");
  AssertEquals(test->GetEventSwapCall() == 0, "");
  stack.Push(test_first);
  AssertEquals(test_first->GetEventSwapCall() == 0, "");
  AssertEquals(test->GetEventSwapCall() == 0, "");
  stack.Update();
  stack.Draw();
  AssertEquals(test_first->GetEventSwapCall() == 0, "");
  AssertEquals(test->GetEventSwapCall() == 0, "");
  stack.Swap(test);
  AssertEquals(test_first->GetEventSwapCall() == 1, "");
  AssertEquals(test->GetEventSwapCall() == 0, "");
  stack.Pop();
  AssertEquals(test_first->GetEventSwapCall() == 1, "");
  AssertEquals(test->GetEventSwapCall() == 0, "");
}
