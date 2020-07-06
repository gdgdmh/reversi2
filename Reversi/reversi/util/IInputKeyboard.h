#ifndef REVERSI_UTIL_IINPUTKEYBOARD_H_
#define REVERSI_UTIL_IINPUTKEYBOARD_H_

#include <string>

namespace reversi {

// キーボード入力インターフェース
class IInputKeyboard {
 public:
  /**
   * デストラクタ
   */
  virtual ~IInputKeyboard() {}

  /**
   * 1行単位での文字列入力を取る
   * @return 取得した文字列
   */
  virtual std::string GetStringLine() = 0;
};

}  // namespace reversi

#endif  // REVERSI_UTIL_IINPUTKEYBOARD_H_
