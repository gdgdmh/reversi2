#ifndef REVERSI_UTIL_SIMPLESTACK_H_
#define REVERSI_UTIL_SIMPLESTACK_H_

#include "Assert.h"

namespace reversi {

// スタッククラス(代入演算子対策はしていないので使わないこと)
template <class T>
class SimpleStack {
public:
	/**
	 * コンストラクタ
	 * @param size スタックの最大サイズ
	 */
	SimpleStack(int size) {
		reversi::Assert::AssertEquals(size > 0, "SimpleStack::SimpleStack invalid size");
		datas = new T[size];
		index = 0;
		maxSize = size;
	}

	/**
	 * デストラクタ
	 */
	virtual ~SimpleStack() {
		if (datas) {
			delete datas;
			datas = NULL;
		}
	}

	/**
	 * データを格納する
	 * @param data データ
	 */
	void Push(T& data) {
		reversi::Assert::AssertArrayRange(index, maxSize, "SimpleStack::Push size full");
		datas[index] = data;
		++index;
	}

	/**
	 * データを取り出す
	 * @return データ
	 */
	T& Pop() {
		--index;
		reversi::Assert::AssertArrayRange(index, maxSize, "SimpleStack::Pop index over");
		return datas[index];
	}

	/**
	 * データを取り出さずに参照する
	 * @return データ
	 */
	T& Back() {
		reversi::Assert::AssertArrayRange(index - 1, maxSize, "SimpleStack::Back index over");
		return datas[index - 1];
	}

	/**
	 * データサイズの取得
	 * @return データサイズ
	 */
	int GetSize() const {
		return index;
	}

	// 代入演算子とコピーコンストラクタの禁止
private:
	void operator =(const SimpleStack<T>& source) {
	}
	SimpleStack(const SimpleStack<T>& source) {
	}
private:
	T* datas;       // データ配列
	int index;      // データのインデックス
	int maxSize;    // 最大サイズ
};

}

#endif  // REVERSI_UTIL_SIMPLESTACK_H_
