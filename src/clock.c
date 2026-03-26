#include "clock.h"
#include "time_provider.h"
#include <time.h>

const char *clock_get_greeting(void)
{
    time_t now = time_provider_get_time();
    struct tm *t = localtime(&now);
    int hour = t->tm_hour;

    if (hour < 12) {
        return "Good morning";
    } else if (hour < 18) {
        return "Good afternoon";
    } else {
        return "Good evening";
    }
}
