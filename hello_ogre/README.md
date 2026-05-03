# OGRE Hello World

OGRE（Object-Oriented Graphics Rendering Engine）を使った最小構成の Hello World 3D アプリです。  
頂点カラー付きの立方体が回転しながら描画される 3D ウィンドウを表示します。

---

## Features

* **3D レンダリングエンジン** — C++ 向けの老舗オープンソース 3D グラフィックスエンジンです
* **OgreBites** — ウィンドウ生成・入力処理・レンダーループをまとめた便利なラッパーです
* **RTShaderSystem** — 固定機能パイプラインを GLSL/HLSL シェーダーで自動置換します
* **ManualObject** — ランタイムに頂点データを直接構築できるプリミティブです

---

## ディレクトリ構成

```text
hello_ogre/
├── CMakeLists.txt
└── main.cpp
```

---

## 要件

* macOS（Apple Silicon / Intel）
* CMake 3.16 以上
* OGRE 1.12 以上（OgreBites・RTShaderSystem コンポーネントを含む）

---

## OGRE のインストール（ソースビルド）

Homebrew に `ogre` formula は存在しないため、ソースからビルドします。

### Initial Setup

```sh
# 依存ライブラリのインストール
brew install cmake sdl2 freetype freeimage

# OGREのビルド
git clone --recurse-submodules https://github.com/OGRECave/ogre.git
cd ogre

mkdir build -p && cd build
cmake .. \
  -DCMAKE_INSTALL_PREFIX=$HOME/ogre-dist \
  -DOGRE_BUILD_COMPONENT_BITES=ON \
  -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM=ON
cmake --build . --config Release
cmake --install .
```

## Build & Run

```sh
cd ../../
cd hello_ogre
mkdir -p build && cd build
cmake -DCMAKE_PREFIX_PATH=$HOME/ogre-dist ..
make
./ogre_hello
```

実行すると頂点カラー付きの立方体が回転する OGRE ウィンドウが表示されます。  
Esc キーを押すかウィンドウを閉じると終了します。

---

## トラブルシューティング

### OGRE が見つからない場合

`cmake ..` で OGRE が見つからない場合、インストール先を明示します。

```sh
cmake -DCMAKE_PREFIX_PATH=$HOME/ogre-dist ..
# または
cmake -DOGRE_DIR=$HOME/ogre-dist/lib/cmake/OGRE ..
```

インストール先を確認するには次を実行してください。

```sh
find $HOME/ogre-dist -name "OGREConfig.cmake"
```

### OGRE なしで configure だけ通す

OGRE がインストールされていない環境では、デフォルトで `ogre_hello` ターゲットをスキップして configure を継続します。  
OGRE を必須にしたい（OGRE が見つからない場合にエラーにしたい）場合は次を使ってください。

```sh
cmake -DOGRE_HELLO_REQUIRE_OGRE=ON ..
```
