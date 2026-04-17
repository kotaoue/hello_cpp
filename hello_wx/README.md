# wxWidgets Hello World

wxWidgets を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

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
mkdir build && cd build
cmake ..
make
./wx_hello
```

macOS で Homebrew の wxWidgets を使う場合、CMake に wxWidgets のパスを渡す必要があります:

```sh
cd hello_wx
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="$(brew --prefix wxwidgets)"
make
./wx_hello
```

実行すると "Hello, World!" と書かれたウィンドウが表示されます。
