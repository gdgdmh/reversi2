#ifndef REVERSI_UTIL_PERFORMANCECOUNTER_H_
#define REVERSI_UTIL_PERFORMANCECOUNTER_H_

#include <windows.h>

namespace reversi {

// パフォーマンスカウンタクラス
// Windows環境に依存しているので他環境では外すことを検討
class PerformanceCounter {
 public:
  /**
   * コンストラクタ
   */
  PerformanceCounter();

  /**
   * デストラクタ
   */
  virtual ~PerformanceCounter();

  /**
   * 計測開始
   */
  void Start();

  /**
   * 計測終了
   */
  void End();

  /**
   * 差分取得(ミリ秒)
   * @return StartとEndの時間差分
   */
  double GetDiff() const;

 private:
  LARGE_INTEGER frequency;  // 周波数
  LARGE_INTEGER start;      // 開始時間
  LARGE_INTEGER end;        // 終了時間
};

}  // namespace reversi

#endif  // REVERSI_UTIL_PERFORMANCECOUNTER_H_
