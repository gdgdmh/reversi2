#ifndef REVERSI_UTIL_SIMPLEVECTOR_H_
#define REVERSI_UTIL_SIMPLEVECTOR_H_

#include "Assert.h"

namespace reversi {

// 動的配列クラス(代入演算子対策はしていないので使わないこと)
template <class T>
class SimpleArray {
 public:
  /**
   * コンストラクタ
   * @param size スタックの最大サイズ
   */
  SimpleArray(int size) {
    reversi::Assert::AssertEqual(size > 0,
                                  "SimpleArray::SimpleArray invalid size");
    datas = new T[size];
    index = 0;
    maxSize = size;
  }

  /**
   * デストラクタ
   */
  virtual ~SimpleArray() {
    if (datas) {
      delete datas;
      datas = NULL;
    }
  }

  /**
   * 配列の要素へアクセスする
   * @param  index 配列のindex
   * @return       データ
   */
  T& At(int index) {
    reversi::Assert::AssertArrayRange(index, maxSize,
                                      "SimpleArray::At index over");
    return datas[index];
  }

  /**
   * データを最後尾に追加
   * @param data 追加するデータ
   */
  void PushBack(T& data) {
    reversi::Assert::AssertArrayRange(index, maxSize,
                                      "SimpleArray::PushBack size full");
    datas[index] = data;
    ++index;
  }

  /**
   * データサイズの取得
   * @return データサイズ
   */
  int GetSize() const { return index; }

 private:
  T* datas;     // データ配列
  int index;    // データのインデックス
  int maxSize;  // 最大サイズ
};

}  // namespace reversi

#endif  // REVERSI_UTIL_SIMPLEVECTOR_H_
