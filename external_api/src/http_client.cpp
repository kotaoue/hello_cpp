/**
 * http_client.cpp — libcurl を使った HTTP GET / POST の C++ 実装
 *
 * C 版 (hello_c/external_api/http_client.c) との主な違い:
 *   - write_callback の userdata に Buffer* ではなく std::string* を渡す
 *     → realloc / memcpy が不要になり、std::string::append に置き換わる
 *   - CURL ハンドルを std::unique_ptr で管理し、解放忘れを防ぐ
 *   - HTTP ヘッダリストを curl_slist の RAII ラッパーで管理する
 */

#include "http_client.hpp"

#include <curl/curl.h>
#include <iostream>
#include <memory>
#include <string>

namespace http {

// ------------------------------------------------------------------ //
// 内部ユーティリティ                                                    //
// ------------------------------------------------------------------ //

namespace {

/**
 * libcurl の CURLOPT_WRITEFUNCTION に渡すコールバック。
 *
 * C 版では realloc + memcpy で動的バッファに追記していたが、
 * C++ 版では userdata を std::string* として受け取り、
 * std::string::append() に置き換える。
 */
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    const size_t total = size * nmemb;
    auto* buf = static_cast<std::string*>(userdata);
    buf->append(ptr, total);
    return total;
}

/// curl_easy_cleanup を呼ぶカスタムデリータ
struct CurlEasyDeleter {
    void operator()(CURL* handle) const noexcept { curl_easy_cleanup(handle); }
};
using CurlHandle = std::unique_ptr<CURL, CurlEasyDeleter>;

/// curl_slist_free_all を呼ぶカスタムデリータ
struct CurlSlistDeleter {
    void operator()(curl_slist* list) const noexcept { curl_slist_free_all(list); }
};
using CurlSlist = std::unique_ptr<curl_slist, CurlSlistDeleter>;

/**
 * 設定済みの CURL ハンドルでリクエストを実行し、Response を返す。
 *
 * C 版の perform_request() に相当するが、戻り値が Response (値型) のため
 * 呼び出し元でのポインタ解放が不要になっている。
 */
Response perform_request(CURL* curl)
{
    Response resp;
    std::string body_buf;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &body_buf);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // リダイレクト追従
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,        10L); // タイムアウト 10 秒

    const CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl error: " << curl_easy_strerror(res) << "\n";
        resp.status_code = -1;
        return resp;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp.status_code);
    resp.body = std::move(body_buf);
    return resp;
}

} // namespace (anonymous)

// ------------------------------------------------------------------ //
// Client メンバー関数                                                   //
// ------------------------------------------------------------------ //

Client::Client()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

Client::~Client()
{
    curl_global_cleanup();
}

Response Client::get(const std::string& url) const
{
    CurlHandle curl{curl_easy_init()};
    if (!curl) {
        return Response{-1, {}};
    }

    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    return perform_request(curl.get());
}

Response Client::post(const std::string& url,
                      const std::string& body,
                      const std::string& content_type) const
{
    CurlHandle curl{curl_easy_init()};
    if (!curl) {
        return Response{-1, {}};
    }

    // Content-Type ヘッダを設定する
    // C 版では malloc + snprintf で文字列を組み立てていたが、
    // C++ 版では std::string の連結で同じことができる。
    CurlSlist headers{
        curl_slist_append(nullptr, ("Content-Type: " + content_type).c_str())
    };
    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headers.get());
    curl_easy_setopt(curl.get(), CURLOPT_URL,        url.c_str());
    // CURLOPT_COPYPOSTFIELDS を使うことで libcurl がボディを内部にコピーし、
    // body の文字列ライフタイムに依存しなくなる。
    curl_easy_setopt(curl.get(), CURLOPT_COPYPOSTFIELDS, body.c_str());

    return perform_request(curl.get());
}

} // namespace http
