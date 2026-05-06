# Cocos2d-x Hello World

Cocos2d-x を使った最小構成の Hello World GUI アプリです。  
ウィンドウ中央に "Hello, World!" と表示します。

---

## Features

- **ゲームエンジン** — 2D・3D ゲーム開発向けのオープンソース C++ フレームワークです
- **クロスプラットフォーム** — iOS・Android・macOS・Windows・Linux で動作します
- **OpenGL** — ハードウェアアクセラレーションによる高速な描画を実現します
- **シーン管理** — シーン・レイヤー・スプライトなどのゲームオブジェクトを階層的に管理できます

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

## Cocos2d-x の準備

- [Cocos2d-x v4.0](https://github.com/cocos2d/cocos2d-x/releases/tag/v4.0)

このプロジェクトは Cocos2d-x エンジンを外部ディレクトリとして参照します。  
以下の手順でエンジンを取得してください。

```sh
# hello_cocos2d の隣に cocos2d-x を配置する
git clone https://github.com/cocos2d/cocos2d-x.git
cd cocos2d-x
git checkout cocos2d-x-4.0
# リポジトリ側の Python 3 対応スクリプトでサードパーティライブラリをダウンロード
python3 ../cocos2d-x-tools/download-deps.py
# サブモジュールを初期化
git submodule update --init
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
mkdir -p build && cd build
cmake ..
make -j4
./HelloCocos2dx
```

実行すると黒い背景に白字で "Hello, World!" と書かれたウィンドウが表示されます。

---

## 注意事項

### macOS での動作について

このプロジェクトは **macOS では動作しません**。理由は以下の通りです：

- **cocos2d-x v4.0 のリリース時期**: 2019年
- **問題**: 最新の macOS SDK（Xcode 15以降）では、`iconv` 関数のシグネチャが変更されました
- **コンパイルエラー**: 型の不一致により、`iconv_close()` と `iconv()` の呼び出しでコンパイルエラーが発生します
- **回避策なし**: CMake フラグやコンパイラオプションでは解決できない、根本的なフレームワークレベルの問題です

---

## macOS での C++ GUI 開発への代替案

macOS で C++ GUI アプリケーションを開発する場合は、以下のライブラリを推奨します：

### 1. **Qt** （推奨）
- 最高レベルのクロスプラットフォーム対応
- macOS での UI が native に見える
- 公式サイト: https://www.qt.io/

### 2. **wxWidgets**
- オープンソース、シンプルな API
- macOS の Cocoa をネイティブに使用
- 公式サイト: https://wxwidgets.org/

### 3. **FLTK（Fast Light Toolkit）**
- 軽量で シンプル
- macOS に対応した版が存在
- 公式サイト: https://www.fltk.org/

### 4. **Dear ImGui**
- ゲーム・実時間アプリ向け
- デスクトップアプリにも利用可能
- 公式サイト: https://github.com/ocornut/imgui

### 5. **Cocoa（macOS Native）**
- macOS 専用ですが、最高のパフォーマンス
- Objective-C++ を使用した直接的なネイティブ開発
- Apple Developer Documentation: https://developer.apple.com/documentation/appkit
