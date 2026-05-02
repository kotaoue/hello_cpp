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
brew install ogre
```

### Ubuntu / Debian

```sh
sudo apt install libogre-1.12-dev ogre-1.12-tools
```

> **Note:** Ubuntu 24.04 以降では `libogre-1.12-dev` の代わりに  
> `libogre-next-dev`（OGRE 2.x）が提供される場合があります。  
> パッケージ名が変わっていても CMakeLists.txt で OGRE が見つかれば問題ありません。

---

## Build & Run

```sh
cd hello_ogre
mkdir build && cd build
cmake ..
make
./ogre_hello
```

実行すると頂点カラー付きの立方体が回転する OGRE ウィンドウが表示されます。  
Esc キーを押すかウィンドウを閉じると終了します。
