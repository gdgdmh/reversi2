#ifndef REVERSI_TEST_CODE_TESTSTDRANDOMINT_H_
#define REVERSI_TEST_CODE_TESTSTDRANDOMINT_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// 整数乱数生成テスト
class TestStdRandomInt : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestStdRandomInt(reversi::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestStdRandomInt();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTSTDRANDOMINT_H_
