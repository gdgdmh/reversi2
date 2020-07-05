#ifndef REVERSI_TEST_CODE_TESTREVERSI_H_
#define REVERSI_TEST_CODE_TESTREVERSI_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// リバーシテストクラス
class TestReversi : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestReversi(mhl::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestReversi();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTREVERSI_H_
