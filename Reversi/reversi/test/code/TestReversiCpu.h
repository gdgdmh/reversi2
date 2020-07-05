#ifndef REVERSI_TEST_CODE_TESTREVERSICPU_H_
#define REVERSI_TEST_CODE_TESTREVERSICPU_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// リバーシCPU連続対局テストクラス
class TestReversiCpu : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestReversiCpu(mhl::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestReversiCpu();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTREVERSICPU_H_
