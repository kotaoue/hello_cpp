/**
 * test_encoding_converter.cpp
 *
 * Google Test を使った文字コード変換のユニットテストサンプル。
 *
 * テスト対象: UTF-8, Shift-JIS, EUC-JP 間の相互変換
 */

#include <gtest/gtest.h>
#include <string>
#include "encoding_converter.h"

// --- UTF-8 → Shift-JIS 変換テスト ---

// "日本語" の UTF-8 バイト列: E6 97 A5 E6 9C AC E8 AA 9E
static const std::string kNihongo_UTF8 =
    "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";

// "日本語" の Shift-JIS バイト列: 93 FA 96 7B 8C EA
static const std::string kNihongo_ShiftJIS =
    "\x93\xfa\x96\x7b\x8c\xea";

// "日本語" の EUC-JP バイト列: C6 FC CB DC B8 EC
static const std::string kNihongo_EUCJP =
    "\xc6\xfc\xcb\xdc\xb8\xec";

// --- 同一エンコーディング変換（恒等変換）テスト ---

TEST(EncodingConverter, UTF8ToUTF8ReturnsInput) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_UTF8, "UTF-8", "UTF-8", output));
    EXPECT_EQ(kNihongo_UTF8, output);
}

TEST(EncodingConverter, ShiftJISToShiftJISReturnsInput) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_ShiftJIS, "Shift-JIS", "Shift-JIS", output));
    EXPECT_EQ(kNihongo_ShiftJIS, output);
}

// --- UTF-8 → Shift-JIS 変換テスト ---

TEST(EncodingConverter, UTF8ToShiftJIS) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_UTF8, "UTF-8", "Shift-JIS", output));
    EXPECT_EQ(kNihongo_ShiftJIS, output);
}

TEST(EncodingConverter, ShiftJISToUTF8) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_ShiftJIS, "Shift-JIS", "UTF-8", output));
    EXPECT_EQ(kNihongo_UTF8, output);
}

// --- UTF-8 → EUC-JP 変換テスト ---

TEST(EncodingConverter, UTF8ToEUCJP) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_UTF8, "UTF-8", "EUC-JP", output));
    EXPECT_EQ(kNihongo_EUCJP, output);
}

TEST(EncodingConverter, EUCJPToUTF8) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_EUCJP, "EUC-JP", "UTF-8", output));
    EXPECT_EQ(kNihongo_UTF8, output);
}

// --- Shift-JIS ↔ EUC-JP 変換テスト ---

TEST(EncodingConverter, ShiftJISToEUCJP) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_ShiftJIS, "Shift-JIS", "EUC-JP", output));
    EXPECT_EQ(kNihongo_EUCJP, output);
}

TEST(EncodingConverter, EUCJPToShiftJIS) {
    std::string output;
    ASSERT_TRUE(convert_encoding(kNihongo_EUCJP, "EUC-JP", "Shift-JIS", output));
    EXPECT_EQ(kNihongo_ShiftJIS, output);
}

// --- ASCII 文字の変換テスト ---

TEST(EncodingConverter, AsciiStringUTF8ToShiftJIS) {
    const std::string ascii = "Hello, World!";
    std::string output;
    ASSERT_TRUE(convert_encoding(ascii, "UTF-8", "Shift-JIS", output));
    EXPECT_EQ(ascii, output);
}

// --- 空文字列の変換テスト ---

TEST(EncodingConverter, EmptyStringUTF8ToShiftJIS) {
    std::string output;
    ASSERT_TRUE(convert_encoding("", "UTF-8", "Shift-JIS", output));
    EXPECT_EQ("", output);
}

// --- エラーハンドリングテスト ---

TEST(EncodingConverter, InvalidEncodingNameReturnsFalse) {
    std::string output;
    EXPECT_FALSE(convert_encoding(kNihongo_UTF8, "UTF-8", "NO-SUCH-ENCODING", output));
}

TEST(EncodingConverter, InvalidInputBytesReturnsFalse) {
    // UTF-8 として不正なバイト列（Shift-JIS のバイト列を UTF-8 として変換しようとする）
    std::string output;
    EXPECT_FALSE(convert_encoding(kNihongo_ShiftJIS, "UTF-8", "Shift-JIS", output));
}
