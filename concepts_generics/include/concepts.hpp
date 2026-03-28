#pragma once

#include <concepts>
#include <iostream>
#include <iterator>
#include <ranges>

// std::ostream に << で出力できる型
template <typename T>
concept Printable = requires(const T& t, std::ostream& os) {
    { os << t } -> std::same_as<std::ostream&>;
};

// + 演算子で同型同士を加算できる型
template <typename T>
concept Addable = requires(const T& a, const T& b) {
    { a + b } -> std::same_as<T>;
};

// - 演算子で同型同士を減算できる型
template <typename T>
concept Subtractable = requires(const T& a, const T& b) {
    { a - b } -> std::same_as<T>;
};

// < による全順序比較が可能な型（==, !=, <, <=, >, >= を要求）
template <typename T>
concept Sortable = std::totally_ordered<T>;

// == と != で比較できる型
template <typename T>
concept EqualityComparable = requires(const T& a, const T& b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

// begin()/end() を持ちイテレータが使える型
template <typename C>
concept Container = requires(C& c) {
    { std::begin(c) } -> std::input_or_output_iterator;
    { std::end(c) }   -> std::sentinel_for<decltype(std::begin(c))>;
};

// 要素が Sortable な Container
template <typename C>
concept SortableContainer =
    Container<C> &&
    Sortable<std::ranges::range_value_t<C>>;

// 要素が Printable な Container
template <typename C>
concept PrintableContainer =
    Container<C> &&
    Printable<std::ranges::range_value_t<C>>;

// 加減算と全順序比較が可能な型
template <typename T>
concept Numeric = Addable<T> && Subtractable<T> && std::totally_ordered<T>;

