# ImGui Hello World

Dear ImGui と GLFW + OpenGL3 を使った最小構成の Hello World GUI アプリです。  
ウィンドウ内に ImGui パネルを表示し、"Hello, World!" テキストと Close ボタンを描画します。

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

## ビルドと実行

```sh
mkdir build && cd build
cmake ..
make
./imgui_hello
```

実行すると "Hello, World!" と "Close" ボタンを持つ ImGui ウィンドウが表示されます。  
Close ボタンをクリックするか、ウィンドウを閉じると終了します。
