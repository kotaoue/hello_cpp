#pragma once

/**
 * buffer.hpp — 動的配列バッファ
 *
 * 動的メモリ確保を伴うクラスで「ルール・オブ・ファイブ」を実装する。
 *
 *   1. コンストラクタ       — new[] でヒープにメモリを確保 (RAII)
 *   2. デストラクタ         — delete[] でメモリを解放
 *   3. コピーコンストラクタ  — ディープコピー（独立した配列を作る）
 *   4. コピー代入演算子     — ディープコピー + 自己代入チェック
 *   5. ムーブコンストラクタ  — 所有権を移転してコピーを避ける (noexcept)
 *   6. ムーブ代入演算子     — 所有権を移転 (noexcept)
 */

#include <cstddef>
#include <stdexcept>

class Buffer {
public:
    /// size 個の int 要素を持つバッファを生成する (RAII: ここでメモリ確保)
    explicit Buffer(std::size_t size);

    /// デストラクタ: ヒープメモリを解放する (RAII)
    ~Buffer() noexcept;

    /// コピーコンストラクタ: 独立したディープコピーを作る
    Buffer(const Buffer& other);

    /// コピー代入演算子: ディープコピー + 自己代入ガード
    Buffer& operator=(const Buffer& other);

    /// ムーブコンストラクタ: ポインタの所有権だけを移転する (O(1), noexcept)
    Buffer(Buffer&& other) noexcept;

    /// ムーブ代入演算子: 所有権を移転し、元オブジェクトは空にする (noexcept)
    Buffer& operator=(Buffer&& other) noexcept;

    // ── 要素アクセス ──

    int&       operator[](std::size_t index);
    const int& operator[](std::size_t index) const;

    // ── 状態クエリ ──

    std::size_t size()  const noexcept;
    bool        empty() const noexcept;  ///< ムーブ後は true になる

    // ── 比較演算子 ──

    bool operator==(const Buffer& other) const noexcept;
    bool operator!=(const Buffer& other) const noexcept;

private:
    int*        data_;  ///< ヒープ上の配列
    std::size_t size_;  ///< 要素数
};
