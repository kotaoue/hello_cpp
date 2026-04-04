# 文字コード変換サンプル（C++ 版）

`iconv` を使って UTF-8・Shift-JIS・EUC-JP など異なる文字コード間でテキストを変換する  
サンプルと Google Test によるユニットテストです。

---

## ディレクトリ構成

```
character_encoding/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── encoding_converter.h    # 変換関数の宣言
│   └── encoding_converter.cpp  # 変換関数の実装（iconv 使用）
└── test/
    └── test_encoding_converter.cpp  # ユニットテスト
```

---

## API

```cpp
// 文字コードを変換する
// input         : 変換元の文字列（バイト列）
// from_encoding : 変換元の文字コード（例: "UTF-8", "Shift-JIS", "EUC-JP"）
// to_encoding   : 変換先の文字コード（例: "UTF-8", "Shift-JIS", "EUC-JP"）
// output        : 変換後の文字列を格納する変数（出力引数）
// 戻り値        : 変換に成功した場合 true、失敗した場合 false
bool convert_encoding(const std::string& input,
                      const std::string& from_encoding,
                      const std::string& to_encoding,
                      std::string& output);
```

---

## ビルドと実行

```bash
mkdir build && cd build
cmake ..
make
ctest --output-on-failure
```

---

## テスト内容

| テスト名 | 内容 |
|---|---|
| `UTF8ToUTF8ReturnsInput` | UTF-8 → UTF-8 の恒等変換 |
| `ShiftJISToShiftJISReturnsInput` | Shift-JIS → Shift-JIS の恒等変換 |
| `UTF8ToShiftJIS` | UTF-8 → Shift-JIS への変換 |
| `ShiftJISToUTF8` | Shift-JIS → UTF-8 への変換 |
| `UTF8ToEUCJP` | UTF-8 → EUC-JP への変換 |
| `EUCJPToUTF8` | EUC-JP → UTF-8 への変換 |
| `ShiftJISToEUCJP` | Shift-JIS → EUC-JP への変換 |
| `EUCJPToShiftJIS` | EUC-JP → Shift-JIS への変換 |
| `AsciiStringUTF8ToShiftJIS` | ASCII 文字列は変換後も一致する |
| `EmptyStringUTF8ToShiftJIS` | 空文字列の変換 |
| `InvalidEncodingNameReturnsFalse` | 不正な文字コード名を指定した場合は false を返す |
| `InvalidInputBytesReturnsFalse` | 不正なバイト列を変換しようとした場合は false を返す |

---

## 依存関係

- `iconv` — Linux / macOS の標準ライブラリに含まれています
- CMake 3.16 以上
- C++17 以上
