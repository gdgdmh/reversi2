#include "PerformanceCounter.h"

/**
 * コンストラクタ
 */
reversi::PerformanceCounter::PerformanceCounter() {}

/**
 * デストラクタ
 */
reversi::PerformanceCounter::~PerformanceCounter() {}

/**
 * 計測開始
 */
void reversi::PerformanceCounter::Start() {
  // タイマー周波数の取得
  QueryPerformanceFrequency(&frequency);
  // 計測開始
  QueryPerformanceCounter(&start);
}

/**
 * 計測終了
 */
void reversi::PerformanceCounter::End() {
  // 計測開始
  QueryPerformanceCounter(&end);
}

/**
 * 差分取得(ミリ秒)
 * @return StartとEndの時間差分
 */
double reversi::PerformanceCounter::GetDiff() const {
  LONGLONG timeDiff = end.QuadPart - start.QuadPart;
  // 差分をdouble型に変換
  double doubleDiff = (double)timeDiff;
  // ミリ秒
  doubleDiff = ((doubleDiff * 1000) / (double)frequency.QuadPart);
  return doubleDiff;
}
