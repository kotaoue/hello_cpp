# GTK Hello World

GTK を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。  
GTK4 を優先し、環境に GTK4 がなければ GTK3 で自動的にビルドします。

---

## Features

* **クロスプラットフォーム** — Linux・macOS・Windows で動作します
* **GTK4/GTK3 対応** — GTK4 を優先し、GTK4 がない環境では GTK3 で自動的にビルドします
* **CSS スタイリング** — CSS 構文でウィジェットの見た目をカスタマイズできます
* **ネイティブ統合** — GNOME デスクトップ環境と深く統合され、システムテーマを活かせます
* **長期サポート** — GNOME プロジェクトによってアクティブにメンテナンスされています

---

## ディレクトリ構成

```text
hello_gtk/
├── CMakeLists.txt
└── main.cpp
```

---

## 要件

- GTK4 または GTK3
- CMake 3.16 以上

### macOS（Homebrew）

```sh
brew install gtk4
# GTK3 を使う場合
# brew install gtk+3
```

---

## Build & Run

```sh
cd hello_gtk
mkdir -p build && cd build
cmake ..
make
./gtk_hello
```

実行すると "Hello, World!" と書かれたウィンドウが表示されます。
