#include <algorithm>
#include "KeyboardSelectCpuLevel.h"
#include "../util/Assert.h"
#include "../util/ConsoleInputKeyboard.h"


// 定数定義

// CPULEVELとみなす文字列パターン
const std::string reversi::KeyboardSelectCpuLevel::LEVEL_STRINGS[LEVEL_PATTERN_COUNT] = {
	"1",
	"2",
	"3",
	"4"
};

/**
 * コンストラクタ
 */
reversi::KeyboardSelectCpuLevel::KeyboardSelectCpuLevel() : inputKeyboard(NULL), isSelected(false), isWrongInput(false), cpuLevel(DEFAULT_CPU_LEVEL) {
}

/**
 * デストラクタ
 */
reversi::KeyboardSelectCpuLevel::~KeyboardSelectCpuLevel() {
	if (inputKeyboard) {
		delete inputKeyboard;
		inputKeyboard = NULL;
	}
}

/**
 * 初期化
 */
void reversi::KeyboardSelectCpuLevel::Initialize() {
	inputKeyboard = new ConsoleInputKeyboard();
	isSelected = false;
	isWrongInput = false;
	cpuLevel = DEFAULT_CPU_LEVEL;
}

/**
 * メイン処理
 */
void reversi::KeyboardSelectCpuLevel::Task() {
	if (IsSelected()) {
		// 選択済みなので何もしない
		return;
	}
	// フラグリセット
	isWrongInput = false;

	// 文字列入力
	std::string selectString = inputKeyboard->GetStringLine();

	if (CheckInputStringLevel(selectString, cpuLevel)) {
		// 有効な入力があった
		return;
	}
	// 有効な入力がなかった
	isWrongInput = true;
}

/**
 * 選択し終わったか
 * @return trueなら選択し終わっている
 */
bool reversi::KeyboardSelectCpuLevel::IsSelected() {
	return isSelected;
}

/**
 * Cpuレベルを取得する
 * @return cpuレベル
 */
int reversi::KeyboardSelectCpuLevel::GetCpuLevel() {
	return cpuLevel;
}

/**
 * 間違った入力をしたか
 * @return trueなら間違った入力をした
 */
bool reversi::KeyboardSelectCpuLevel::IsWrongInput() {
	return isWrongInput;
}

/**
 * 入力された文字列のCPUレベルをチェック
 * @param  checkString    チェックする文字列
 * @param  selectCpuLevel 戻り値がtrueだった場合CPUレベルが入る
 * @return                trueならCPUレベルが入力された
 */
bool reversi::KeyboardSelectCpuLevel::CheckInputStringLevel(const std::string& checkString, int& selectCpuLevel) {
	for (int i = 0; i < LEVEL_PATTERN_COUNT; ++i) {
		reversi::Assert::AssertArrayRange(i, LEVEL_PATTERN_COUNT, "KeyboardSelectCpuLevel::CheckInputStringLevel index over yes");
		// 文字列一致をチェック
		if (checkString == LEVEL_STRINGS[i]) {
			isSelected = true;
			// intへ変換
			selectCpuLevel = std::stoi(checkString);
			return true;
		}
	}
	return false;
}
