# cpp_class

コンストラクタ・デストラクタをはじめ、C++ クラスの主要機能を一通り体験できるサンプルです。  
Google Test でテストしています。

---

## ディレクトリ構成

```
cpp_class/
├── CMakeLists.txt
├── include/
│   ├── shape.hpp    # 図形クラス階層（抽象基底クラス・派生クラス）
│   └── buffer.hpp   # 動的配列バッファ（Rule of Five の実装例）
├── src/
│   ├── shape.cpp
│   ├── buffer.cpp
│   └── main.cpp     # デモプログラム
└── test/
    └── test_class.cpp
```

---

## 実演する C++ クラス機能

### 1. コンストラクタ / デストラクタ（`Shape` 系クラス）

```cpp
class Shape {
public:
    explicit Shape(std::string name);  // コンストラクタ
    virtual ~Shape();                  // 仮想デストラクタ
    // ...
};
```

- **仮想デストラクタ** — 基底クラスのポインタで派生クラスを扱うとき、  
  `virtual ~Shape()` がなければ派生クラスのデストラクタが呼ばれない。

### 2. 純粋仮想関数 / 抽象クラス

```cpp
// 純粋仮想関数を持つクラスは抽象クラスとなり、直接インスタンス化できない
virtual double area()      const = 0;
virtual double perimeter() const = 0;
```

### 3. override キーワード

```cpp
class Circle : public Shape {
public:
    double area()      const override;  // override で意図を明示
    double perimeter() const override;
};
```

### 4. static メンバー変数 / 関数

```cpp
// インスタンスを生成するたびにカウントが増え、破棄で減る
static int instance_count() noexcept;

// 使い方（インスタンスなしで呼べる）
int n = Shape::instance_count();
```

### 5. const メンバー関数

```cpp
const std::string& name() const noexcept;  // オブジェクトを変更しない
```

### 6. operator<< オーバーロード

```cpp
std::ostream& operator<<(std::ostream& os, const Shape& shape);

// 使い方
Circle c(5.0);
std::cout << c << '\n';  // "Circle(r=5, area=78.54, perimeter=31.42)"
```

### 7. Rule of Five — `Buffer` クラス

動的メモリ確保を行うクラスでは以下の 5 つを明示的に実装する必要がある。

| # | 特殊メンバー関数 | 役割 |
|---|---|---|
| 1 | コンストラクタ | `new[]` でメモリ確保 (RAII) |
| 2 | デストラクタ | `delete[]` でメモリ解放 |
| 3 | コピーコンストラクタ | ディープコピー（独立した配列） |
| 4 | コピー代入演算子 | ディープコピー + 自己代入ガード |
| 5 | ムーブコンストラクタ | 所有権の移転（O(1), `noexcept`） |
| 6 | ムーブ代入演算子 | 所有権の移転（`noexcept`） |

```cpp
// コピー — 独立した配列が作られる
Buffer b1(4);
Buffer b2(b1);    // コピーコンストラクタ
b2[0] = 99;       // b1[0] は変わらない

// ムーブ — O(1) でポインタの所有権だけを移転
Buffer b3(std::move(b1));  // b1 は empty() になる
```

### 8. RAII パターン

```cpp
{
    Buffer buf(1024);  // コンストラクタでメモリ確保
    // ... 使用 ...
}  // ← スコープを抜けるとデストラクタが自動でメモリ解放
   //   例外が発生しても確実に解放される
```

---

## ビルドと実行

```sh
mkdir build && cd build
cmake ..
make

# デモ実行
./cpp_class_demo

# テスト実行
ctest --output-on-failure
```

---

## 学べること

| テーマ | 内容 |
|---|---|
| コンストラクタ / デストラクタ | オブジェクトの生成と破棄のタイミング |
| 仮想デストラクタ | 基底クラスポインタ経由での安全な破棄 |
| 純粋仮想関数 | インターフェースの定義と強制 |
| ポリモーフィズム | 基底クラスポインタで派生クラスを統一的に扱う |
| static メンバー | クラス全体で共有されるデータと関数 |
| const メンバー関数 | 状態を変えない操作の明示 |
| Rule of Five | コピー・ムーブの正しい実装パターン |
| RAII | コンストラクタ/デストラクタでリソースを管理 |
| operator オーバーロード | `<<` / `[]` / `==` / `!=` の実装例 |
