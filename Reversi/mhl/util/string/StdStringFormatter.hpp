#ifndef MHL_UTIL_STRING_STDSTRINGFORMATTER_HPP_
#define MHL_UTIL_STRING_STDSTRINGFORMATTER_HPP_

#include <string>
#include <vector>

namespace mhl {

// コンソール出力のインターフェースクラス
class StdStringFormatter {
 public:
  /**
   * 指定された形式に基づいて文字列に変換し、別の文字列に挿入する
   * @param  fmt  フォーマット文字列
   * @param  args パラメータ
   * @return      整形された文字列
   */
  template <typename... Args>
  static std::string Format(const std::string& fmt, Args... args) {
    size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args...);
    std::vector<char> buf(len + 1);
    std::snprintf(&buf[0], len + 1, fmt.c_str(), args...);
    return std::string(&buf[0], &buf[0] + len);
  }
};

}  // namespace mhl

#endif  // MH_LIBRARY_UTIL_STRING_STDSTRINGFORMATTER_HPP_
