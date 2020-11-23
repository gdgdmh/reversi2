#ifndef MHL_BIT_BIT_CONTROL_UINT32_HPP_
#define MHL_BIT_BIT_CONTROL_UINT32_HPP_

#include <cstdint>

namespace mhl {

// ビット操作
class BitControlUint32 {
 public:
  /**
   * @brief デフォルトコンストラクタ
   *
   */
  BitControlUint32();

  /**
   * @brief コンストラクタ
   *
   * @param value 初期化値
   */
  BitControlUint32(uint32_t value);

  /**
   * @brief デストラクタ
   *
   */
  virtual ~BitControlUint32();

  /**
   * @brief 値の設定
   *
   * @param value 設定する値
   */
  void Set(uint32_t value);

  /**
   * @brief 指定ビットをONにする
   *
   * @param bit 指定ビット
   */
  void BitOn(uint32_t bit);

  /**
   * @brief 指定ビットをOFFにする
   *
   * @param bit 指定ビット
   */
  void BitOff(uint32_t bit);

  /**
   * @brief ビットの切り替え
   * 指定ビットがONならOFFに切り替える
   * 指定ビットがOFFならONに切り替える
   *
   * @param bit 指定ビット
   */
  void BitToggle(uint32_t bit);

  /**
   * @brief 値の取得
   *
   * @return uint32_t 値
   */
  uint32_t Get() const;

  /**
   * @brief ビットの取得
   *
   * @param bit 何ビット目を取得するか
   * @return true 指定のビットが立っている
   * @return false 指定のビットが立っていない
   */
  bool GetBit(uint32_t bit) const;

 private:
  uint32_t value_;
};

}  // namespace mhl

#endif  // MHL_BIT_BIT_CONTROL_UINT32_HPP_
