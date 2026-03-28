#pragma once

#include "ITimeProvider.h"
#include <ctime>

// 実際のシステム時刻を返す実装
class SystemTimeProvider : public ITimeProvider {
public:
    std::time_t now() const override {
        return std::time(nullptr);
    }
};
