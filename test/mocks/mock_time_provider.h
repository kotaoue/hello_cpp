/* =========================================================================
 * このファイルは通常 CMock が自動生成します。
 * 実際には以下のコマンドで生成されます:
 *   ruby vendor/cmock/lib/cmock.rb --mock_path=test/mocks src/time_provider.h
 *
 * ここでは CMock の動作を理解するために手書きで作成しています。
 * ========================================================================= */

#ifndef MOCK_TIME_PROVIDER_H
#define MOCK_TIME_PROVIDER_H

#include "time_provider.h"
#include "cmock.h"

/* --- モックの管理関数 --- */

/* テスト開始前にモックを初期化する */
void mock_time_provider_Init(void);

/* テスト終了後に期待した呼び出しが全て行われたか確認する */
void mock_time_provider_Verify(void);

/* テスト終了後にモックのリソースを解放する */
void mock_time_provider_Destroy(void);

/* --- 期待設定関数 (CMock が生成するインターフェース) --- */

/* 次の呼び出しで toReturn を返すことを期待する */
void time_provider_get_time_ExpectAndReturn(time_t toReturn);

/* 以降の全呼び出しで toReturn を返す (呼び出し回数は問わない) */
void time_provider_get_time_IgnoreAndReturn(time_t toReturn);

#endif /* MOCK_TIME_PROVIDER_H */
