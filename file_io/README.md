# file_io

テキストファイルの読み書きを行うシンプルなサンプルです。  
C++ 標準ライブラリの `<fstream>` を使い、Google Test でテストしています。

---

## ディレクトリ構成

```text
.
├── CMakeLists.txt       # ビルド設定（FetchContent で Google Test を取得）
├── src/
│   ├── file_io.h        # ファイル読み書き関数の宣言
│   └── file_io.cpp      # ファイル読み書き関数の実装
└── test/
    └── test_file_io.cpp # Google Test を使ったテスト
```

---

## 実装している関数

```cpp
// テキストファイルに文字列を書き込む（成功時 true）
bool write_text_file(const std::string& path, const std::string& content);

// テキストファイルから文字列を読み込む（成功時 true、content に格納）
bool read_text_file(const std::string& path, std::string& content);
```

---

## Build & Run

```sh
cd file_io
mkdir -p build && cd build
cmake ..
make
ctest --output-on-failure
```

### 実行結果例

```text
100% tests passed, 0 tests failed out of 8
```
