# GTK Hello World

GTK を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。  
GTK4 を優先し、環境に GTK4 がなければ GTK3 で自動的にビルドします。

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

### Ubuntu / Debian

```sh
sudo apt install libgtk-4-dev cmake
# GTK3 を使う場合
# sudo apt install libgtk-3-dev cmake
```

---

## Build & Run

```sh
cd hello_gtk
mkdir build && cd build
cmake ..
make
./gtk_hello
```

実行すると "Hello, World!" と書かれたウィンドウが表示されます。
