#include "algorithms.hpp"
#include "concepts.hpp"
#include "sfinae_comparison.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// ============================================================
// ヘルパー関数
// ============================================================

// セクションの見出しを出力する
void print_section(const std::string& title)
{
    std::cout << "\n=== " << title << " ===\n";
}

// ============================================================
// Concept 定義の確認（static_assert）
//
// static_assert は条件を コンパイル時 に検査するため、
// 型が制約を満たすかどうかをドキュメントとして明示できる。
// ============================================================
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

// ============================================================
// デモ 1: sort_if_sortable
// ============================================================
void demo_sort()
{
    print_section("sort_if_sortable");

    // int の vector をソート
    std::vector<int> nums = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    std::cout << "Before: ";
    print_all(nums);

    auto sorted_nums = sort_if_sortable(nums);
    std::cout << "After:  ";
    print_all(sorted_nums);

    // string の vector もソート可能
    std::vector<std::string> words = {"banana", "apple", "cherry", "date"};
    std::cout << "Before: ";
    print_all(words);

    auto sorted_words = sort_if_sortable(words);
    std::cout << "After:  ";
    print_all(sorted_words);

    // コンパイルエラーになる例（コメントアウト）:
    //   struct NoCompare {};
    //   std::vector<NoCompare> v = {NoCompare{}};
    //   sort_if_sortable(v);  // エラー: SortableContainer 制約不成立
}

// ============================================================
// デモ 2: print_all
// ============================================================
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

// ============================================================
// デモ 3: sum / max_element_of / min_element_of
// ============================================================
void demo_aggregates()
{
    print_section("sum / max / min");

    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "nums:    ";
    print_all(nums);
    std::cout << "sum:     " << sum(nums) << '\n';
    std::cout << "max:     " << max_element_of(nums) << '\n';
    std::cout << "min:     " << min_element_of(nums) << '\n';

    std::vector<double> reals = {2.7, 1.4, 3.6, 0.5};
    std::cout << "reals:   ";
    print_all(reals, std::cout, ", ");
    std::cout << "sum:     " << sum(reals) << '\n';
}

// ============================================================
// デモ 4: filter_and_print（Ranges との組み合わせ）
// ============================================================
void demo_ranges()
{
    print_section("filter_and_print (Ranges)");

    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "all:    ";
    print_all(nums);

    std::cout << "even:   ";
    filter_and_print(nums, [](int n) { return n % 2 == 0; });

    std::cout << ">5:     ";
    filter_and_print(nums, [](int n) { return n > 5; });

    std::vector<std::string> words = {"apple", "banana", "cherry", "avocado", "blueberry"};
    std::cout << "starts 'a': ";
    filter_and_print(words, [](const std::string& s) {
        return !s.empty() && s[0] == 'a';
    }, std::cout, ", ");
}

// ============================================================
// デモ 5: transform_and_collect
// ============================================================
void demo_transform()
{
    print_section("transform_and_collect");

    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "original: ";
    print_all(nums);

    // int -> int: 2 乗
    auto squares = transform_and_collect(nums, [](int n) { return n * n; });
    std::cout << "squares:  ";
    print_all(squares);

    // int -> double: 平方根
    auto roots = transform_and_collect(nums, [](int n) {
        return static_cast<double>(n) * 0.5;
    });
    std::cout << "halves:   ";
    print_all(roots, std::cout, ", ");

    // string -> int: 文字数
    std::vector<std::string> words = {"hi", "hello", "C++20 Concepts"};
    auto lengths = transform_and_collect(words, [](const std::string& s) {
        return static_cast<int>(s.size());
    });
    std::cout << "lengths:  ";
    print_all(lengths);
}

// ============================================================
// デモ 6: clamp_all
// ============================================================
void demo_clamp()
{
    print_section("clamp_all");

    std::vector<int> nums = {-5, 0, 3, 7, 10, 15};
    std::cout << "original: ";
    print_all(nums);

    auto clamped = clamp_all(nums, 0, 10);
    std::cout << "clamped [0,10]: ";
    print_all(clamped);
}

// ============================================================
// デモ 7: SFINAE 版との比較
// ============================================================
void demo_sfinae_comparison()
{
    print_section("SFINAE 版との比較");

    std::vector<int> nums = {5, 3, 8, 1, 9};
    std::vector<std::string> words = {"banana", "apple", "cherry"};

    // SFINAE 版 print_all
    std::cout << "[SFINAE] print_all(ints): ";
    sfinae::print_all(nums);

    // SFINAE 版 sort_and_return
    auto sorted_sfinae = sfinae::sort_and_return(nums);
    std::cout << "[SFINAE] sort_and_return: ";
    sfinae::print_all(sorted_sfinae);

    // SFINAE 版 sum
    std::cout << "[SFINAE] sum: " << sfinae::sum(nums) << '\n';

    std::cout << "\n";
    std::cout << "比較ポイント:\n";
    std::cout << "  Concepts: template <SortableContainer C> void sort_if_sortable(C)\n";
    std::cout << "  SFINAE:   template <typename C, typename = std::enable_if_t<...>> void ...\n";
    std::cout << "\n";
    std::cout << "  Concepts はエラーメッセージが「制約 X を満たさない」と明確。\n";
    std::cout << "  SFINAE はオーバーロード解決失敗として報告され、原因が分かりにくい。\n";
}

// ============================================================
// main
// ============================================================
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
