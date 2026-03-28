# hello_cpp

Google Test を使ったシンプルなユニットテストのサンプルです。

---

## ディレクトリ構成

```
.
├── CMakeLists.txt          # ビルド設定（FetchContent で Google Test を取得）
├── src/
│   ├── calculator.h        # 足し算・引き算・掛け算の関数宣言
│   └── calculator.cpp      # 足し算・引き算・掛け算の実装
└── test/
    └── test_calculator.cpp # Google Test を使ったテスト
```

---

## Google Test を使った簡単なテスト

**Google Test** は Google 製の C++ テストフレームワークで、C++ のデファクトスタンダードです。

```cpp
// テストケース例
TEST(CalculatorAdd, 正の数同士) {
    EXPECT_EQ(5, calculator_add(2, 3));
}
```

`TEST(スイート名, テスト名)` マクロでテストケースを定義し、  
`EXPECT_EQ(期待値, 実際値)` で検証します。

---

## ビルドと実行

```sh
mkdir build && cd build
cmake ..
make
ctest --output-on-failure
```

### 実行結果例

```
100% tests passed, 0 tests failed out of 7
```
