# Cocos2d-x Hello World

Cocos2d-x を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

---

## Features

* **ゲームエンジン** — 2D・3D ゲーム開発向けのオープンソース C++ フレームワークです
* **クロスプラットフォーム** — iOS・Android・macOS・Windows・Linux で動作します
* **OpenGL** — ハードウェアアクセラレーションによる高速な描画を実現します
* **シーン管理** — シーン・レイヤー・スプライトなどのゲームオブジェクトを階層的に管理できます

---

## ディレクトリ構成

```text
hello_cocos2d/
├── Classes/
│   ├── AppDelegate.h
│   ├── AppDelegate.cpp
│   ├── HelloWorldScene.h
│   └── HelloWorldScene.cpp
└── CMakeLists.txt
```

---

## 要件

- [Cocos2d-x v4.0](https://github.com/cocos2d/cocos2d-x/releases/tag/v4.0)
- CMake 3.16 以上
- C++17 対応コンパイラ（GCC 7+・Clang 5+・MSVC 2017+）

### macOS

```sh
# Xcode コマンドラインツール
xcode-select --install
# CMake（Homebrew）
brew install cmake
```

### Ubuntu / Debian

```sh
sudo apt update
sudo apt install build-essential cmake libgl1-mesa-dev libglu1-mesa-dev \
    libx11-dev libxrandr-dev libxi-dev libxxf86vm-dev \
    libpng-dev libjpeg-dev libfreetype6-dev zlib1g-dev \
    libopenal-dev libvorbis-dev libsndfile1-dev
```

---

## Cocos2d-x の準備

このプロジェクトは Cocos2d-x エンジンを外部ディレクトリとして参照します。  
以下の手順でエンジンを取得してください。

```sh
# hello_cocos2d の隣に cocos2d-x を配置する
cd <このリポジトリのルート>
git clone https://github.com/cocos2d/cocos2d-x.git --branch v4.0 --depth 1
cd cocos2d-x
python3 download-deps.py   # サードパーティライブラリをダウンロード
```

実行後のディレクトリ構成：

```text
<リポジトリルート>/
├── hello_cocos2d/   ← このプロジェクト
└── cocos2d-x/       ← エンジン（リポジトリ外）
```

---

## Build & Run

```sh
cd hello_cocos2d
mkdir build && cd build
cmake ..
make -j$(nproc)
./HelloCocos2dx
```

### Cocos2d-x が別の場所にある場合

```sh
cmake .. -DCOCOS2DX_ROOT_PATH=/path/to/cocos2d-x
```

実行すると黒い背景に白字で "Hello, World!" と書かれたウィンドウが表示されます。
