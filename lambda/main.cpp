/**
 * main.cpp
 *
 * C++ ラムダ式のサンプル集。
 *
 * 基本構文・キャプチャ・可変ラムダ・再帰ラムダ・ジェネリックラムダ（C++14）
 * ・即時実行・高階関数への渡し方など、よく使うパターンを網羅する。
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// セクションの見出しを出力する
void print_section(const std::string& title)
{
    std::cout << "\n=== " << title << " ===\n";
}

// --- 1. 基本的なラムダ式 ---

void demo_basic()
{
    print_section("基本的なラムダ式");

    // 引数なし・戻り値なし
    auto greet = []() {
        std::cout << "Hello from lambda!\n";
    };
    greet();

    // 引数あり・戻り値あり（型推論）
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "add(3, 4) = " << add(3, 4) << '\n';

    // 戻り値の型を明示する
    auto divide = [](double a, double b) -> double {
        return a / b;
    };
    std::cout << "divide(7.0, 2.0) = " << divide(7.0, 2.0) << '\n';
}

// --- 2. キャプチャ ---

void demo_capture()
{
    print_section("キャプチャ");

    int  x = 10;
    int  y = 20;

    // 値キャプチャ（コピー）
    auto by_value = [x, y]() {
        std::cout << "by value: x=" << x << ", y=" << y << '\n';
    };
    x = 99;   // ラムダ外で変更しても影響しない
    by_value();

    // 参照キャプチャ
    int counter = 0;
    auto increment = [&counter]() {
        ++counter;
    };
    increment();
    increment();
    std::cout << "counter after 2 increments: " << counter << '\n';

    // デフォルト値キャプチャ [=]（全変数をコピー）
    int a = 1, b = 2, c = 3;
    auto sum_abc = [=]() { return a + b + c; };
    std::cout << "sum(1,2,3) = " << sum_abc() << '\n';

    // デフォルト参照キャプチャ [&]（全変数を参照）
    int total = 0;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::for_each(nums.begin(), nums.end(), [&](int n) {
        total += n;
    });
    std::cout << "total = " << total << '\n';
}

// --- 3. mutable ラムダ ---

void demo_mutable()
{
    print_section("mutable ラムダ");

    int count = 0;

    // 値キャプチャの変数をラムダ内で変更するには mutable が必要
    auto inc = [count]() mutable {
        ++count;
        std::cout << "inside lambda: count=" << count << '\n';
    };

    inc();
    inc();
    std::cout << "outside lambda: count=" << count << '\n';   // 変化しない
}

// --- 4. std::function に格納する ---

void demo_std_function()
{
    print_section("std::function に格納");

    std::function<int(int, int)> op;

    op = [](int a, int b) { return a + b; };
    std::cout << "add: " << op(3, 5) << '\n';

    op = [](int a, int b) { return a * b; };
    std::cout << "mul: " << op(3, 5) << '\n';
}

// --- 5. 高階関数への渡し方（STL アルゴリズム） ---

void demo_stl_algorithms()
{
    print_section("STL アルゴリズムとの組み合わせ");

    std::vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};

    // std::sort — 降順
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    std::cout << "sorted (desc): ";
    for (int n : v) { std::cout << n << ' '; }
    std::cout << '\n';

    // std::find_if — 最初の偶数
    auto it = std::find_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
    if (it != v.end()) {
        std::cout << "first even: " << *it << '\n';
    }

    // std::transform — 2 乗
    std::vector<int> squares(v.size());
    std::transform(v.begin(), v.end(), squares.begin(), [](int n) { return n * n; });
    std::cout << "squares: ";
    for (int n : squares) { std::cout << n << ' '; }
    std::cout << '\n';

    // std::accumulate — 合計
    int total = std::accumulate(v.begin(), v.end(), 0, [](int acc, int n) {
        return acc + n;
    });
    std::cout << "total = " << total << '\n';
}

// --- 6. ジェネリックラムダ（C++14） ---

void demo_generic_lambda()
{
    print_section("ジェネリックラムダ (C++14)");

    auto print = [](const auto& val) {
        std::cout << val << '\n';
    };
    print(42);
    print(3.14);
    print(std::string("hello"));

    auto max_of = [](auto a, auto b) {
        return (a > b) ? a : b;
    };
    std::cout << "max(3, 7)       = " << max_of(3, 7) << '\n';
    std::cout << "max(1.5, 0.8)   = " << max_of(1.5, 0.8) << '\n';
}

// --- 7. 即時実行ラムダ（IIFE） ---

void demo_iife()
{
    print_section("即時実行ラムダ (IIFE)");

    // 定義と同時に呼び出す
    int result = [](int n) { return n * n; }(7);
    std::cout << "7^2 = " << result << '\n';

    // 初期化ブロックとして利用
    const std::string message = []{
        std::string s = "Hello";
        s += ", ";
        s += "World!";
        return s;
    }();
    std::cout << message << '\n';
}

// --- 8. ラムダを返す関数（クロージャファクトリ） ---

std::function<int(int)> make_adder(int offset)
{
    return [offset](int n) { return n + offset; };
}

void demo_closure_factory()
{
    print_section("クロージャファクトリ");

    auto add10 = make_adder(10);
    auto add100 = make_adder(100);

    std::cout << "add10(5)  = " << add10(5)  << '\n';
    std::cout << "add100(5) = " << add100(5) << '\n';
}

// --- 9. 再帰ラムダ ---

void demo_recursive_lambda()
{
    print_section("再帰ラムダ");

    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    };

    for (int i = 0; i <= 7; ++i) {
        std::cout << i << "! = " << factorial(i) << '\n';
    }
}

// ---------------------------------------------------------------------------

int main()
{
    std::cout << "C++ ラムダ式 サンプル集\n";
    std::cout << "========================\n";

    demo_basic();
    demo_capture();
    demo_mutable();
    demo_std_function();
    demo_stl_algorithms();
    demo_generic_lambda();
    demo_iife();
    demo_closure_factory();
    demo_recursive_lambda();

    std::cout << "\n全デモ完了\n";
    return 0;
}
