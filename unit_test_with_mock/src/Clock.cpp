#include "Clock.h"
#include <ctime>

Clock::Clock(const ITimeProvider& timeProvider)
    : timeProvider_(timeProvider) {}

std::string Clock::greeting() const {
    std::time_t t = timeProvider_.now();
    std::tm* lt = std::localtime(&t);
    if (lt == nullptr) {
        return "Good morning";
    }
    int hour = lt->tm_hour;

    if (hour < 12) {
        return "Good morning";
    } else if (hour < 18) {
        return "Good afternoon";
    } else {
        return "Good evening";
    }
}
