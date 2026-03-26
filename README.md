# hello_cpp

ユニットテストを理解するための最小構成サンプルです。  
C 言語のテストフレームワーク **Unity** と、モック生成フレームワーク **CMock** を使っています。

---

## ディレクトリ構成

```
.
├── CMakeLists.txt          # ビルド設定
├── src/
│   ├── calculator.h/c      # 足し算・引き算・掛け算（Unity でテスト対象）
│   ├── clock.h/c           # 時刻で挨拶を返す関数（CMock でテスト対象）
│   ├── time_provider.h/c   # time() のラッパー（モック差し替えのための境界）
├── test/
│   ├── test_calculator.c   # Unity を使ったシンプルなテスト
│   ├── test_clock.c        # CMock を使って time_provider をモックしたテスト
│   └── mocks/
│       ├── mock_time_provider.h/c  # CMock が生成するモック（今回は手書き）
└── vendor/
    ├── unity/src/          # Unity フレームワーク本体
    └── cmock/src/          # CMock フレームワーク本体
```

---

## 1. Unity を使った簡単なテスト (`test_calculator.c`)

**Unity** は ThrowTheSwitch 製の軽量 C 用テストフレームワークです。

```c
// テストケース例
void test_calculator_add_正の数(void)
{
    TEST_ASSERT_EQUAL_INT(5, calculator_add(2, 3));
}
```

`TEST_ASSERT_EQUAL_INT(期待値, 実際値)` のようなマクロで期待値を宣言するだけです。  
`setUp()` / `tearDown()` は各テストの前後に自動で呼ばれます。

---

## 2. CMock を使ってモックしたテスト (`test_clock.c`)

**CMock** は同じく ThrowTheSwitch 製のモック自動生成フレームワークです。  
ヘッダファイルを解析して、テスト用のモック実装を自動生成します。

### なぜモックが必要か？

`clock_get_greeting()` は内部で **現在時刻** を取得します。  
実際の時刻に依存するとテストが不安定になります（昼に実行すると深夜のテストができない）。

```c
// clock.c の内部
const char *clock_get_greeting(void)
{
    time_t now = time_provider_get_time();  // ← ここをモックで差し替える
    ...
}
```

### モックの使い方

```c
void test_clock_朝は_Good_morning(void)
{
    // 「次の呼び出しで午前 8 時を返す」と期待を設定
    time_provider_get_time_ExpectAndReturn(make_time(8, 0, 0));

    // clock_get_greeting() は内部でモックを呼ぶので、常に朝の挨拶になる
    TEST_ASSERT_EQUAL_STRING("Good morning", clock_get_greeting());
}
```

1. `time_provider_get_time_ExpectAndReturn(値)` でモックの戻り値を設定
2. `tearDown()` 内の `mock_time_provider_Verify()` で、設定した期待呼び出しが全て行われたか確認

### CMock のモック生成（通常の使い方）

本来は以下のコマンドでモックを自動生成します：

```sh
ruby vendor/cmock/lib/cmock.rb --mock_path=test/mocks src/time_provider.h
```

今回は学習目的で手書きしています（`test/mocks/mock_time_provider.c`）。

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
test_calculator.c:PASS (7 tests)
test_clock.c:PASS (8 tests)

100% tests passed, 0 tests failed out of 2
```

