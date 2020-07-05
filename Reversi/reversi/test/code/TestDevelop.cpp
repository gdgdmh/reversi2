#include "TestDevelop.h"
// test include(テストするものはここに追加する)
#include "../../util/IOutputConsole.h"
#include "../../util/OutputConsole.h"
#include "../../logic/base/Board.h"
#include "../../logic/base/Move.h"

#include "../code/TestBoard.h"
#include "../code/TestMove.h"
#include "../code/TestReverseInfo.h"
#include "../code/TestReversi.h"
#include "../code/TestStdRandomInt.h"
#include "../code/TestReversiCpu.h"
#include "../code/TestCalcBoardEvaluationPointByPosition.h"
#include "../code/TestThinkingNode.h"
#include "../code/TestSimpleStack.h"
#include "../code/TestSimpleArray.h"
#include "../code/TestPerformanceCounter.h"

/**
 * コンストラクタ
 */
reversi::TestDevelop::TestDevelop(reversi::IOutputConsole* outputConsole) : UnitTestBase(outputConsole), console(NULL) {
	console = new OutputConsole();
}

/**
 * デストラクタ
 */
reversi::TestDevelop::~TestDevelop() {
	if (console) {
		delete console;
		console = NULL;
	}
}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestDevelop::Execute() {
	console->PrintLine("--- TestDevelop start -------------------");

	// UnitTest
	{
		// TestBoard
		{
			reversi::TestBoard t(console);
			if (!t.Execute()) {
				return false;
			}
		}
		// TestMove
		{
			reversi::TestMove m(console);
			if (!m.Execute()) {
				return false;
			}
		}
		// TestReverseInfo
		{
			reversi::TestReverseInfo info(console);
			if (!info.Execute()) {
				return false;
			}
		}
		// TestReversi
		{
			reversi::TestReversi r(console);
			if (!r.Execute()) {
				return false;
			}
		}
		// TestStdRandomInt
		{
			reversi::TestStdRandomInt s(console);
			if (!s.Execute()) {
				return false;
			}
		}
		// TestReversiCpu
		{
			reversi::TestReversiCpu c(console);
			if (!c.Execute()) {
				return false;
			}
		}
		// TestCalcBoardEvaluationPointByPosition
		{
			reversi::TestCalcBoardEvaluationPointByPosition calc(console);
			if (!calc.Execute()) {
				return false;
			}
		}
		// TestThinkingNode
		{
			reversi::TestThinkingNode n(console);
			if (!n.Execute()) {
				return false;
			}
		}
		// TestSimpleStack
		{
			reversi::TestSimpleStack s(console);
			if (!s.Execute()) {
				return false;
			}
		}
		// TestSimpleArray
		{
			reversi::TestSimpleArray s(console);
			if (!s.Execute()) {
				return false;
			}
		}
		// TestPerformanceCounter
		{
			reversi::TestPerformanceCounter c(console);
			if (!c.Execute()) {
				return false;
			}
		}
	}

	// test code here

	console->PrintLine("--- TestDevelop end -------------------");
	return true;
}
