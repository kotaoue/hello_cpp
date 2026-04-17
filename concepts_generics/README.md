# hello_cpp

C++20 Concepts を使った型制約付きジェネリクスライブラリのサンプルです。  
テンプレートメタプログラミング・Concepts による制約・SFINAE との比較を学べます。

---

## ディレクトリ構成

```text
concepts_generics/
├── CMakeLists.txt
├── include/
│   ├── concepts.hpp          # Concept 定義
│   ├── algorithms.hpp        # 制約付きアルゴリズム
│   └── sfinae_comparison.hpp # SFINAE 版（比較用）
└── src/
    └── main.cpp              # デモプログラム
```

---

## 1. Concept 定義 (`include/concepts.hpp`)

**Concept** は「型が満たすべき制約」をコンパイル時に検査する仕組みです。

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

| Concept | 意味 |
| --- | --- |
| `Printable<T>` | `std::ostream <<` で出力できる型 |
| `Sortable<T>` | `<` による全順序比較が可能な型 |
| `Addable<T>` / `Subtractable<T>` | `+` / `-` が使える型 |
| `Container<C>` | `begin()` / `end()` を持つ型 |
| `SortableContainer<C>` | 要素が `Sortable` な `Container` |
| `Numeric<T>` | 複数 Concept を合成した例 |

---

## 2. 制約付きアルゴリズム (`include/algorithms.hpp`)

```cpp
// テンプレート引数の位置に Concept を書く
template <SortableContainer C>
C sort_if_sortable(C container);

// requires 節を後置する書き方
template <Container C>
    requires Addable<std::ranges::range_value_t<C>>
auto sum(const C& container) -> std::ranges::range_value_t<C>;
```

| 関数 | 概要 |
| --- | --- |
| `sort_if_sortable(c)` | コンテナをソートして返す |
| `print_all(c, os, sep)` | 要素を区切り文字付きで出力 |
| `sum(c)` | 要素の総和を返す |
| `max_element_of(c)` / `min_element_of(c)` | 最大・最小要素を返す |
| `filter_and_print(c, pred)` | 述語でフィルタして出力（Ranges） |
| `transform_and_collect(c, f)` | 変換して `vector` に収める（Ranges） |
| `clamp_all(c, lo, hi)` | 各要素を範囲にクランプする |

---

## 3. SFINAE との比較 (`include/sfinae_comparison.hpp`)

同じ機能を `std::enable_if_t` で実装した比較用コードです。

```cpp
// Concepts 版
template <SortableContainer C>
C sort_if_sortable(C container);

// SFINAE 版
template <typename C,
          typename = std::enable_if_t<is_sortable_v<typename C::value_type>>>
C sort_and_return(C container);
```

| 比較項目 | Concepts | SFINAE |
| --- | --- | --- |
| 宣言の読みやすさ | ◎ 意図が一目瞭然 | △ `enable_if_t` が長くなる |
| エラーメッセージ | ◎「制約 X を満たさない」と明確 | △ オーバーロード失敗として報告 |
| 対応バージョン | C++20 以降 | C++11 以降 |

---

## Build & Run

```sh
cd concepts_generics
mkdir build && cd build
cmake ..
make
./concepts_demo
```
