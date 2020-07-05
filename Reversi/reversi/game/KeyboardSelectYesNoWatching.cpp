#include <algorithm>
#include "KeyboardSelectYesNoWatching.h"
#include "../util/Assert.h"
#include "../util/ConsoleInputKeyboard.h"


// 定数定義
// Yesとみなす大文字文字列パターン
const std::string reversi::KeyboardSelectYesNoWatching::YES_UPPER_STRINGS[YES_UPPER_PATTERN_COUNT] = {
	"Y",
	"YES"
};
// Noとみなす大文字文字列パターン
const std::string reversi::KeyboardSelectYesNoWatching::NO_UPPER_STRINGS[NO_UPPER_PATTERN_COUNT] = {
	"N",
	"NO"
};
// Watchingとみなす大文字文字列パターン
const std::string reversi::KeyboardSelectYesNoWatching::WATCHING_UPPER_STRINGS[NO_UPPER_PATTERN_COUNT] = {
	"W",
	"WATCHING"
};


/**
 * コンストラクタ
 */
reversi::KeyboardSelectYesNoWatching::KeyboardSelectYesNoWatching() : inputKeyboard(NULL), selectReply(reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::NONE), isWrongInput(false) {
}

/**
 * デストラクタ
 */
reversi::KeyboardSelectYesNoWatching::~KeyboardSelectYesNoWatching() {
	if (inputKeyboard) {
		delete inputKeyboard;
		inputKeyboard = NULL;
	}
}

/**
 * 初期化
 */
void reversi::KeyboardSelectYesNoWatching::Initialize() {
	inputKeyboard = new ConsoleInputKeyboard();
	selectReply = reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::NONE;
	isWrongInput = false;
}

/**
 * メイン処理
 */
void reversi::KeyboardSelectYesNoWatching::Task() {
	if (IsSelected()) {
		// 選択済みなので何もしない
		return;
	}
	// フラグリセット
	isWrongInput = false;

	// 文字列入力
	std::string selectString = inputKeyboard->GetStringLine();

	if (CheckInputStringType(selectString, selectReply)) {
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
bool reversi::KeyboardSelectYesNoWatching::IsSelected() {
	if (selectReply != reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::NONE) {
		return true;
	}
	return false;
}

/**
 * Yesを選択したか
 * @return trueならyes
 */
bool reversi::KeyboardSelectYesNoWatching::IsSelectYes() {
	if (selectReply == reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::YES) {
		return true;
	}
	return false;
}

/**
 * Noを選択したか
 * @return trueならno
 */
bool reversi::KeyboardSelectYesNoWatching::IsSelectNo() {
	if (selectReply == reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::NO) {
		return true;
	}
	return false;
}

/**
 * Watchingを選択したか
 * @return trueならwatching
 */
bool reversi::KeyboardSelectYesNoWatching::IsSelectWatching() {
	if (selectReply == reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::WATCHING) {
		return true;
	}
	return false;
}

/**
 * 間違った入力をしたか
 * @return trueなら間違った入力をした
 */
bool reversi::KeyboardSelectYesNoWatching::IsWrongInput() {
	return isWrongInput;
}

/**
 * 入力された文字列のタイプをチェック
 * @param  checkString チェックする文字列
 * @param  reply       戻り値がtrueだった場合タイプが入る
 * @return             trueなら何かのタイプが入力された
 */
bool reversi::KeyboardSelectYesNoWatching::CheckInputStringType(const std::string& checkString, reversi::KeyboardSelectYesNoWatching::SELECT_REPLY& reply) {
	// チェックする文字列を大文字に変換する(小文字指定でもOKとするため)
	std::string upperString = checkString;
	TransformStringUpper(upperString);

	for (int i = 0; i < YES_UPPER_PATTERN_COUNT; ++i) {
		reversi::Assert::AssertArrayRange(i, YES_UPPER_PATTERN_COUNT, "KeyboardSelectYesNoWatching::CheckInputStringType index over yes");
		if (upperString == YES_UPPER_STRINGS[i]) {
			// yesの入力があった
			reply = reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::YES;
			return true;
		}
	}
	for (int i = 0; i < NO_UPPER_PATTERN_COUNT; ++i) {
		reversi::Assert::AssertArrayRange(i, NO_UPPER_PATTERN_COUNT, "KeyboardSelectYesNoWatching::CheckInputStringType index over no");
		if (upperString == NO_UPPER_STRINGS[i]) {
			// noの入力があった
			reply = reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::NO;
			return true;
		}
	}
	for (int i = 0; i < WATCHING_UPPER_PATTERN_COUNT; ++i) {
		reversi::Assert::AssertArrayRange(i, WATCHING_UPPER_PATTERN_COUNT, "KeyboardSelectYesNoWatching::CheckInputStringType index over watching");
		if (upperString == WATCHING_UPPER_STRINGS[i]) {
			// watchingの入力があった
			reply = reversi::KeyboardSelectYesNoWatching::SELECT_REPLY::WATCHING;
			return true;
		}
	}
	// 間違った入力
	isWrongInput = true;
	return false;
}

/**
 * 文字列を大文字に変換する
 * @param targetString 対象の文字列
 */
void reversi::KeyboardSelectYesNoWatching::TransformStringUpper(std::string& targetString) {
	std::transform(targetString.begin(), targetString.end(), targetString.begin(), std::toupper);
}
