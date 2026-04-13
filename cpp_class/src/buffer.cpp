/**
 * buffer.cpp — Buffer クラスの実装（ルール・オブ・ファイブ）
 */

#include "buffer.hpp"

#include <algorithm>  // std::copy, std::equal

// ─── コンストラクタ: メモリ確保 (RAII) ───────────────────────────

Buffer::Buffer(std::size_t size)
    : data_(new int[size]{}),  // value-initialize (ゼロ埋め)
      size_(size)
{
}

// ─── デストラクタ: メモリ解放 ────────────────────────────────────

Buffer::~Buffer() noexcept
{
    delete[] data_;
}

// ─── コピーコンストラクタ: ディープコピー ─────────────────────────

Buffer::Buffer(const Buffer& other)
    : data_(new int[other.size_]),
      size_(other.size_)
{
    std::copy(other.data_, other.data_ + size_, data_);
}

// ─── コピー代入演算子: ディープコピー + 自己代入ガード ─────────────

Buffer& Buffer::operator=(const Buffer& other)
{
    if (this == &other) {
        return *this;  // 自己代入は何もしない
    }

    // 新しいメモリを確保してからコピー（例外安全性のため先に確保）
    int* new_data = new int[other.size_];
    std::copy(other.data_, other.data_ + other.size_, new_data);

    delete[] data_;   // 古いメモリを解放
    data_ = new_data;
    size_ = other.size_;
    return *this;
}

// ─── ムーブコンストラクタ: 所有権の移転 (O(1), noexcept) ──────────

Buffer::Buffer(Buffer&& other) noexcept
    : data_(other.data_),
      size_(other.size_)
{
    // 移転元を「空」の状態にする（二重解放を防ぐ）
    other.data_ = nullptr;
    other.size_ = 0;
}

// ─── ムーブ代入演算子: 所有権の移転 (noexcept) ────────────────────

Buffer& Buffer::operator=(Buffer&& other) noexcept
{
    if (this == &other) {
        return *this;
    }

    delete[] data_;       // 自分のメモリを解放

    data_ = other.data_;  // 所有権を受け取る
    size_ = other.size_;

    other.data_ = nullptr;  // 移転元を「空」にする
    other.size_ = 0;
    return *this;
}

// ─── 要素アクセス ────────────────────────────────────────────────

int& Buffer::operator[](std::size_t index)
{
    if (index >= size_) {
        throw std::out_of_range("Buffer: index out of range");
    }
    return data_[index];
}

const int& Buffer::operator[](std::size_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Buffer: index out of range");
    }
    return data_[index];
}

// ─── 状態クエリ ──────────────────────────────────────────────────

std::size_t Buffer::size() const noexcept
{
    return size_;
}

bool Buffer::empty() const noexcept
{
    return size_ == 0;
}

// ─── 比較演算子 ──────────────────────────────────────────────────

bool Buffer::operator==(const Buffer& other) const noexcept
{
    if (size_ != other.size_) {
        return false;
    }
    return std::equal(data_, data_ + size_, other.data_);
}

bool Buffer::operator!=(const Buffer& other) const noexcept
{
    return !(*this == other);
}
