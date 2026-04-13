# lambda

C++ のラムダ式（無名関数）の書き方をひととおり学べるサンプルです。  
C++11 で導入されたラムダ式の基本から、C++14 のジェネリックラムダまでを網羅します。

---

## ディレクトリ構成

```text
.
├── CMakeLists.txt   # ビルド設定
└── main.cpp         # ラムダ式デモ
```

---

## デモ一覧

| 関数 | 内容 |
| --- | --- |
| `demo_basic` | 引数なし・引数あり・戻り値型明示 |
| `demo_capture` | 値キャプチャ・参照キャプチャ・デフォルトキャプチャ |
| `demo_mutable` | `mutable` で値キャプチャ変数を書き換える |
| `demo_std_function` | `std::function` への格納と差し替え |
| `demo_stl_algorithms` | `std::sort` / `find_if` / `transform` / `accumulate` との組み合わせ |
| `demo_generic_lambda` | `auto` パラメータを使ったジェネリックラムダ（C++14） |
| `demo_iife` | 定義と同時に呼び出す即時実行ラムダ（IIFE） |
| `demo_closure_factory` | ラムダを返す関数（クロージャファクトリ） |
| `demo_recursive_lambda` | `std::function` を使った再帰ラムダ |

---

## ビルドと実行

```sh
mkdir build && cd build
cmake ..
make
./lambda_demo
```

### 実行結果例

```text
C++ ラムダ式 サンプル集
========================

=== 基本的なラムダ式 ===
Hello from lambda!
add(3, 4) = 7
divide(7.0, 2.0) = 3.5

=== キャプチャ ===
by value: x=10, y=20
counter after 2 increments: 2
sum(1,2,3) = 6
total = 15

=== mutable ラムダ ===
inside lambda: count=1
inside lambda: count=2
outside lambda: count=0

=== std::function に格納 ===
add: 8
mul: 15

=== STL アルゴリズムとの組み合わせ ===
sorted (desc): 9 8 7 6 5 4 3 2 1
first even: 8
squares: 81 64 49 36 25 16 9 4 1
total = 45

=== ジェネリックラムダ (C++14) ===
42
3.14
hello
max(3, 7)       = 7
max(1.5, 0.8)   = 1.5

=== 即時実行ラムダ (IIFE) ===
7^2 = 49
Hello, World!

=== クロージャファクトリ ===
add10(5)  = 15
add100(5) = 105

=== 再帰ラムダ ===
0! = 1
1! = 1
2! = 2
3! = 6
4! = 24
5! = 120
6! = 720
7! = 5040

全デモ完了
```
