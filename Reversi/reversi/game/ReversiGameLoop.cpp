#include "ReversiGameLoop.h"
#include "../util/Assert.h"


/**
 * コンストラクタ
 */
reversi::ReversiGameLoop::ReversiGameLoop() {
}

/**
 * デストラクタ
 */
reversi::ReversiGameLoop::~ReversiGameLoop() {
}

/**
 * 初期化
 */
void reversi::ReversiGameLoop::Initialize() {
	reversiGameScene.Initialize();
}

/**
 * メイン処理
 */
void reversi::ReversiGameLoop::Task() {
	while (true) {
		if (!reversiGameScene.Task()) {
			// 終了
			break;
		}
	}
}
