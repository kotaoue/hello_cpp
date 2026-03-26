# Concepts を活用したジェネリクスライブラリ

C++20 の **Concepts** を使い、型制約付きのテンプレートライブラリを実装したサンプルプロジェクト。

## ディレクトリ構成

```
concepts_generics/
├── include/
│   ├── concepts.hpp          # Concept 定義
│   ├── algorithms.hpp        # 制約付きアルゴリズム
│   └── sfinae_comparison.hpp # SFINAE 版（比較用）
├── src/
│   └── main.cpp              # デモプログラム
├── CMakeLists.txt
└── README.md
```

## ビルドと実行

```bash
cmake -S . -B build
cmake --build build
./build/concepts_demo
```

## 学べること

### 1. Concept 定義 (`include/concepts.hpp`)

| Concept | 意味 |
|---|---|
| `Printable<T>` | `std::ostream << T` が可能な型 |
| `Sortable<T>` | `<` による全順序比較が可能な型（`std::totally_ordered` の拡張） |
| `Addable<T>` | `T + T -> T` が可能な型 |
| `Subtractable<T>` | `T - T -> T` が可能な型 |
| `EqualityComparable<T>` | `==` と `!=` で比較できる型 |
| `Container<C>` | `begin()` / `end()` を持つイテレータ型 |
| `SortableContainer<C>` | 要素が `Sortable` な `Container` |
| `PrintableContainer<C>` | 要素が `Printable` な `Container` |
| `Numeric<T>` | `Addable` かつ `Subtractable` かつ全順序比較可能な型 |

```cpp
// requires 式で「式が valid かどうか」を検査する
template <typename T>
concept Printable = requires(const T& t, std::ostream& os) {
    { os << t } -> std::same_as<std::ostream&>;
};

// 既存の標準 concept を再利用する例
template <typename T>
concept Sortable = std::totally_ordered<T>;

// Concept を && で合成する例
template <typename T>
concept Numeric = Addable<T> && Subtractable<T> && std::totally_ordered<T>;
```

### 2. 制約付きアルゴリズム (`include/algorithms.hpp`)

```cpp
// 書き方 1: テンプレート引数の位置に Concept を書く
template <SortableContainer C>
C sort_if_sortable(C container);

// 書き方 2: requires 節を関数宣言の後ろに書く
template <Container C>
    requires Addable<std::ranges::range_value_t<C>>
auto sum(const C& container) -> std::ranges::range_value_t<C>;
```

| 関数 | 概要 |
|---|---|
| `sort_if_sortable(c)` | コンテナをソートして返す |
| `print_all(c, os, sep)` | 要素を区切り文字付きで出力 |
| `sum(c)` | 要素の総和を返す |
| `max_element_of(c)` | 最大要素を返す（空なら例外） |
| `min_element_of(c)` | 最小要素を返す（空なら例外） |
| `filter_and_print(c, pred)` | 述語でフィルタして出力（Ranges） |
| `transform_and_collect(c, f)` | 変換して `vector` に収める（Ranges） |
| `clamp_all(c, lo, hi)` | 各要素を範囲にクランプする |

### 3. Ranges との組み合わせ

`std::views::filter` や `std::views::transform` などの **Ranges アダプタ** と Concepts を組み合わせると、型安全な遅延評価パイプラインが書ける。

```cpp
// 偶数だけ出力する例
filter_and_print(nums, [](int n) { return n % 2 == 0; });

// 2 乗して collect する例
auto squares = transform_and_collect(nums, [](int n) { return n * n; });
```

### 4. SFINAE との比較 (`include/sfinae_comparison.hpp`)

| 比較項目 | Concepts | SFINAE |
|---|---|---|
| 宣言の読みやすさ | ◎ 意図が一目瞭然 | △ `enable_if_t` が長くなる |
| エラーメッセージ | ◎「制約 X を満たさない」と明確 | △ オーバーロード失敗として報告 |
| コンパイル速度 | ◎ 一般的に速い | △ 深い再帰が起きやすい |
| 対応する C++ バージョン | C++20 以降 | C++11 以降 |

**Concepts 版:**
```cpp
template <SortableContainer C>
C sort_if_sortable(C container);
```

**SFINAE 版:**
```cpp
template <typename C,
          typename = std::enable_if_t<
              sfinae::is_sortable_v<typename C::value_type>>>
C sort_and_return(C container);
```

## コンパイル時検査（`static_assert`）

```cpp
// Concept の適用結果をコンパイル時に検証できる
static_assert(Printable<int>);    // OK
static_assert(Sortable<double>);  // OK
static_assert(Numeric<int>);      // OK
```

不適切な型を渡した場合のコンパイルエラー例:

```
error: no matching function for call to 'sort_if_sortable'
note: constraints not satisfied
note: 'SortableContainer<std::vector<NoCompare>>' was not satisfied
```
