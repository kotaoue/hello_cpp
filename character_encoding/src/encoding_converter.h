#pragma once

#include <string>

// 文字コードを変換する
// input         : 変換元の文字列（バイト列）
// from_encoding : 変換元の文字コード（例: "UTF-8", "Shift-JIS", "EUC-JP"）
// to_encoding   : 変換先の文字コード（例: "UTF-8", "Shift-JIS", "EUC-JP"）
// output        : 変換後の文字列を格納する変数（出力引数）
// 戻り値        : 変換に成功した場合 true、失敗した場合 false
bool convert_encoding(const std::string& input,
                      const std::string& from_encoding,
                      const std::string& to_encoding,
                      std::string& output);
