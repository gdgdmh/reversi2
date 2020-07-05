#ifndef REVERSI_TEST_CODE_TESTSIMPLEARRAY_H_
#define REVERSI_TEST_CODE_TESTSIMPLEARRAY_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// 動的配列テスト
class TestSimpleArray : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestSimpleArray(mhl::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestSimpleArray();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTSIMPLEARRAY_H_
