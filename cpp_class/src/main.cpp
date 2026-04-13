/**
 * main.cpp — C++ クラス機能のデモプログラム
 *
 * 実演する機能:
 *   - コンストラクタ / デストラクタ
 *   - 継承と仮想関数（ポリモーフィズム）
 *   - 純粋仮想関数 / 抽象クラス
 *   - static メンバー変数 / 関数
 *   - const メンバー関数
 *   - operator<< / operator[] / operator==
 *   - Rule of Five (コピー/ムーブ コンストラクタ / 代入演算子)
 *   - RAII パターン
 */

#include "buffer.hpp"
#include "shape.hpp"

#include <iostream>
#include <memory>
#include <vector>

// ── ヘルパー ──────────────────────────────────────────────────────

static void section(const std::string& title)
{
    std::cout << "\n=== " << title << " ===\n";
}

// ─────────────────────────────────────────────────────────────────
// デモ 1: コンストラクタ / デストラクタ / static メンバー
// ─────────────────────────────────────────────────────────────────

static void demo_constructor_destructor()
{
    section("コンストラクタ / デストラクタ / static メンバー");

    std::cout << "生成前のインスタンス数: " << Shape::instance_count() << '\n';

    {
        Circle    c(3.0);
        Rectangle r(4.0, 5.0);
        std::cout << "スコープ内のインスタンス数: " << Shape::instance_count() << '\n';
        std::cout << "  " << c << '\n';
        std::cout << "  " << r << '\n';
    }  // ← スコープを抜けるとデストラクタが自動的に呼ばれる

    std::cout << "スコープ後のインスタンス数: " << Shape::instance_count() << '\n';
}

// ─────────────────────────────────────────────────────────────────
// デモ 2: 継承と仮想関数（ポリモーフィズム）
// ─────────────────────────────────────────────────────────────────

static void demo_polymorphism()
{
    section("継承と仮想関数（ポリモーフィズム）");

    // 基底クラスのポインタで派生クラスを扱う
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));
    shapes.push_back(std::make_unique<Circle>(1.0));

    for (const auto& s : shapes) {
        // 実行時に適切な派生クラスの area()/perimeter() が呼ばれる
        std::cout << *s << '\n';
    }
}

// ─────────────────────────────────────────────────────────────────
// デモ 3: Rule of Five — コピーとムーブ
// ─────────────────────────────────────────────────────────────────

static void demo_rule_of_five()
{
    section("Rule of Five（Buffer クラス）");

    // (1) コンストラクタ — ヒープにメモリを確保
    Buffer b1(4);
    b1[0] = 10; b1[1] = 20; b1[2] = 30; b1[3] = 40;
    std::cout << "b1: size=" << b1.size()
              << "  [" << b1[0] << ", " << b1[1] << ", " << b1[2] << ", " << b1[3] << "]\n";

    // (2) コピーコンストラクタ — ディープコピー（独立した配列）
    Buffer b2(b1);
    b2[0] = 99;
    std::cout << "b2 (コピー後 b2[0]=99): b1[0]=" << b1[0]
              << "  b2[0]=" << b2[0] << "  (b1 は変わらない)\n";

    // (3) コピー代入演算子
    Buffer b3(2);
    b3 = b1;
    std::cout << "b3 (b1 をコピー代入): size=" << b3.size()
              << "  b3[0]=" << b3[0] << '\n';

    // (4) ムーブコンストラクタ — O(1) で所有権を移転
    Buffer b4(std::move(b1));
    std::cout << "b4 (b1 をムーブ): b4[0]=" << b4[0]
              << "  b1.empty()=" << std::boolalpha << b1.empty() << '\n';

    // (5) ムーブ代入演算子
    Buffer b5(1);
    b5 = std::move(b4);
    std::cout << "b5 (b4 をムーブ代入): b5[0]=" << b5[0]
              << "  b4.empty()=" << b4.empty() << '\n';

    // (6) 等値比較
    Buffer x(3), y(3);
    x[0] = 1; x[1] = 2; x[2] = 3;
    y[0] = 1; y[1] = 2; y[2] = 3;
    std::cout << "x == y: " << (x == y) << '\n';
    y[2] = 99;
    std::cout << "x != y (y[2]=99): " << (x != y) << '\n';
}

// ─────────────────────────────────────────────────────────────────
// デモ 4: RAII パターン
// ─────────────────────────────────────────────────────────────────

static void demo_raii()
{
    section("RAII パターン");

    std::cout << "スコープ開始 — Buffer が自動で確保される\n";
    {
        Buffer buf(1024);  // コンストラクタでメモリ確保
        buf[0] = 42;
        std::cout << "  buf[0]=" << buf[0] << "  size=" << buf.size() << '\n';
        // 例外が発生しても確実に解放される
    }  // ← デストラクタで自動解放
    std::cout << "スコープ終了 — Buffer が自動で解放された\n";
}

// ─────────────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────────────

int main()
{
    std::cout << "C++ クラス機能デモ\n";
    std::cout << "==================\n";

    demo_constructor_destructor();
    demo_polymorphism();
    demo_rule_of_five();
    demo_raii();

    std::cout << "\n全デモ完了\n";
    return 0;
}
