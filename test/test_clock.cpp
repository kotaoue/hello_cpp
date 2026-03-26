/**
 * test_clock.cpp
 *
 * Google Mock を使って ITimeProvider をモックし、
 * Clock::greeting() を現在時刻に依存せずテストするサンプル。
 *
 * Google Mock を使うことで:
 *   - 実際の時刻に依存せずテストが書ける
 *   - 朝・昼・夜など任意の時間帯を再現できる
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Clock.h"
#include "ITimeProvider.h"
#include <ctime>

// --- モッククラスの定義 ---
//
// MOCK_METHOD マクロで ITimeProvider::now() のモックを自動生成する。
// 通常はこれを .h に切り出すが、最小サンプルとして .cpp 内にまとめている。
class MockTimeProvider : public ITimeProvider {
public:
    MOCK_METHOD(std::time_t, now, (), (const, override));
};

// --- ヘルパー: 指定した時・分のローカル time_t を作る ---

static std::time_t make_time(int hour, int min) {
    std::tm t{};
    t.tm_year  = 124;  // 2024 年
    t.tm_mon   = 0;    // 1 月
    t.tm_mday  = 1;
    t.tm_hour  = hour;
    t.tm_min   = min;
    t.tm_sec   = 0;
    t.tm_isdst = -1;
    return std::mktime(&t);
}

// --- テストスイート ---

using ::testing::Return;

TEST(ClockGreeting, 朝は_GoodMorning) {
    MockTimeProvider mock;
    // now() が午前 8 時を返すよう期待を設定
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(8, 0)));

    Clock clock(mock);
    EXPECT_EQ("Good morning", clock.greeting());
}

TEST(ClockGreeting, 昼は_GoodAfternoon) {
    MockTimeProvider mock;
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(14, 0)));

    Clock clock(mock);
    EXPECT_EQ("Good afternoon", clock.greeting());
}

TEST(ClockGreeting, 夜は_GoodEvening) {
    MockTimeProvider mock;
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(21, 0)));

    Clock clock(mock);
    EXPECT_EQ("Good evening", clock.greeting());
}

TEST(ClockGreeting, 深夜0時は_GoodMorning) {
    MockTimeProvider mock;
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(0, 0)));

    Clock clock(mock);
    EXPECT_EQ("Good morning", clock.greeting());
}

TEST(ClockGreeting, 11時59分は_GoodMorning) {
    MockTimeProvider mock;
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(11, 59)));

    Clock clock(mock);
    EXPECT_EQ("Good morning", clock.greeting());
}

TEST(ClockGreeting, 12時ちょうどは_GoodAfternoon) {
    MockTimeProvider mock;
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(12, 0)));

    Clock clock(mock);
    EXPECT_EQ("Good afternoon", clock.greeting());
}

TEST(ClockGreeting, 17時59分は_GoodAfternoon) {
    MockTimeProvider mock;
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(17, 59)));

    Clock clock(mock);
    EXPECT_EQ("Good afternoon", clock.greeting());
}

TEST(ClockGreeting, 18時ちょうどは_GoodEvening) {
    MockTimeProvider mock;
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(18, 0)));

    Clock clock(mock);
    EXPECT_EQ("Good evening", clock.greeting());
}
