# 外部 API 接続サンプル（C++ 版）

libcurl を使って外部 REST API を叩くサンプルです。  
[hello_c/external_api](https://github.com/kotaoue/hello_c/tree/main/external_api) と同じ処理を **C++ らしい書き方** で実装し、違いを比較します。

---

## ディレクトリ構成

```
external_api/
├── CMakeLists.txt
├── include/
│   └── http_client.hpp   # http::Response 構造体と http::Client クラスの宣言
└── src/
    ├── http_client.cpp   # libcurl を使った GET / POST の実装
    └── main.cpp          # httpbin.org を叩くデモプログラム
```

---

## 学べること

| テーマ | 内容 |
|---|---|
| RAII | `Client` クラスがコンストラクタ/デストラクタで `curl_global_init/cleanup` を管理 |
| `std::unique_ptr` | CURL ハンドルと `curl_slist` をスマートポインタで管理し、手動解放を排除 |
| 値型のレスポンス | `struct Response { std::string body; long status_code; }` — ポインタ渡し不要 |
| `std::string` | `realloc` + `memcpy` の代わりに `append()` でレスポンスボディを蓄積 |
| カスタムデリータ | `std::unique_ptr` に libcurl 専用のデリータを渡してリソース管理を汎用化 |

---

## C 版との比較

### リソース管理

```c
// C 版: main() で明示的に呼ぶ必要がある
curl_global_init(CURL_GLOBAL_DEFAULT);
// ... 処理 ...
curl_global_cleanup();
```

```cpp
// C++ 版: コンストラクタ/デストラクタが自動で管理する (RAII)
const http::Client client; // ← ここで curl_global_init()
// ... 処理 ...
// ← スコープを抜けると自動で curl_global_cleanup()
```

### レスポンスの受け取り方

```c
// C 版: ポインタで受け取り、使い終わったら手動で解放する
HttpResponse *resp = http_get("https://httpbin.org/get");
printf("%ld\n%s\n", resp->status_code, resp->body);
http_response_free(resp); // ← 忘れるとメモリリーク
```

```cpp
// C++ 版: 値型で受け取る。std::string が自動的にメモリを解放する
auto resp = client.get("https://httpbin.org/get");
std::cout << resp.status_code << "\n" << resp.body << "\n";
// ← 解放不要
```

### レスポンスボディの蓄積

```c
// C 版: realloc + memcpy で動的バッファに追記する
char *tmp = realloc(buf->data, buf->len + total + 1);
memcpy(buf->data + buf->len, ptr, total);
buf->len += total;
buf->data[buf->len] = '\0';
```

```cpp
// C++ 版: std::string::append() に置き換えるだけ
buf->append(ptr, total);
```

### CURL ハンドルの管理

```c
// C 版: 手動で解放する（例外が起きると漏れる）
CURL *curl = curl_easy_init();
// ... 処理 ...
curl_easy_cleanup(curl);
```

```cpp
// C++ 版: unique_ptr + カスタムデリータでスコープ終了時に自動解放
struct CurlEasyDeleter {
    void operator()(CURL* h) const noexcept { curl_easy_cleanup(h); }
};
std::unique_ptr<CURL, CurlEasyDeleter> curl{curl_easy_init()};
```

---

## 依存ライブラリ

| ライブラリ | 用途 |
|---|---|
| [libcurl](https://curl.se/libcurl/) | HTTP リクエストの送受信 |

### インストール方法

```bash
# macOS
brew install curl

# Ubuntu / Debian
sudo apt install libcurl4-openssl-dev

# Fedora / RHEL
sudo dnf install libcurl-devel
```

---

## ビルドと実行

```sh
mkdir build && cd build
cmake ..
make
./external_api_demo
```

---

## 実行結果の例

```
--- GET リクエスト ---
URL: https://httpbin.org/get
ステータスコード: 200
レスポンスボディ:
{
  "args": {},
  "headers": {
    "Accept": "*/*",
    "Host": "httpbin.org",
    ...
  },
  "url": "https://httpbin.org/get"
}

--- POST リクエスト ---
URL:              https://httpbin.org/post
リクエストボディ: {"name": "hello_cpp", "version": 1}
ステータスコード: 200
レスポンスボディ:
{
  "data": "{\"name\": \"hello_cpp\", \"version\": 1}",
  "json": {
    "name": "hello_cpp",
    "version": 1
  },
  ...
}
```
