# hello_cpp

This is HelloWorld++.

## ユニットテスト (Unit Tests)

[Unity](https://github.com/ThrowTheSwitch/Unity) を使ったユニットテストサンプルが `unittest/` フォルダにあります。

### 実行方法

```bash
cd unittest
make
```

または

```bash
cd unittest
make test
```

### クリーンアップ

```bash
cd unittest
make clean
```

### 構成

```
unittest/
├── Makefile              # ビルド・テスト実行用
├── test_calculator.c     # テストコード
├── src/
│   ├── calculator.h      # テスト対象のヘッダ
│   └── calculator.c      # テスト対象の実装（加算・減算・乗算）
└── unity/
    ├── unity.h           # Unity フレームワーク
    ├── unity_internals.h
    └── unity.c
```
