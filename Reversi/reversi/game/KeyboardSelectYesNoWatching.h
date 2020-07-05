#ifndef REVERSI_GAME_KEYBOARDSELECTYESNOWATCHING_H_
#define REVERSI_GAME_KEYBOARDSELECTYESNOWATCHING_H_

#include "ISelectYesNoWatching.h"
#include "../util/IInputKeyboard.h"

namespace reversi {

// キーボードによるYes,No,Watching選択クラス
class KeyboardSelectYesNoWatching : public ISelectYesNoWatching {
private:
	static const int YES_UPPER_PATTERN_COUNT = 2;                           // Yesパターン
	static const std::string YES_UPPER_STRINGS[YES_UPPER_PATTERN_COUNT];    // Yesとみなす大文字文字列パターン
	static const int NO_UPPER_PATTERN_COUNT = 2;                            // Noパターン
	static const std::string NO_UPPER_STRINGS[NO_UPPER_PATTERN_COUNT];      // Noとみなす大文字文字列パターン
	static const int WATCHING_UPPER_PATTERN_COUNT = 2;                      // Watchパターン
	static const std::string WATCHING_UPPER_STRINGS[NO_UPPER_PATTERN_COUNT];// Watchingとみなす大文字文字列パターン
	// 選択
	enum class SELECT_REPLY {
		NONE,       // 未入力
		YES,        // はい
		NO,         // いいえ
		WATCHING    // 観戦
	};
public:

	/**
	 * コンストラクタ
	 */
	KeyboardSelectYesNoWatching();

	/**
	 * デストラクタ
	 */
	virtual ~KeyboardSelectYesNoWatching();

	/**
	 * 初期化
	 */
	void Initialize();

	/**
	 * メイン処理
	 */
	void Task();

	/**
	 * 選択し終わったか
	 * @return trueなら選択し終わっている
	 */
	bool IsSelected();

	/**
	 * Yesを選択したか
	 * @return trueならyes falseならno
	 */
	bool IsSelectYes();

	/**
	 * Noを選択したか
	 * @return trueならno
	 */
	bool IsSelectNo();

	/**
	 * Watchingを選択したか
	 * @return trueならwatching
	 */
	bool IsSelectWatching();

	/**
	 * 間違った入力をしたか
	 * @return trueなら間違った入力をした
	 */
	bool IsWrongInput();

private:

	/**
	 * 入力された文字列のタイプをチェック
	 * @param  checkString チェックする文字列
	 * @param  reply       戻り値がtrueだった場合タイプが入る
	 * @return             trueなら何かのタイプが入力された
	 */
	bool CheckInputStringType(const std::string& checkString, reversi::KeyboardSelectYesNoWatching::SELECT_REPLY& reply);

	/**
	 * 文字列を大文字に変換する
	 * @param targetString 対象の文字列
	 */
	void TransformStringUpper(std::string& targetString);

private:
	reversi::IInputKeyboard* inputKeyboard;                         // キーボード入力クラス
	reversi::KeyboardSelectYesNoWatching::SELECT_REPLY selectReply; // 選択した返答
	bool isWrongInput;                                              // 間違った入力をしたか

};

}

#endif  // REVERSI_GAME_KEYBOARDSELECTYESNOWATCHING_H_
