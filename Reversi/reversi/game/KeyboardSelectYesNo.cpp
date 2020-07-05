#include <algorithm>
#include "KeyboardSelectYesNo.h"
#include "../util/Assert.h"
#include "../util/ConsoleInputKeyboard.h"


// 定数定義
// Yesとみなす大文字文字列パターン
const std::string reversi::KeyboardSelectYesNo::YES_UPPER_STRINGS[YES_UPPER_PATTERN_COUNT] = {
	"Y",
	"YES"
};
// Noとみなす大文字文字列パターン
const std::string reversi::KeyboardSelectYesNo::NO_UPPER_STRINGS[NO_UPPER_PATTERN_COUNT] = {
	"N",
	"NO"
};

/**
 * コンストラクタ
 */
reversi::KeyboardSelectYesNo::KeyboardSelectYesNo() : inputKeyboard(NULL), isSelected(false), isYes(true), isWrongInput(false) {
}

/**
 * デストラクタ
 */
reversi::KeyboardSelectYesNo::~KeyboardSelectYesNo() {
	if (inputKeyboard) {
		delete inputKeyboard;
		inputKeyboard = NULL;
	}
}

/**
 * 初期化
 */
void reversi::KeyboardSelectYesNo::Initialize() {
	if (inputKeyboard == NULL) {
		inputKeyboard = new ConsoleInputKeyboard();
	}
	isSelected = false;
	isYes = true;
	isWrongInput = false;
}

/**
 * メイン処理
 */
void reversi::KeyboardSelectYesNo::Task() {
	if (isSelected) {
		// 選択済みなので何もしない
		return;
	}
	// フラグリセット
	isWrongInput = false;

	// 文字列入力
	std::string selectString = inputKeyboard->GetStringLine();
	if (!CheckValidString(selectString)) {
		// 有効な文字列が指定されなかった
		isWrongInput = true;
		return;
	}

	if (IsStringYes(selectString)) {
		// Yesを選択
		isSelected = true;
		isYes = true;
		return;
	}
	// Noを選択
	isSelected = true;
	isYes = false;
}

/**
 * 選択し終わったか
 * @return trueなら選択し終わっている
 */
bool reversi::KeyboardSelectYesNo::IsSelected() {
	return isSelected;
}

/**
 * Yesを選択したか
 * @return trueならyes falseならno
 */
bool reversi::KeyboardSelectYesNo::IsSelectYes() {
	return isYes;
}

/**
 * 間違った入力をしたか
 * @return trueなら間違った入力をした
 */
bool reversi::KeyboardSelectYesNo::IsWrongInput() {
	return isWrongInput;
}

/**
 * YesかNoと解釈できる文字列が指定されたかチェックする
 * @param  checkString チェックする文字列
 * @return             trueなら正しい文字列が指定された
 */
bool reversi::KeyboardSelectYesNo::CheckValidString(const std::string& checkString) {

	// チェックする文字列を大文字に変換する(小文字指定でもOKとするため)
	std::string upperString = checkString;
	TransformStringUpper(upperString);

	for (int i = 0; i < YES_UPPER_PATTERN_COUNT; ++i) {
		if (upperString == YES_UPPER_STRINGS[i]) {
			// yesを入力
			return true;
		}
	}
	for (int i = 0; i < NO_UPPER_PATTERN_COUNT; ++i) {
		if (upperString == NO_UPPER_STRINGS[i]) {
			// noを入力
			return true;
		}
	}
	// YesでもNoでもない文字列だった
	return false;
}

/**
 * 文字列を大文字に変換する
 * @param targetString 対象の文字列
 */
void reversi::KeyboardSelectYesNo::TransformStringUpper(std::string& targetString) {
	std::transform(targetString.begin(), targetString.end(), targetString.begin(), std::toupper);
}

/**
 * 文字列がYesと解釈できるか
 * @param  checkString チェックスル文字列
 * @return             trueならYesと解釈できる文字列
 */
bool reversi::KeyboardSelectYesNo::IsStringYes(const std::string& checkString) {
	// チェックする文字列を大文字に変換する(小文字指定でもOKとするため)
	std::string upperString = checkString;
	TransformStringUpper(upperString);

	for (int i = 0; i < YES_UPPER_PATTERN_COUNT; ++i) {
		if (upperString == YES_UPPER_STRINGS[i]) {
			return true;
		}
	}
	return false;
}
