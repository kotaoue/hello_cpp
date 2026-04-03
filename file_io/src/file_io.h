#pragma once

#include <string>

// テキストファイルにコンテンツを書き込む
// path    : 書き込み先のファイルパス
// content : 書き込む文字列
// 戻り値  : 成功した場合 true、失敗した場合 false
bool write_text_file(const std::string& path, const std::string& content);

// テキストファイルからコンテンツを読み込む
// path    : 読み込み元のファイルパス
// content : 読み込んだ文字列を格納する変数（出力引数）
// 戻り値  : 成功した場合 true、失敗した場合 false
bool read_text_file(const std::string& path, std::string& content);
