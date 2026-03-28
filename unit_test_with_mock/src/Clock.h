#pragma once

#include "ITimeProvider.h"
#include <string>

// 現在時刻に応じた挨拶を返すクラス。
// ITimeProvider を依存注入することで、テスト時にモックへ差し替えられる。
//
//   0〜11時 : "Good morning"
//  12〜17時 : "Good afternoon"
//  18〜23時 : "Good evening"
class Clock {
public:
    explicit Clock(const ITimeProvider& timeProvider);
    std::string greeting() const;

private:
    const ITimeProvider& timeProvider_;
};
