/**
 * test_calculator.cpp
 *
 * Google Test を使ったシンプルなユニットテストのサンプル。
 *
 * TEST(テストスイート名, テスト名) マクロでテストケースを定義する。
 * EXPECT_EQ / EXPECT_NE などで期待値と実際値を比較する。
 */

#include <gtest/gtest.h>
#include "calculator.h"

// --- 足し算 ---

TEST(CalculatorAdd, 正の数同士) {
    EXPECT_EQ(5, calculator_add(2, 3));
}

TEST(CalculatorAdd, 負の数) {
    EXPECT_EQ(-1, calculator_add(-3, 2));
}

TEST(CalculatorAdd, ゼロ) {
    EXPECT_EQ(0, calculator_add(0, 0));
}

// --- 引き算 ---

TEST(CalculatorSubtract, 正の結果) {
    EXPECT_EQ(1, calculator_subtract(3, 2));
}

TEST(CalculatorSubtract, 負の結果) {
    EXPECT_EQ(-5, calculator_subtract(0, 5));
}

// --- 掛け算 ---

TEST(CalculatorMultiply, 正の数同士) {
    EXPECT_EQ(6, calculator_multiply(2, 3));
}

TEST(CalculatorMultiply, ゼロとの積) {
    EXPECT_EQ(0, calculator_multiply(100, 0));
}
