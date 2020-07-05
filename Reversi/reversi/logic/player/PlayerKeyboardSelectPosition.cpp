#include <iostream>
#include <algorithm>
#include "PlayerKeyboardSelectPosition.h"
#include "../../../mhl/util/output/IOutputConsole.hpp"
#include "../../util/Assert.h"
#include "../../util/IInputKeyboard.h"
#include "../../util/ConsoleInputKeyboard.h"

/**
 * コンストラクタ
 */
reversi::PlayerKeyboardSelectPosition::PlayerKeyboardSelectPosition() {
}

/**
 * デストラクタ
 */
reversi::PlayerKeyboardSelectPosition::~PlayerKeyboardSelectPosition() {
}

/**
 * 位置選択を取得する
 * @param  position 選択した位置
 * @return          trueなら位置選択した
 */
bool reversi::PlayerKeyboardSelectPosition::GetSelectPosition(reversi::ReversiConstant::POSITION& position) {
	reversi::IInputKeyboard* inputKeyboard = new ConsoleInputKeyboard();
	std::string positionName = "";
	// キーボードから位置の文字列を取得する
	positionName = inputKeyboard->GetStringLine();
	if (inputKeyboard) {
		delete inputKeyboard;
		inputKeyboard = NULL;
	}
	// 小文字で入力したときのために大文字に変換する
	TransformStringUpper(positionName);
	// 文字列から座標へ変換
	if (reversi::ReversiConstant::GetStringToPosition(positionName, position)) {
		return true;
	}
	return false;
}

/**
 * 大文字に変換する
 * @param targetString 変換対象の文字列
 */
void reversi::PlayerKeyboardSelectPosition::TransformStringUpper(std::string& targetString) {
	std::transform(targetString.begin(), targetString.end(), targetString.begin(), std::toupper);
}
