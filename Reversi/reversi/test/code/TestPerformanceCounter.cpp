#include "TestPerformanceCounter.h"
// test
#include "../../util/PerformanceCounter.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::TestPerformanceCounter::TestPerformanceCounter(mhl::IOutputConsole* outputConsole) : UnitTestBase(outputConsole) {
}

/**
 * デストラクタ
 */
reversi::TestPerformanceCounter::~TestPerformanceCounter() {
}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestPerformanceCounter::Execute() {

	// 時間計測ができるか
	reversi::PerformanceCounter counter;
	counter.Start();
	// 少しだけ時間稼ぎ
	for (int i = 0; i < 1000; ++i) {
	}
	counter.End();
	double diff = counter.GetDiff();
	if (!AssertEqual(diff > 0.0000000, "TestPerformanceCounter::Execute diff invalid")) {
		return false;
	}

	return true;
}

