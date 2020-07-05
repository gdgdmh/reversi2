#ifndef REVERSI_TEST_CODE_TESTSIMPLESTACK_H_
#define REVERSI_TEST_CODE_TESTSIMPLESTACK_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// スタックテスト
class TestSimpleStack : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestSimpleStack(reversi::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestSimpleStack();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTSIMPLESTACK_H_
