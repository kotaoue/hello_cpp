# FLTK Hello World

FLTK (Fast Light Toolkit) を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

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
