#ifndef MHL_TEST_CODE_TESTSCENESTACK_HPP_
#define MHL_TEST_CODE_TESTSCENESTACK_HPP_

#include <memory>

#include "../scene/ISceneable.hpp"
#include "../test/UnitTestBase.hpp"

namespace test {

class TestScene : public mhl::ISceneable {
 public:
  TestScene();

  virtual ~TestScene();

  /**
   * @brief シーンの初期化
   *
   */
  void Initialize();

  /**
   * @brief シーンの開放処理
   *
   */
  void Release();

  /**
   * @brief シーンのロード
   * 時間のかかる処理はここで行う
   */
  void Load();

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
   * @brief シーンがトップより下に積まれているときにシーンの更新を行うか設定する
   *
   * @param under_update trueなら更新処理を行う
   */
  void SetUnderUpdate(bool under_update);

  /**
   * @brief シーンがトップより下に積まれているときにシーンの更新を行うか
   *
   * @return true シーンの更新を行う
   * @return false シーンの更新をしない
   */
  bool IsUnderUpdate();

  /**
   * @brief シーンがトップより下に積まれているときにシーンの描画を行うか設定する
   *
   * @param under_draw trueなら描画処理を行う
   */
  void SetUnderDraw(bool under_draw);

  /**
   * @brief シーンがトップより下に積まれているときにシーンの描画を行うか
   *
   * @return true シーンの描画を行う
   * @return false シーンの描画をしない
   */
  bool IsUnderDraw();

  /**
   * @brief このシーンがポップ処理をされる前に呼び出される
   *
   */
  void EventPop();

  /**
   * @brief このシーンの上にプッシュ処理をされる前に呼び出される
   * ただし、このシーンが現在のシーンであるときのみ
   * @param next このシーンの上にプッシュされるシーン
   */
  void EventPush(std::shared_ptr<ISceneable> next);

  /**
   * @brief シーンのスワップ処理をされる前に呼び出される
   * ただし、このシーンが現在のシーンであるときのみ
   * @param next このシーンの代わりにスワップされるシーン
   */
  void EventSwap(std::shared_ptr<ISceneable> next);

  /**
   * @brief Initializeコールの取得
   *
   * @return int コールされた回数
   */
  int GetInitializeCall();

  /**
   * @brief Releaseコールの取得
   *
   * @return int コールされた回数
   */
  int GetReleaseCall();

  /**
   * @brief Loadコールの取得
   *
   * @return int コールされた回数
   */
  int GetLoadCall();

  /**
   * @brief Updateコールの取得
   *
   * @return int コールされた回数
   */
  int GetUpdateCall();

  /**
   * @brief Drawコールの取得
   *
   * @return int コールされた回数
   */
  int GetDrawCall();

  /**
   * @brief EventPopコールの取得
   *
   * @return int コールされた回数
   */
  int GetEventPopCall();

  /**
   * @brief EventPushコールの取得
   *
   * @return int コールされた回数
   */
  int GetEventPushCall();

  /**
   * @brief EventSwapコールの取得
   *
   * @return int コールされた回数
   */
  int GetEventSwapCall();

 private:
  bool under_update_;
  bool under_draw_;
  int call_initialize_;
  int call_release_;
  int call_load_;
  int call_update_;
  int call_draw_;
  int call_event_pop_;
  int call_event_push_;
  int call_event_swap_;
};

/**
 * @brief シーンスタックテスト
 *
 */
class TestSceneStack : public mhl::UnitTestBase {
 public:
  /**
   * @brief Construct a new Test Scene Stack object
   *
   * @param output_console 出力クラス
   */
  TestSceneStack(std::shared_ptr<mhl::IOutputConsole> output_console);

  /**
   * @brief Destroy the Test Scene Stack object
   *
   */
  virtual ~TestSceneStack();

  /**
   * @brief ユニットテスト実行
   *
   */
  void ExecuteUnitTest();

  /**
   * @brief Initializeコールのテスト
   *
   */
  void TestInitializeCall();

  /**
   * @brief Releaseコールのテスト
   *
   */
  void TestReleaseCall();

  /**
   * @brief Loadコールのテスト
   *
   */
  void TestLoadCall();

  /**
   * @brief Updateコールのテスト
   *
   */
  void TestUpdateCall();

  /**
   * @brief Drawコールのテスト
   *
   */
  void TestDrawCall();

  /**
   * @brief EventPushコールのテスト
   *
   */
  void TestEventPushCall();

  /**
   * @brief EventPopコールのテスト
   *
   */
  void TestEventPopCall();

  /**
   * @brief EventSwapコールのテスト
   *
   */
  void TestEventSwapCall();
};

}  // namespace test

#endif  // MHL_TEST_CODE_TESTSCENESTACK_HPP_
