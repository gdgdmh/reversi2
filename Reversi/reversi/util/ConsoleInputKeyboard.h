#ifndef REVERSI_UTIL_CONSOLEINPUTKEYBOARD_H_
#define REVERSI_UTIL_CONSOLEINPUTKEYBOARD_H_

//#include <string>
#include "IInputKeyboard.h"

namespace reversi {

// コンソールキーボード入力クラス
class ConsoleInputKeyboard : public reversi::IInputKeyboard {
 public:
  /**
   * コンストラクタ
   */
  ConsoleInputKeyboard();

  /**
   * デストラクタ
   */
  virtual ~ConsoleInputKeyboard();

  /**
   * 1行単位での文字列入力を取る
   * @return 取得した文字列
   */
  std::string GetStringLine();
};

}  // namespace reversi

#endif  // REVERSI_UTIL_CONSOLEINPUTKEYBOARD_H_
