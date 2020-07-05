#ifndef REVERSI_TEST_CODE_TESTREVERSEINFO_H_
#define REVERSI_TEST_CODE_TESTREVERSEINFO_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// 裏返し情報テストクラス
class TestReverseInfo : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestReverseInfo(reversi::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestReverseInfo();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTREVERSEINFO_H_
