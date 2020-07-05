#ifndef REVERSI_TEST_CODE_TESTCALCBOARDEVALUATIONPOINTBYPOSITION_H_
#define REVERSI_TEST_CODE_TESTCALCBOARDEVALUATIONPOINTBYPOSITION_H_

#include "../base/UnitTestBase.h"

namespace reversi {

// 位置から盤の評価値を計算テストクラス
class TestCalcBoardEvaluationPointByPosition : public UnitTestBase {
public:
	/**
	 * コンストラクタ
	 */
	TestCalcBoardEvaluationPointByPosition(mhl::IOutputConsole* outputConsole);

	/**
	 * デストラクタ
	 */
	virtual ~TestCalcBoardEvaluationPointByPosition();

	/**
	 * 実行
	 * @return trueなら成功 falseなら失敗
	 */
	bool Execute();
};

}

#endif  // REVERSI_TEST_CODE_TESTCALCBOARDEVALUATIONPOINTBYPOSITION_H_
