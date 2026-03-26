#ifndef TIME_PROVIDER_H
#define TIME_PROVIDER_H

#include <time.h>

/*
 * time() のラッパーインターフェース。
 * CMock でモック化するために関数ポインタを使って差し替え可能にしている。
 */
time_t time_provider_get_time(void);

#endif /* TIME_PROVIDER_H */
