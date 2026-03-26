#pragma once

#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>

// ============================================================
// SFINAE を使った旧来の実装（C++17 以前のスタイル）
//
// SFINAE (Substitution Failure Is Not An Error) は
// テンプレート引数の置換が失敗してもエラーにしないことで
// 条件付きテンプレートを実現する技法。
// Concepts と比較すると宣言が複雑で、エラーメッセージも不明瞭。
// ============================================================

namespace sfinae {

// ------------------------------------------------------------
// is_printable_v: << で ostream に出力できるか判定するメタ関数
//
// SFINAE の仕組み:
//  1. std::declval<std::ostream&>() << std::declval<const T&>()
//     の式が valid なら char 型が選ばれる
//  2. valid でなければ ... が選ばれ int 型になる
//  3. ::value でその結果を bool として取り出す
// ------------------------------------------------------------
template <typename T, typename = void>
struct is_printable : std::false_type {};

template <typename T>
struct is_printable<T,
    std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
    : std::true_type {};

template <typename T>
inline constexpr bool is_printable_v = is_printable<T>::value;

// ------------------------------------------------------------
// is_sortable_v: < 演算子で比較できるか判定するメタ関数
// ------------------------------------------------------------
template <typename T, typename = void>
struct is_sortable : std::false_type {};

template <typename T>
struct is_sortable<T,
    std::void_t<decltype(std::declval<const T&>() < std::declval<const T&>())>>
    : std::true_type {};

template <typename T>
inline constexpr bool is_sortable_v = is_sortable<T>::value;

// ------------------------------------------------------------
// print_all (SFINAE 版)
//   std::enable_if_t で "Printable な T を持つコンテナのみ" に制限。
//   Concepts 版と比べて宣言がかなり複雑。
//
//   エラー時のメッセージ例 (GCC):
//     "no matching function for call to 'sfinae::print_all(...)'"
//   Concepts 版では:
//     "constraints not satisfied for ... [with T = ...]"
//   のように、何の制約を満たさないかが明示される。
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// sort_and_return (SFINAE 版)
//   is_sortable_v でソート可能な要素を持つコンテナのみに制限。
// ------------------------------------------------------------
template <typename C,
          typename = std::enable_if_t<
              is_sortable_v<typename C::value_type>>>
C sort_and_return(C container)
{
    std::sort(container.begin(), container.end());
    return container;
}

// ------------------------------------------------------------
// sum (SFINAE 版)
//   value_type が算術型 (std::is_arithmetic) のコンテナのみ受け付ける。
//   Concepts 版では Addable という意味的な名前を使えるが、
//   SFINAE では型特性のチェックに頼るため表現力が落ちる。
// ------------------------------------------------------------
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
