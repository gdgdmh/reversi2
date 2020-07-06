#include "TestInstanceOfTest.hpp"

#include <list>

/**
 * コンストラクタ
 */
test::TestInstanceOfTest::TestInstanceOfTest(
    std::shared_ptr<mhl::IOutputConsole> output_console)
    : UnitTestBase(output_console) {}

/**
 * デストラクタ
 */
test::TestInstanceOfTest::~TestInstanceOfTest() {}

void test::TestInstanceOfTest::ExecuteUnitTest() {
  /*
  std::list<std::shared_ptr<Enemy> > enemys;
  {
      enemys.push_back(std::shared_ptr<LightEnemy>(new LightEnemy()));
      enemys.push_back(std::shared_ptr<DarkEnemy>(new DarkEnemy()));
  }

  for (std::list<std::shared_ptr<Enemy> >::iterator it = enemys.begin(); it !=
  enemys.end(); ++it) { std::shared_ptr<Enemy> e(*it);
    e->Attack(output_console_);
  }
  */
  // LightEnemyがEnemyの子であることをチェック
  AssertEquals((std::is_base_of<Enemy, LightEnemy>::value == true),
               "TestInstanceOfTest not EnemyBase");

  LightEnemy le;

  AssertEquals(instanceOf<Enemy>(&le), "TestInstanceOfTest not EnemyBase 2");
  AssertEquals(instanceOf<LightEnemy>(&le),
               "TestInstanceOfTest not EnemyBase 3");
}
