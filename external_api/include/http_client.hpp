/**
 * http_client.hpp — libcurl を使った HTTP クライアントの C++ 公開 API
 *
 * C 版 (hello_c/external_api/http_client.h) との主な違い:
 *   - struct + 関数群 → クラス (RAII でリソースを自動管理)
 *   - char* + size_t  → std::string (メモリ管理不要)
 *   - 呼び出し元での http_response_free() → デストラクタが自動解放
 */

#pragma once

#include <string>

namespace http {

/**
 * HTTP レスポンスを表す値型。
 *
 * C 版では http_response_free() による手動解放が必要だったが、
 * C++ 版では std::string がデストラクタで自動解放する。
 */
struct Response {
    long        status_code{0}; ///< HTTP ステータスコード。失敗時は -1。
    std::string body;           ///< レスポンスボディ。
};

/**
 * libcurl を RAII でラップした HTTP クライアントクラス。
 *
 * C 版では curl_global_init() / curl_global_cleanup() を
 * main() 内で明示的に呼んでいたが、C++ 版ではコンストラクタと
 * デストラクタがそれぞれ担当するため、呼び忘れが起きない。
 *
 * 使用例:
 * @code
 *   http::Client client;
 *   auto resp = client.get("https://httpbin.org/get");
 *   std::cout << resp.status_code << "\n" << resp.body << "\n";
 * @endcode
 */
class Client {
public:
    /// curl_global_init() を呼び出す。
    Client();

    /// curl_global_cleanup() を呼び出す。
    ~Client();

    // グローバル状態を持つためコピー禁止・ムーブ禁止
    Client(const Client&)            = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&&)                 = delete;
    Client& operator=(Client&&)      = delete;

    /**
     * HTTP GET リクエストを送信する。
     *
     * @param url リクエスト先の URL
     * @return    Response オブジェクト (status_code が -1 の場合は通信エラー)
     */
    Response get(const std::string& url) const;

    /**
     * HTTP POST リクエストを送信する。
     *
     * @param url          リクエスト先の URL
     * @param body         送信するボディ文字列 (例: JSON 文字列)
     * @param content_type Content-Type ヘッダの値 (デフォルト: "application/json")
     * @return             Response オブジェクト (status_code が -1 の場合は通信エラー)
     */
    Response post(const std::string& url,
                  const std::string& body,
                  const std::string& content_type = "application/json") const;
};

} // namespace http
