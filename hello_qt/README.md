# Qt Hello World

Qt Widgets を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

---

## Features

* **クロスプラットフォーム** — Linux・macOS・Windows・Android・iOS・組み込みシステムで動作します
* **シグナル & スロット** — オブジェクト間のイベント駆動通信を直感的に記述できます
* **豊富なウィジェット** — 標準・カスタムウィジェットの包括的なコレクションを提供します
* **Qt Designer 連携** — ドラッグ & ドロップでの UI 設計とライブプレビューが可能です
* **商用・OSS 両対応** — Qt Company による長期サポートと、オープンソース (LGPL/GPL) ライセンスの双方を選択できます

---

## ディレクトリ構成

```text
qt_hello/
├── CMakeLists.txt
└── main.cpp
```

---

## 要件

- Qt6 または Qt5（Widgets モジュール）
- CMake 3.16 以上

### macOS（Homebrew）

```sh
brew install qt
```

### Ubuntu / Debian

```sh
sudo apt install qt6-base-dev cmake
# Qt6 が使えない場合は Qt5 でも可
# sudo apt install qtbase5-dev cmake
```

---

## Build & Run

```sh
cd hello_qt
mkdir build && cd build
cmake ..
make
./qt_hello
```

macOS で Homebrew の Qt を使う場合、CMake に Qt のパスを渡す必要があります:

```sh
cd hello_qt
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
make
./qt_hello
```

実行すると "Hello, World!" と書かれたウィンドウが表示されます。
