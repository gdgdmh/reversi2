#include "TestSimpleStack.h"
// test
#include "../../util/SimpleStack.h"
#include "../../util/Assert.h"

/**
 * コンストラクタ
 */
reversi::TestSimpleStack::TestSimpleStack(mhl::IOutputConsole* outputConsole) : UnitTestBase(outputConsole) {
}

/**
 * デストラクタ
 */
reversi::TestSimpleStack::~TestSimpleStack() {
}

/**
 * 実行
 * @return trueなら成功 falseなら失敗
 */
bool reversi::TestSimpleStack::Execute() {
	// pushとpopの値とサイズをチェック
	{
		const int STACK_SIZE = 10;
		reversi::SimpleStack<int> stack(STACK_SIZE);

		for (int i = 0; i < STACK_SIZE; ++i) {
			stack.Push(i);
		}
		if (!AssertEqual(stack.GetSize() == STACK_SIZE, "TestSimpleStack::Execute size invalid")) {
			return false;
		}
		// 最後尾データをチェック
		if (!AssertEqual(stack.Back() == (STACK_SIZE - 1), "TestSimpleStack::Execute back invalid")) {
			return false;
		}
		for (int i = (STACK_SIZE - 1); i >= 0; --i) {
			int data = stack.Pop();
			if (!AssertEqual(data == i, "TestSimpleStack::Execute pop value invalid")) {
				return false;
			}
			int stackSize = stack.GetSize();
			if (!AssertEqual(stackSize == i, "TestSimpleStack::Execute pop after size invalid")) {
				return false;
			}
		}
	}
	return true;
}

