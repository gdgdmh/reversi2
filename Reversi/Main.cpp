// メモリリーク検出用
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <iostream>
#include <string>

#include "reversi/game/ReversiGameLoop.h"
#include "mhl/util/output/ioutput_console.hpp"
#include "mhl/util/output/output_console.hpp"
#include "mhl/test_code/test_mhl.hpp"
/*
#include "mhl/util/output/IOutputConsole.hpp"
#include "mhl/util/output/OutputConsole.hpp"
#include "mhl/test_code/TestMhl.hpp"
*/
#include "reversi/test_code/TestReversiProject.hpp"

// エントリーポイント;
int main(int argc, const char *argv[]) {
  // メモリリーク検出用
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  mhl::IOutputConsole *console = new mhl::OutputConsole();
  std::shared_ptr<mhl::IOutputConsole> c(new mhl::OutputConsole());
  console->PrintLine("--- main start -------------------");

  bool isTest = true;
  if (isTest) {
    // ライブラリのユニットテスト
    test_code::TestMhl mhl(c);
    mhl.ExecuteUnitTest();
    //test::TestMhl mhl(c);
    //mhl.ExecuteUnitTest();
    // リバーシプロジェクトに対するユニットテスト
    test_code::TestReversiProject rp(c);
    rp.ExecuteUnitTest();
  }

  // リバーシゲーム
  bool is_game_execute = true;
  if (is_game_execute) {
    reversi::ReversiGameLoop gameLoop;
    gameLoop.Initialize();
    gameLoop.Task();
  }

  /*
  while (true)
  {
          std::cout <<
  "　　　ａ　　　ｂ　　　ｃ　　　ｄ　　　ｅ　　　ｆ　　　ｇ　　　ｈ　　" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "１｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "２｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "３｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "４｜　　　｜　　　｜　　　｜　◯　｜　Ｘ　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "５｜　　　｜　　　｜　　　｜　Ｘ　｜　◯　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "６｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "７｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl; std::cout <<
  "８｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜　　　｜" <<
  std::endl; std::cout <<
  "　＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋ーーー＋" <<
  std::endl;

          std::string input;
          std::cout << "Your move: ";
          std::getline(std::cin, input);
          std::cout << "Opponent move: XX" << std::endl;
  }
  */
  console->PrintLine("--- main end -------------------");
  if (console) {
    delete console;
    console = NULL;
  }
  return 0;
}
