/**
 * main.cpp
 *
 * C++20 Concepts を活用したジェネリクスライブラリのデモ。
 *
 * static_assert でコンパイル時に型の制約を確認し、
 * 各アルゴリズムの動作を実際に出力して確かめる。
 */

#include "algorithms.hpp"
#include "concepts.hpp"
#include "sfinae_comparison.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// セクションの見出しを出力する
void print_section(const std::string& title)
{
    std::cout << "\n=== " << title << " ===\n";
}

// --- コンパイル時に型の制約を確認 ---

static_assert(Printable<int>);
static_assert(Printable<double>);
static_assert(Printable<std::string>);

static_assert(Sortable<int>);
static_assert(Sortable<double>);
static_assert(Sortable<std::string>);

static_assert(Addable<int>);
static_assert(Addable<double>);

static_assert(Numeric<int>);
static_assert(Numeric<double>);

// --- sort_if_sortable ---

void demo_sort()
{
    print_section("sort_if_sortable");

    std::vector<int> nums = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    std::cout << "Before: ";
    print_all(nums);

    auto sorted_nums = sort_if_sortable(nums);
    std::cout << "After:  ";
    print_all(sorted_nums);

    std::vector<std::string> words = {"banana", "apple", "cherry", "date"};
    std::cout << "Before: ";
    print_all(words);

    auto sorted_words = sort_if_sortable(words);
    std::cout << "After:  ";
    print_all(sorted_words);
}

// --- print_all ---

void demo_print()
{
    print_section("print_all");

    std::vector<int>    ints    = {1, 2, 3, 4, 5};
    std::vector<double> doubles = {1.1, 2.2, 3.3};
    std::vector<std::string> strs = {"hello", "world", "C++20"};

    std::cout << "ints:    ";
    print_all(ints);

    std::cout << "doubles: ";
    print_all(doubles, std::cout, ", ");

    std::cout << "strings: ";
    print_all(strs, std::cout, " | ");
}

// --- sum / max / min ---

void demo_aggregates()
{
    print_section("sum / max / min");

    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "nums:  ";
    print_all(nums);
    std::cout << "sum:   " << sum(nums) << '\n';
    std::cout << "max:   " << max_element_of(nums) << '\n';
    std::cout << "min:   " << min_element_of(nums) << '\n';

    std::vector<double> reals = {2.7, 1.4, 3.6, 0.5};
    std::cout << "reals: ";
    print_all(reals, std::cout, ", ");
    std::cout << "sum:   " << sum(reals) << '\n';
}

// --- filter_and_print（Ranges との組み合わせ） ---

void demo_ranges()
{
    print_section("filter_and_print (Ranges)");

    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "all:  ";
    print_all(nums);

    std::cout << "even: ";
    filter_and_print(nums, [](int n) { return n % 2 == 0; });

    std::cout << ">5:   ";
    filter_and_print(nums, [](int n) { return n > 5; });

    std::vector<std::string> words = {"apple", "banana", "cherry", "avocado", "blueberry"};
    std::cout << "starts 'a': ";
    filter_and_print(words, [](const std::string& s) {
        return !s.empty() && s[0] == 'a';
    }, std::cout, ", ");
}

// --- transform_and_collect ---

void demo_transform()
{
    print_section("transform_and_collect");

    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "original: ";
    print_all(nums);

    auto squares = transform_and_collect(nums, [](int n) { return n * n; });
    std::cout << "squares:  ";
    print_all(squares);

    auto roots = transform_and_collect(nums, [](int n) {
        return static_cast<double>(n) * 0.5;
    });
    std::cout << "halves:   ";
    print_all(roots, std::cout, ", ");

    std::vector<std::string> words = {"hi", "hello", "C++20 Concepts"};
    auto lengths = transform_and_collect(words, [](const std::string& s) {
        return static_cast<int>(s.size());
    });
    std::cout << "lengths:  ";
    print_all(lengths);
}

// --- clamp_all ---

void demo_clamp()
{
    print_section("clamp_all");

    std::vector<int> nums = {-5, 0, 3, 7, 10, 15};
    std::cout << "original:       ";
    print_all(nums);

    auto clamped = clamp_all(nums, 0, 10);
    std::cout << "clamped [0,10]: ";
    print_all(clamped);
}

// --- SFINAE 版との比較 ---

void demo_sfinae_comparison()
{
    print_section("SFINAE 版との比較");

    std::vector<int> nums = {5, 3, 8, 1, 9};

    std::cout << "[SFINAE] print_all:      ";
    sfinae::print_all(nums);

    auto sorted_sfinae = sfinae::sort_and_return(nums);
    std::cout << "[SFINAE] sort_and_return: ";
    sfinae::print_all(sorted_sfinae);

    std::cout << "[SFINAE] sum:            " << sfinae::sum(nums) << '\n';

    std::cout << "\n";
    std::cout << "Concepts 版: template <SortableContainer C> C sort_if_sortable(C)\n";
    std::cout << "SFINAE  版: template <typename C, typename = std::enable_if_t<...>> C sort(...)\n";
    std::cout << "\n";
    std::cout << "Concepts はエラー時に制約名が明示されるため、診断が格段に分かりやすい。\n";
}

int main()
{
    std::cout << "C++20 Concepts を活用したジェネリクスライブラリ デモ\n";
    std::cout << "======================================================\n";

    demo_sort();
    demo_print();
    demo_aggregates();
    demo_ranges();
    demo_transform();
    demo_clamp();
    demo_sfinae_comparison();

    std::cout << "\n全デモ完了\n";
    return 0;
}

