#pragma once

#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>

// SFINAE (Substitution Failure Is Not An Error) を使った旧来の実装（C++17 以前のスタイル）
//
// テンプレート引数の置換が失敗してもエラーにしないことで条件付きテンプレートを実現する。
// Concepts と比較すると宣言が複雑で、エラーメッセージも不明瞭になりやすい。

namespace sfinae {

// << で ostream に出力できるか判定するメタ関数
template <typename T, typename = void>
struct is_printable : std::false_type {};

template <typename T>
struct is_printable<T,
    std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
    : std::true_type {};

template <typename T>
inline constexpr bool is_printable_v = is_printable<T>::value;

// < 演算子で比較できるか判定するメタ関数
template <typename T, typename = void>
struct is_sortable : std::false_type {};

template <typename T>
struct is_sortable<T,
    std::void_t<decltype(std::declval<const T&>() < std::declval<const T&>())>>
    : std::true_type {};

template <typename T>
inline constexpr bool is_sortable_v = is_sortable<T>::value;

// 各要素を区切り文字で出力する（SFINAE 版）
//   Concepts 版: template <PrintableContainer C> void print_all(...)
//   SFINAE 版:   template <typename C, typename = std::enable_if_t<...>> void print_all(...)
template <typename C,
          typename = std::enable_if_t<
              is_printable_v<typename C::value_type>>>
void print_all(const C& container,
               std::ostream& os = std::cout,
               const std::string& sep = " ")
{
    bool first = true;
    for (const auto& elem : container) {
        if (!first) os << sep;
        os << elem;
        first = false;
    }
    os << '\n';
}

// ソートして返す（SFINAE 版）
template <typename C,
          typename = std::enable_if_t<
              is_sortable_v<typename C::value_type>>>
C sort_and_return(C container)
{
    std::sort(container.begin(), container.end());
    return container;
}

// 算術型の要素を持つコンテナの総和を返す（SFINAE 版）
template <typename C,
          typename = std::enable_if_t<
              std::is_arithmetic_v<typename C::value_type>>>
typename C::value_type sum(const C& container)
{
    typename C::value_type result{};
    for (const auto& v : container) result += v;
    return result;
}

} // namespace sfinae

