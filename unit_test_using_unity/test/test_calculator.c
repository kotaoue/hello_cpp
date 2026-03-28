#include "unity.h"
#include "calculator.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_add_positive_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(5, add(2, 3));
}

void test_add_negative_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(-5, add(-2, -3));
}

void test_add_zero(void)
{
    TEST_ASSERT_EQUAL_INT(0, add(0, 0));
}

void test_subtract(void)
{
    TEST_ASSERT_EQUAL_INT(1, subtract(3, 2));
}

void test_subtract_negative_result(void)
{
    TEST_ASSERT_EQUAL_INT(-1, subtract(2, 3));
}

void test_multiply(void)
{
    TEST_ASSERT_EQUAL_INT(6, multiply(2, 3));
}

void test_multiply_by_zero(void)
{
    TEST_ASSERT_EQUAL_INT(0, multiply(5, 0));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_add_positive_numbers);
    RUN_TEST(test_add_negative_numbers);
    RUN_TEST(test_add_zero);
    RUN_TEST(test_subtract);
    RUN_TEST(test_subtract_negative_result);
    RUN_TEST(test_multiply);
    RUN_TEST(test_multiply_by_zero);

    return UNITY_END();
}
