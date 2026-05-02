# hello_cpp

ユニットテストを理解するための最小構成サンプルです。  
C++ のテストフレームワーク **Google Test** と、モックフレームワーク **Google Mock** を使っています。

---

## ディレクトリ構成

```text
unit_test_with_mock/
├── .gitignore
├── CMakeLists.txt          # ビルド設定（FetchContent で Google Test を取得）
├── README.md
├── src/
│   ├── calculator.h/cpp    # 足し算・引き算・掛け算（Google Test でテスト対象）
│   ├── ITimeProvider.h     # 現在時刻インターフェース（純粋仮想クラス）
│   ├── SystemTimeProvider.h # 実際のシステム時刻を返す実装
│   └── Clock.h/cpp         # 時刻で挨拶を返すクラス（Google Mock でテスト対象）
└── test/
    ├── test_calculator.cpp # Google Test を使ったシンプルなテスト
    └── test_clock.cpp      # Google Mock で ITimeProvider をモックしたテスト
```

---

## 1. Google Test を使った簡単なテスト (`test/test_calculator.cpp`)

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

## 2. Google Mock を使ってモックしたテスト (`test/test_clock.cpp`)

**Google Mock** は Google Test に付属するモックフレームワークです。  
`MOCK_METHOD` マクロで純粋仮想関数のモックを自動生成します。

### なぜモックが必要か？

`Clock::greeting()` は内部で **現在時刻** を取得します。  
実際の時刻に依存するとテストが不安定になります（昼に実行すると深夜のテストができない）。

```cpp
// ITimeProvider を継承したモッククラスを定義
class MockTimeProvider : public ITimeProvider {
public:
    MOCK_METHOD(std::time_t, now, (), (const, override));
};
```

### モックの使い方

```cpp
TEST(ClockGreeting, 朝は_GoodMorning) {
    MockTimeProvider mock;
    // now() が午前 8 時を返すよう期待を設定
    EXPECT_CALL(mock, now()).WillOnce(Return(make_time(8, 0)));

    Clock clock(mock);  // 依存注入でモックを渡す
    EXPECT_EQ("Good morning", clock.greeting());
}
```

1. `MockTimeProvider` で `ITimeProvider` のモックを作成
2. `EXPECT_CALL` で「どの戻り値を返すか」を設定
3. `Clock` にモックを注入してテスト（実際のシステム時刻には依存しない）

---

## Build & Run

```sh
cd unit_test_with_mock
mkdir -p build && cd build
cmake ..
make
ctest --output-on-failure
```

### 実行結果例

```text
100% tests passed, 0 tests failed out of 15
```
