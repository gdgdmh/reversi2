#include "bit_control_uint32.hpp"

/**
 * @brief デフォルトコンストラクタ
 *
 */
mhl::BitControlUint32::BitControlUint32() : value_(0) {}

/**
 * @brief コンストラクタ
 *
 * @param value 初期化値
 */
mhl::BitControlUint32::BitControlUint32(uint32_t value) : value_(value) {}

/**
 * @brief デストラクタ
 *
 */
mhl::BitControlUint32::~BitControlUint32() {}

/**
 * @brief 値の設定
 *
 * @param value 設定する値
 */
void mhl::BitControlUint32::Set(uint32_t value) { value_ = value; }

/**
 * @brief 指定ビットをONにする
 *
 * @param bit 指定ビット
 */
void mhl::BitControlUint32::BitOn(uint32_t bit) { value_ |= (1 << bit); }

/**
 * @brief 指定ビットをOFFにする
 *
 * @param bit 指定ビット
 */
void mhl::BitControlUint32::BitOff(uint32_t bit) { value_ &= ~(1 << bit); }

/**
 * @brief ビットの切り替え
 * 指定ビットがONならOFFに切り替える
 * 指定ビットがOFFならONに切り替える
 *
 * @param bit 指定ビット
 */
void mhl::BitControlUint32::BitToggle(uint32_t bit) { value_ ^= (1 << bit); }

/**
 * @brief 値の取得
 *
 * @return uint32_t 値
 */
uint32_t mhl::BitControlUint32::Get() const { return value_; }

/**
 * @brief ビットの取得
 *
 * @param bit 何ビット目を取得するか
 * @return true 指定のビットが立っている
 * @return false 指定のビットが立っていない
 */
bool mhl::BitControlUint32::GetBit(uint32_t bit) const {
  if (value_ & (1 << bit)) {
    return true;
  }
  return false;
}