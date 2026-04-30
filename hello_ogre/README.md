# OGRE Hello World

OGRE（Object-Oriented Graphics Rendering Engine）の `OgreBites::ApplicationContext` を使った最小構成の Hello World アプリです。  
ウィンドウを作成し、紺色の背景を描画します。Escape キーを押すと終了します。

---

## Features

* **OGRE 3D エンジン** — シーン指向の C++ 製 3D グラフィックスエンジンで、OpenGL / DirectX などの複数バックエンドに対応しています
* **ApplicationContext** — OGRE Bites が提供するアプリケーションフレームワーク。ウィンドウ生成・入力処理・レンダリングループを自動管理します
* **RTShaderSystem** — 実行時シェーダー生成システム。固定パイプラインを自動的に GLSL / HLSL シェーダーへ変換します

---

## ディレクトリ構成

```text
hello_ogre/
├── CMakeLists.txt
└── main.cpp
```

---

## 要件

- CMake 3.16 以上
- OGRE 1.12 以上（開発パッケージ）

### macOS（Homebrew）

```sh
brew install ogre cmake
```

### Ubuntu / Debian

```sh
sudo apt install libogre-1.12-dev cmake
```

---

## Build & Run

```sh
cd hello_ogre
mkdir build && cd build
cmake ..
make
./ogre_hello
```

実行すると紺色の背景を持つ OGRE ウィンドウが表示されます。  
Escape キーを押すか、ウィンドウを閉じると終了します。

---

## ビルド時の注意

Ubuntu でデフォルトの `cmake ..` を実行すると OGRE の CMake 設定ファイルが自動的に検出されます。  
検出に失敗する場合は以下のように cmake のオプションで明示的に指定してください。

```sh
cmake .. -DOGRE_DIR=/usr/lib/x86_64-linux-gnu/OGRE/cmake
```

macOS の Homebrew 環境では次のようにしてください。

```sh
cmake .. -DOGRE_DIR=$(brew --prefix ogre)/lib/cmake/OGRE
```
