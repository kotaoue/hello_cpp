#pragma once

#include <concepts>
#include <iostream>
#include <iterator>
#include <ranges>

// ============================================================
// C++20 Concepts 定義
//
// Concept は「型が満たすべき制約」をコンパイル時に検査する仕組み。
// テンプレートの requires 句や concept キーワードで記述する。
// ============================================================

// ------------------------------------------------------------
// Printable: std::ostream に << で出力できる型
// ------------------------------------------------------------
template <typename T>
concept Printable = requires(const T& t, std::ostream& os) {
    { os << t } -> std::same_as<std::ostream&>;
};

// ------------------------------------------------------------
// Addable: + 演算子で同型同士を加算できる型
// 結果の型が T と同じかどうかも検査する
// ------------------------------------------------------------
template <typename T>
concept Addable = requires(const T& a, const T& b) {
    { a + b } -> std::same_as<T>;
};

// ------------------------------------------------------------
// Subtractable: - 演算子で同型同士を減算できる型
// ------------------------------------------------------------
template <typename T>
concept Subtractable = requires(const T& a, const T& b) {
    { a - b } -> std::same_as<T>;
};

// ------------------------------------------------------------
// Sortable: < による全順序比較が可能な型
// std::totally_ordered は ==, !=, <, <=, >, >= を要求する
// ------------------------------------------------------------
template <typename T>
concept Sortable = std::totally_ordered<T>;

// ------------------------------------------------------------
// EqualityComparable: == と != で比較できる型
// (std::equality_comparable は標準ライブラリにすでに存在するが、
//  学習目的で手動定義したバージョンも示す)
// ------------------------------------------------------------
template <typename T>
concept EqualityComparable = requires(const T& a, const T& b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

// ------------------------------------------------------------
// Container: begin()/end() を持ちイテレータが使える型
// std::ranges::range がそのものだが、学習用に手動定義も示す
// ------------------------------------------------------------
template <typename C>
concept Container = requires(C& c) {
    { std::begin(c) } -> std::input_or_output_iterator;
    { std::end(c) }   -> std::sentinel_for<decltype(std::begin(c))>;
};

// ------------------------------------------------------------
// SortableContainer: 要素が Sortable な Container
// コンセプトを組み合わせ、より強い制約を作る例
// ------------------------------------------------------------
template <typename C>
concept SortableContainer =
    Container<C> &&
    Sortable<std::ranges::range_value_t<C>>;

// ------------------------------------------------------------
// PrintableContainer: 要素が Printable な Container
// ------------------------------------------------------------
template <typename C>
concept PrintableContainer =
    Container<C> &&
    Printable<std::ranges::range_value_t<C>>;

// ------------------------------------------------------------
// Numeric: 数値演算（加減算）が可能な型
// 複数のコンセプトを && で合成した例
// ------------------------------------------------------------
template <typename T>
concept Numeric = Addable<T> && Subtractable<T> && std::totally_ordered<T>;
