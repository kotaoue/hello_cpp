# Qt Hello World

Qt Widgets を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

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
