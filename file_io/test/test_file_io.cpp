/**
 * test_file_io.cpp
 *
 * Google Test を使ったテキストファイル読み書きのユニットテストサンプル。
 *
 * テスト実行前に一時ファイルを作成し、テスト後に削除する。
 */

#include <gtest/gtest.h>
#include <cstdio>
#include <string>
#include "file_io.h"

// テスト用一時ファイルパス
static const std::string kTestFile = "test_file_io_tmp.txt";

// 各テスト後に一時ファイルを削除する
class FileIoTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::remove(kTestFile.c_str());
    }
};

// --- 書き込みテスト ---

TEST_F(FileIoTest, WritesStringToFile) {
    EXPECT_TRUE(write_text_file(kTestFile, "Hello, World!"));
}

TEST_F(FileIoTest, WritesEmptyString) {
    EXPECT_TRUE(write_text_file(kTestFile, ""));
}

TEST_F(FileIoTest, FailsWhenWritingToInvalidPath) {
    EXPECT_FALSE(write_text_file("/invalid_dir/no_such_file.txt", "data"));
}

// --- 読み込みテスト ---

TEST_F(FileIoTest, ReadsWrittenContentCorrectly) {
    const std::string expected = "Hello, File IO!";
    ASSERT_TRUE(write_text_file(kTestFile, expected));

    std::string actual;
    ASSERT_TRUE(read_text_file(kTestFile, actual));
    EXPECT_EQ(expected, actual);
}

TEST_F(FileIoTest, HandlesMultiLineText) {
    const std::string expected = "line1\nline2\nline3\n";
    ASSERT_TRUE(write_text_file(kTestFile, expected));

    std::string actual;
    ASSERT_TRUE(read_text_file(kTestFile, actual));
    EXPECT_EQ(expected, actual);
}

TEST_F(FileIoTest, ReadsEmptyFileAsEmptyString) {
    ASSERT_TRUE(write_text_file(kTestFile, ""));

    std::string actual;
    ASSERT_TRUE(read_text_file(kTestFile, actual));
    EXPECT_EQ("", actual);
}

TEST_F(FileIoTest, FailsWhenReadingNonexistentFile) {
    std::string content;
    EXPECT_FALSE(read_text_file("nonexistent_file.txt", content));
}

// --- 上書きテスト ---

TEST_F(FileIoTest, OverwritesFileOnSecondWrite) {
    ASSERT_TRUE(write_text_file(kTestFile, "first"));
    ASSERT_TRUE(write_text_file(kTestFile, "second"));

    std::string actual;
    ASSERT_TRUE(read_text_file(kTestFile, actual));
    EXPECT_EQ("second", actual);
}
