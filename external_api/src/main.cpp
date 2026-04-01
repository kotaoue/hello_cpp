/**
 * main.cpp — 外部 API 接続サンプル (C++ 版)
 *
 * C 版 (hello_c/external_api/main.c) と同じく httpbin.org を使い、
 * HTTP GET / POST リクエストを実際に送信してレスポンスを表示する。
 *
 * C 版との主な違い:
 *   - curl_global_init / curl_global_cleanup → http::Client のコンストラクタ/デストラクタ
 *   - HttpResponse* (ポインタ) + http_response_free() → Response (値型)、自動解放
 *   - printf / fprintf → std::cout / std::cerr
 *
 * httpbin.org は HTTP リクエストをそのままエコーバックする
 * テスト用の公開 API サービス。
 *   GET  https://httpbin.org/get   → リクエスト情報を JSON で返す
 *   POST https://httpbin.org/post  → 送信したボディを JSON で返す
 */

#include "http_client.hpp"

#include <iostream>
#include <string>

// ------------------------------------------------------------------ //
// デモ関数                                                              //
// ------------------------------------------------------------------ //

/** GET リクエストのデモ */
static void demo_get(const http::Client& client)
{
    const std::string url = "https://httpbin.org/get";

    std::cout << "\n--- GET リクエスト ---\n";
    std::cout << "URL: " << url << "\n";

    const auto resp = client.get(url);

    std::cout << "ステータスコード: " << resp.status_code << "\n";
    std::cout << "レスポンスボディ:\n"
              << (resp.body.empty() ? "(empty)" : resp.body) << "\n";
}

/** POST リクエストのデモ */
static void demo_post(const http::Client& client)
{
    const std::string url  = "https://httpbin.org/post";
    const std::string body = R"({"name": "hello_cpp", "version": 1})";

    std::cout << "\n--- POST リクエスト ---\n";
    std::cout << "URL:              " << url  << "\n";
    std::cout << "リクエストボディ: " << body << "\n";

    const auto resp = client.post(url, body, "application/json");

    std::cout << "ステータスコード: " << resp.status_code << "\n";
    std::cout << "レスポンスボディ:\n"
              << (resp.body.empty() ? "(empty)" : resp.body) << "\n";
}

// ------------------------------------------------------------------ //
// エントリポイント                                                       //
// ------------------------------------------------------------------ //

int main()
{
    // http::Client のコンストラクタが curl_global_init() を呼ぶ。
    // C 版のように main() で明示的に呼ぶ必要がなく、
    // スコープを抜けると自動的に curl_global_cleanup() が実行される。
    const http::Client client;

    demo_get(client);
    demo_post(client);

    return 0;
}
