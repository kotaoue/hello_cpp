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
brew install cmake ogre
```

CMake は `brew --prefix ogre` でインストール先を自動検出します。  
`brew info ogre` で formula が存在するか事前に確認してください。

### Ubuntu / Debian

```sh
sudo apt install cmake libogre-1.12-dev ogre-1.12-tools
```

---

## Build & Run

```sh
cd hello_ogre
mkdir -p build && cd build
cmake ..
make
./ogre_hello
```

実行すると頂点カラー付きの立方体が回転する OGRE ウィンドウが表示されます。  
Esc キーを押すかウィンドウを閉じると終了します。

---

## トラブルシューティング

### OGRE が見つからない場合

`cmake ..` で OGRE が見つからない場合、`OGREConfig.cmake` の場所を明示します。

```sh
# OGRE のインストール先を確認（macOS の例）
brew info ogre

# cmake に場所を指定
cmake -DOGRE_DIR=/opt/homebrew/lib/cmake/OGRE ..
# または
cmake -DCMAKE_PREFIX_PATH=$(brew --prefix ogre) ..
```

Ubuntu では次のように確認できます。

```sh
find /usr -name "OGREConfig.cmake" 2>/dev/null
cmake -DOGRE_DIR=<上記のディレクトリパス> ..
```

### OGRE なしで configure だけ通す

OGRE がインストールされていない環境では、デフォルトで `ogre_hello` ターゲットをスキップして configure を継続します。  
OGRE を必須にしたい（OGRE が見つからない場合にエラーにしたい）場合は次を使ってください。

```sh
cmake -DOGRE_HELLO_REQUIRE_OGRE=ON ..
```

