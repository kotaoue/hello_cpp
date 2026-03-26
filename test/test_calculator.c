/**
 * test_calculator.c
 *
 * Unity を使ったシンプルなユニットテストのサンプル。
 *
 * Unity は ThrowTheSwitch 製の軽量 C 用テストフレームワーク。
 * TEST_ASSERT_EQUAL_INT などのマクロで期待値と実際値を比較する。
 */

#include "unity.h"
#include "calculator.h"

/* --- setUp / tearDown --- */
/* 各テストの前後に自動で呼ばれる。初期化・後処理に使う。 */

void setUp(void)
{
    /* 今回はとくに初期化なし */
}

void tearDown(void)
{
    /* 今回はとくに後処理なし */
}

/* --- テストケース --- */

void test_calculator_add_正の数(void)
{
    TEST_ASSERT_EQUAL_INT(5, calculator_add(2, 3));
}

void test_calculator_add_負の数(void)
{
    TEST_ASSERT_EQUAL_INT(-1, calculator_add(-3, 2));
}

void test_calculator_add_ゼロ(void)
{
    TEST_ASSERT_EQUAL_INT(0, calculator_add(0, 0));
}

void test_calculator_subtract_正の数(void)
{
    TEST_ASSERT_EQUAL_INT(1, calculator_subtract(3, 2));
}

void test_calculator_subtract_負の結果(void)
{
    TEST_ASSERT_EQUAL_INT(-5, calculator_subtract(0, 5));
}

void test_calculator_multiply_正の数(void)
{
    TEST_ASSERT_EQUAL_INT(6, calculator_multiply(2, 3));
}

void test_calculator_multiply_ゼロとの積(void)
{
    TEST_ASSERT_EQUAL_INT(0, calculator_multiply(100, 0));
}

/* --- エントリポイント --- */

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_calculator_add_正の数);
    RUN_TEST(test_calculator_add_負の数);
    RUN_TEST(test_calculator_add_ゼロ);
    RUN_TEST(test_calculator_subtract_正の数);
    RUN_TEST(test_calculator_subtract_負の結果);
    RUN_TEST(test_calculator_multiply_正の数);
    RUN_TEST(test_calculator_multiply_ゼロとの積);

    return UNITY_END();
}
