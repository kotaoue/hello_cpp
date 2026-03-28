#pragma once

#include <ctime>

// 現在時刻を返すインターフェース。
// Google Mock でモック化するための純粋仮想クラス。
class ITimeProvider {
public:
    virtual ~ITimeProvider() = default;
    virtual std::time_t now() const = 0;
};
