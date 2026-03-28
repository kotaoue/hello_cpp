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

// --- Addition ---

TEST(CalculatorAdd, PositiveNumbers) {
    EXPECT_EQ(5, calculator_add(2, 3));
}

TEST(CalculatorAdd, NegativeNumber) {
    EXPECT_EQ(-1, calculator_add(-3, 2));
}

TEST(CalculatorAdd, Zero) {
    EXPECT_EQ(0, calculator_add(0, 0));
}

// --- Subtraction ---

TEST(CalculatorSubtract, PositiveResult) {
    EXPECT_EQ(1, calculator_subtract(3, 2));
}

TEST(CalculatorSubtract, NegativeResult) {
    EXPECT_EQ(-5, calculator_subtract(0, 5));
}

// --- Multiplication ---

TEST(CalculatorMultiply, PositiveNumbers) {
    EXPECT_EQ(6, calculator_multiply(2, 3));
}

TEST(CalculatorMultiply, MultiplyByZero) {
    EXPECT_EQ(0, calculator_multiply(100, 0));
}
