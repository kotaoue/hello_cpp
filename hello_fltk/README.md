# FLTK Hello World

FLTK (Fast Light Toolkit) を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

---

## Features

* **軽量・高速** — 最小限の依存関係で起動が速く、フットプリントが小さいです
* **クロスプラットフォーム** — Linux・macOS・Windows で一貫した見た目で動作します
* **自己完結型** — システムのウィジェットツールキットに依存せず、単体ライブラリとして動作します
* **OpenGL サポート** — オプションでハードウェアアクセラレーションによるレンダリングが可能です
* **シンプルな API** — 小さく学習しやすい C++ API で素早くアプリを開発できます

---

## ディレクトリ構成

```text
hello_fltk/
├── CMakeLists.txt
└── main.cpp
```

---

## 要件

- FLTK 1.3 以上
- CMake 3.16 以上

### macOS（Homebrew）

```sh
brew install fltk
```

### Ubuntu / Debian

```sh
sudo apt install libfltk1.3-dev cmake
```

---

## Build & Run

```sh
cd hello_fltk
mkdir build && cd build
cmake ..
make
./fltk_hello
```

実行すると "Hello, World!" と書かれたウィンドウが表示されます。
