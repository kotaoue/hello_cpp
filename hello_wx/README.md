# wxWidgets Hello World

wxWidgets を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

---

## Features

* **ネイティブな外観** — Windows (Win32)・macOS (Cocoa)・Linux (GTK) の OS ネイティブウィジェットを使用し、プラットフォームらしい見た目を実現します
* **クロスプラットフォーム** — 単一のコードベースで主要 OS 向けにビルドできます
* **成熟・安定** — 25 年以上の開発実績と大規模なユーザーコミュニティを持ちます
* **豊富なウィジェット** — ファイルダイアログ・メニュー・ツールバーなどが標準で揃っています
* **C++ 標準準拠** — 最新の C++ コンパイラで動作し、標準ライブラリと自然に組み合わせられます

---

## ディレクトリ構成

```text
hello_wx/
├── CMakeLists.txt
└── main.cpp
```

---

## 要件

- wxWidgets 3.x（core・base モジュール）
- CMake 3.16 以上

### macOS（Homebrew）

```sh
brew install wxwidgets
```

### Ubuntu / Debian

```sh
sudo apt install libwxgtk3.2-dev cmake
# 古い環境では libwxgtk3.0-gtk3-dev でも可
```

---

## Build & Run

```sh
cd hello_wx
mkdir -p build && cd build
# macOS で Homebrew の wxWidgets を使う場合、CMake に wxWidgets のパスを渡す必要があります:
cmake .. -DCMAKE_PREFIX_PATH="$(brew --prefix wxwidgets)"
make
open ./wx_hello.app
```

実行すると "Hello, World!" と書かれたウィンドウが表示されます。
