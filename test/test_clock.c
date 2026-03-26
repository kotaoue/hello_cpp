/**
 * test_clock.c
 *
 * CMock を使ったモックテストのサンプル。
 *
 * clock_get_greeting() は内部で time_provider_get_time() を呼ぶ。
 * CMock で生成したモック (mock_time_provider) を使い、
 * 「現在時刻」を自由に差し替えてテストする。
 *
 * モックを使うことで:
 *   - 実際の時刻に依存せずテストが書ける
 *   - 深夜や朝など、あらゆる時間帯を再現できる
 */

#include "unity.h"
#include "mock_time_provider.h"  /* CMock が生成したモック */
#include "clock.h"
#include <time.h>

/* --- setUp / tearDown --- */

void setUp(void)
{
    /* 各テストの前にモックを初期化する */
    mock_time_provider_Init();
}

void tearDown(void)
{
    /* 各テストの後に期待した呼び出しが全て行われたか検証する */
    mock_time_provider_Verify();
    mock_time_provider_Destroy();
}

/* --- ヘルパー: 指定した時・分・秒の time_t を作る --- */

static time_t make_time(int hour, int min, int sec)
{
    struct tm t = {0};
    t.tm_year = 124; /* 2024 年 */
    t.tm_mon  = 0;   /* 1 月 */
    t.tm_mday = 1;
    t.tm_hour = hour;
    t.tm_min  = min;
    t.tm_sec  = sec;
    t.tm_isdst = -1;
    return mktime(&t);
}

/* --- テストケース --- */

void test_clock_朝は_Good_morning(void)
{
    /* 午前 8 時を返すようにモック設定 */
    time_provider_get_time_ExpectAndReturn(make_time(8, 0, 0));

    TEST_ASSERT_EQUAL_STRING("Good morning", clock_get_greeting());
}

void test_clock_昼は_Good_afternoon(void)
{
    /* 午後 2 時 (14:00) を返すようにモック設定 */
    time_provider_get_time_ExpectAndReturn(make_time(14, 0, 0));

    TEST_ASSERT_EQUAL_STRING("Good afternoon", clock_get_greeting());
}

void test_clock_夜は_Good_evening(void)
{
    /* 午後 9 時 (21:00) を返すようにモック設定 */
    time_provider_get_time_ExpectAndReturn(make_time(21, 0, 0));

    TEST_ASSERT_EQUAL_STRING("Good evening", clock_get_greeting());
}

void test_clock_深夜0時は_Good_morning(void)
{
    /* 0 時 (0:00) → 朝 */
    time_provider_get_time_ExpectAndReturn(make_time(0, 0, 0));

    TEST_ASSERT_EQUAL_STRING("Good morning", clock_get_greeting());
}

void test_clock_11時59分は_Good_morning(void)
{
    /* 11:59 → まだ朝 */
    time_provider_get_time_ExpectAndReturn(make_time(11, 59, 59));

    TEST_ASSERT_EQUAL_STRING("Good morning", clock_get_greeting());
}

void test_clock_12時ちょうどは_Good_afternoon(void)
{
    /* 12:00 ちょうど → 午後 */
    time_provider_get_time_ExpectAndReturn(make_time(12, 0, 0));

    TEST_ASSERT_EQUAL_STRING("Good afternoon", clock_get_greeting());
}

void test_clock_17時59分は_Good_afternoon(void)
{
    /* 17:59 → まだ午後 */
    time_provider_get_time_ExpectAndReturn(make_time(17, 59, 59));

    TEST_ASSERT_EQUAL_STRING("Good afternoon", clock_get_greeting());
}

void test_clock_18時ちょうどは_Good_evening(void)
{
    /* 18:00 ちょうど → 夜 */
    time_provider_get_time_ExpectAndReturn(make_time(18, 0, 0));

    TEST_ASSERT_EQUAL_STRING("Good evening", clock_get_greeting());
}

/* --- エントリポイント --- */

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_clock_朝は_Good_morning);
    RUN_TEST(test_clock_昼は_Good_afternoon);
    RUN_TEST(test_clock_夜は_Good_evening);
    RUN_TEST(test_clock_深夜0時は_Good_morning);
    RUN_TEST(test_clock_11時59分は_Good_morning);
    RUN_TEST(test_clock_12時ちょうどは_Good_afternoon);
    RUN_TEST(test_clock_17時59分は_Good_afternoon);
    RUN_TEST(test_clock_18時ちょうどは_Good_evening);

    return UNITY_END();
}
