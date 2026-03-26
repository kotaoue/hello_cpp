#include "time_provider.h"

time_t time_provider_get_time(void)
{
    return time(NULL);
}
