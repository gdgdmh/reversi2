#ifndef REVERSI_TEST_CODE_TESTDEVELOP_H_
#define REVERSI_TEST_CODE_TESTDEVELOP_H_

#include "../base/UnitTestBase.h"

// 前方宣言
namespace reversi {
class IOutputConsole;
}

namespace reversi {

	// 実装テスト用クラス
	class TestDevelop : public UnitTestBase {
	public:
		/**
		 * コンストラクタ
		 */
		TestDevelop(reversi::IOutputConsole* outputConsole);

		/**
		 * デストラクタ
		 */
		virtual ~TestDevelop();

		/**
		 * 実行
		 * @return trueなら成功 falseなら失敗
		 */
		bool Execute();

	private:
		IOutputConsole* console;
	};
}

#endif  // REVERSI_TEST_CODE_TESTDEVELOP_H_
