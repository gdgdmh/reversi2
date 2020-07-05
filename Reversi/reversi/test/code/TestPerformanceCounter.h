#ifndef REVERSI_TEST_CODE_TESTPERFORMANCECOUNTER_H_
#define REVERSI_TEST_CODE_TESTPERFORMANCECOUNTER_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// パフォーマンスカウンタテストクラス
class TestPerformanceCounter : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestPerformanceCounter(reversi::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestPerformanceCounter();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTPERFORMANCECOUNTER_H_
