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

* CMake 3.16 以上
* OGRE 1.12 以上（OgreBites・RTShaderSystem コンポーネントを含む）
* OpenGL 対応グラフィックドライバー

### macOS（Homebrew）

```sh
# 利用可能か確認（時期により formula が提供されない場合があります）
brew search ogre
```

Homebrew で OGRE formula が見つからない場合は、OGRE を手動インストールして
`OGRE_DIR` または `CMAKE_PREFIX_PATH` を指定してください。

## Build & Run

```sh
cd hello_ogre
mkdir -p build && cd build
cmake ..
make
./ogre_hello
```

### OGRE の場所を明示して configure

```sh
cmake -DOGRE_DIR=/path/to/OGREConfig.cmake-directory ..
# または
cmake -DCMAKE_PREFIX_PATH=/path/to/ogre-prefix ..
```

### OGRE がない環境で configure だけ通す

`cmake ..` 実行時に OGRE が見つからない場合、デフォルトでは
`ogre_hello` ターゲットをスキップして configure を継続します。

OGRE を必須にしたい場合は次を使ってください。

```sh
cmake -DOGRE_HELLO_REQUIRE_OGRE=ON ..
```

実行すると頂点カラー付きの立方体が回転する OGRE ウィンドウが表示されます。  
Esc キーを押すかウィンドウを閉じると終了します。
