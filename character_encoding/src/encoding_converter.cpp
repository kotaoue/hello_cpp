#include "encoding_converter.h"

#include <iconv.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <vector>

bool convert_encoding(const std::string& input,
                      const std::string& from_encoding,
                      const std::string& to_encoding,
                      std::string& output)
{
    iconv_t cd = iconv_open(to_encoding.c_str(), from_encoding.c_str());
    if (cd == reinterpret_cast<iconv_t>(-1)) {
        return false;
    }

    // 出力バッファの初期サイズは入力の 4 倍（マルチバイト文字の最大膨張率を考慮）
    std::size_t out_buf_size = input.size() * 4 + 4;

    while (true) {
        // 入力バッファの設定（ループ毎にリセット）
        const char* in_buf = input.data();
        std::size_t in_bytes_left = input.size();

        std::vector<char> buf(out_buf_size);
        char* out_buf = buf.data();
        std::size_t out_bytes_left = out_buf_size;

        const std::size_t err = iconv(cd, const_cast<char**>(&in_buf), &in_bytes_left,
                                      &out_buf, &out_bytes_left);

        if (err == static_cast<std::size_t>(-1)) {
            if (errno == E2BIG) {
                // バッファが不足している場合はサイズを倍にして再試行する
                out_buf_size *= 2;
                iconv(cd, nullptr, nullptr, nullptr, nullptr); // 変換状態をリセット
                continue;
            }
            iconv_close(cd);
            return false;
        }

        iconv_close(cd);
        output.assign(buf.data(), out_buf_size - out_bytes_left);
        return true;
    }
}

