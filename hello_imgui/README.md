# ImGui Hello World

Dear ImGui と GLFW + OpenGL3 を使った最小構成の Hello World GUI アプリです。  
ウィンドウ内に ImGui パネルを表示し、"Hello, World!" テキストと Close ボタンを描画します。

---

## Features

* **即時モード (Immediate Mode)** — フレームごとに UI を再構築するため、状態管理がシンプルで予測しやすいです
* **バックエンド非依存** — OpenGL・DirectX・Vulkan・Metal など任意のレンダリングバックエンドと組み合わせられます
* **OS ウィジェット不要** — 選択したグラフィックス API のみで UI を描画するため、OS のウィジェット機能に依存しません
* **ゲーム・ツール向け** — ゲームエンジンや開発ツールのデバッグ UI として広く使われています
* **簡単な統合** — ヘッダーオンリーで導入できるため、既存プロジェクトへの組み込みが容易です

---

## ディレクトリ構成

```text
imgui_hello/
├── CMakeLists.txt
└── main.cpp
```

---

## 要件

- CMake 3.16 以上
- OpenGL をサポートするグラフィックドライバー
- インターネット接続（初回ビルド時に ImGui・GLFW を自動取得）

### macOS

```sh
xcode-select --install   # Xcode コマンドラインツール（未インストールの場合）
brew install cmake       # CMake
```

### Ubuntu / Debian

```sh
sudo apt install cmake libgl1-mesa-dev libxrandr-dev libxinerama-dev \
                 libxcursor-dev libxi-dev libxext-dev
```

---

## Build & Run

```sh
cd hello_imgui
mkdir -p build && cd build
cmake ..
make
./imgui_hello
```

実行すると "Hello, World!" と "Close" ボタンを持つ ImGui ウィンドウが表示されます。  
Close ボタンをクリックするか、ウィンドウを閉じると終了します。
