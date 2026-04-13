/**
 * test_class.cpp — Shape / Buffer クラスの Google Test テスト
 */

#include <gtest/gtest.h>

#include "buffer.hpp"
#include "shape.hpp"

#include <cmath>
#include <memory>
#include <sstream>

// ─────────────────────────────────────────────
// Circle
// ─────────────────────────────────────────────

TEST(Circle, 面積) {
    Circle c(5.0);
    EXPECT_DOUBLE_EQ(c.area(), M_PI * 25.0);
}

TEST(Circle, 周囲長) {
    Circle c(3.0);
    EXPECT_DOUBLE_EQ(c.perimeter(), 2.0 * M_PI * 3.0);
}

TEST(Circle, 名前) {
    Circle c(1.0);
    EXPECT_EQ(c.name(), "Circle");
}

TEST(Circle, 半径アクセサ) {
    Circle c(7.5);
    EXPECT_DOUBLE_EQ(c.radius(), 7.5);
}

TEST(Circle, describe出力) {
    Circle c(2.0);
    const std::string s = c.describe();
    EXPECT_NE(s.find("Circle"), std::string::npos);
    EXPECT_NE(s.find("r=2"), std::string::npos);
}

// ─────────────────────────────────────────────
// Rectangle
// ─────────────────────────────────────────────

TEST(Rectangle, 面積) {
    Rectangle r(4.0, 6.0);
    EXPECT_DOUBLE_EQ(r.area(), 24.0);
}

TEST(Rectangle, 周囲長) {
    Rectangle r(3.0, 4.0);
    EXPECT_DOUBLE_EQ(r.perimeter(), 14.0);
}

TEST(Rectangle, 名前) {
    Rectangle r(1.0, 2.0);
    EXPECT_EQ(r.name(), "Rectangle");
}

TEST(Rectangle, 幅と高さアクセサ) {
    Rectangle r(5.0, 8.0);
    EXPECT_DOUBLE_EQ(r.width(),  5.0);
    EXPECT_DOUBLE_EQ(r.height(), 8.0);
}

// ─────────────────────────────────────────────
// Shape — ポリモーフィズム
// ─────────────────────────────────────────────

TEST(Shape, ポリモーフィズム_Circle) {
    std::unique_ptr<Shape> s = std::make_unique<Circle>(2.0);
    EXPECT_NEAR(s->area(), M_PI * 4.0, 1e-9);
}

TEST(Shape, ポリモーフィズム_Rectangle) {
    std::unique_ptr<Shape> s = std::make_unique<Rectangle>(3.0, 5.0);
    EXPECT_DOUBLE_EQ(s->area(), 15.0);
}

TEST(Shape, operator_stream出力) {
    Circle c(1.0);
    std::ostringstream oss;
    oss << c;
    EXPECT_NE(oss.str().find("Circle"), std::string::npos);
}

TEST(Shape, staticインスタンス数) {
    const int before = Shape::instance_count();
    {
        Circle    c(1.0);
        Rectangle r(2.0, 3.0);
        EXPECT_EQ(Shape::instance_count(), before + 2);
    }
    EXPECT_EQ(Shape::instance_count(), before);
}

// ─────────────────────────────────────────────
// Buffer — Rule of Five
// ─────────────────────────────────────────────

TEST(Buffer, コンストラクタとサイズ) {
    Buffer b(5);
    EXPECT_EQ(b.size(), 5u);
    EXPECT_FALSE(b.empty());
}

TEST(Buffer, 空バッファ) {
    Buffer b(0);
    EXPECT_TRUE(b.empty());
}

TEST(Buffer, 要素アクセス) {
    Buffer b(3);
    b[0] = 10; b[1] = 20; b[2] = 30;
    EXPECT_EQ(b[0], 10);
    EXPECT_EQ(b[1], 20);
    EXPECT_EQ(b[2], 30);
}

TEST(Buffer, 範囲外アクセスで例外) {
    Buffer b(3);
    EXPECT_THROW(b[3], std::out_of_range);
}

TEST(Buffer, コピーコンストラクタはディープコピー) {
    Buffer b1(3);
    b1[0] = 1; b1[1] = 2; b1[2] = 3;

    Buffer b2(b1);
    EXPECT_EQ(b2[0], 1);

    b2[0] = 99;              // b2 を変更しても
    EXPECT_EQ(b1[0], 1);     // b1 は変わらない
}

TEST(Buffer, コピー代入演算子) {
    Buffer b1(2);
    b1[0] = 10; b1[1] = 20;

    Buffer b2(1);
    b2 = b1;

    EXPECT_EQ(b2.size(), 2u);
    EXPECT_EQ(b2[0], 10);
    EXPECT_EQ(b2[1], 20);
}

TEST(Buffer, 自己代入は安全) {
    Buffer b(2);
    b[0] = 5; b[1] = 6;
    b = b;  // 自己代入
    EXPECT_EQ(b[0], 5);
    EXPECT_EQ(b[1], 6);
}

TEST(Buffer, ムーブコンストラクタ) {
    Buffer b1(3);
    b1[0] = 42;

    Buffer b2(std::move(b1));

    EXPECT_EQ(b2[0], 42);
    EXPECT_TRUE(b1.empty());  // 移転元は空になる
}

TEST(Buffer, ムーブ代入演算子) {
    Buffer b1(3);
    b1[0] = 7;

    Buffer b2(1);
    b2 = std::move(b1);

    EXPECT_EQ(b2[0], 7);
    EXPECT_TRUE(b1.empty());
}

TEST(Buffer, 等値比較) {
    Buffer b1(3), b2(3);
    b1[0] = 1; b1[1] = 2; b1[2] = 3;
    b2[0] = 1; b2[1] = 2; b2[2] = 3;

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);

    b2[2] = 99;
    EXPECT_FALSE(b1 == b2);
    EXPECT_TRUE(b1 != b2);
}

TEST(Buffer, サイズ違いは不等) {
    Buffer b1(2), b2(3);
    EXPECT_FALSE(b1 == b2);
}
