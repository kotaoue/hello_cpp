#pragma once

#include "concepts.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>

// コンテナをソートして返す
template <SortableContainer C>
C sort_if_sortable(C container)
{
    std::ranges::sort(container);
    return container;
}

// 各要素を区切り文字で出力する
template <PrintableContainer C>
void print_all(const C& container,
               std::ostream& os = std::cout,
               std::string_view sep = " ")
{
    bool first = true;
    for (const auto& elem : container) {
        if (!first) os << sep;
        os << elem;
        first = false;
    }
    os << '\n';
}

// Addable な要素を持つコンテナの総和を返す
template <Container C>
    requires Addable<std::ranges::range_value_t<C>>
auto sum(const C& container) -> std::ranges::range_value_t<C>
{
    using T = std::ranges::range_value_t<C>;
    return std::accumulate(std::begin(container), std::end(container), T{});
}

// 最大要素を返す（空コンテナは例外を投げる）
template <SortableContainer C>
auto max_element_of(const C& container) -> std::ranges::range_value_t<C>
{
    if (std::begin(container) == std::end(container)) {
        throw std::invalid_argument("max_element_of: empty container");
    }
    return *std::ranges::max_element(container);
}

// 最小要素を返す（空コンテナは例外を投げる）
template <SortableContainer C>
auto min_element_of(const C& container) -> std::ranges::range_value_t<C>
{
    if (std::begin(container) == std::end(container)) {
        throw std::invalid_argument("min_element_of: empty container");
    }
    return *std::ranges::min_element(container);
}

// 述語で絞り込んだ要素を出力する（Ranges との組み合わせ例）
template <PrintableContainer C, typename Pred>
    requires std::predicate<Pred, const std::ranges::range_value_t<C>&>
void filter_and_print(const C& container,
                      Pred predicate,
                      std::ostream& os = std::cout,
                      std::string_view sep = " ")
{
    bool first = true;
    for (const auto& elem : container | std::views::filter(predicate)) {
        if (!first) os << sep;
        os << elem;
        first = false;
    }
    os << '\n';
}

// 各要素に変換関数を適用し、新しい vector に収めて返す
template <Container C, typename F>
    requires std::invocable<F, const std::ranges::range_value_t<C>&>
auto transform_and_collect(const C& container, F func)
    -> std::vector<std::invoke_result_t<F, const std::ranges::range_value_t<C>&>>
{
    using R = std::invoke_result_t<F, const std::ranges::range_value_t<C>&>;
    std::vector<R> result;
    result.reserve(std::ranges::distance(container));
    for (const auto& elem : container | std::views::transform(func)) {
        result.push_back(elem);
    }
    return result;
}

// 各要素を [lo, hi] の範囲にクランプする
template <Container C>
    requires Numeric<std::ranges::range_value_t<C>>
C clamp_all(C container,
            const std::ranges::range_value_t<C>& lo,
            const std::ranges::range_value_t<C>& hi)
{
    for (auto& elem : container) {
        elem = std::clamp(elem, lo, hi);
    }
    return container;
}

