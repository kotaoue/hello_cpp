/* =========================================================================
 * このファイルは通常 CMock が自動生成します。
 * ここでは CMock の動作を理解するために手書きで作成しています。
 * ========================================================================= */

#include "mock_time_provider.h"
#include "unity.h"
#include "cmock.h"
#include <string.h>

/* --- CMock が生成する内部型 --- */

typedef struct {
    UNITY_LINE_TYPE LineNumber;
    time_t ReturnVal;
} CMOCK_time_provider_get_time_CALL_INSTANCE;

static struct {
    CMOCK_MEM_INDEX_TYPE head;
    CMOCK_MEM_INDEX_TYPE tail;
    int isIgnore;
    time_t ignoreReturn;
} Mock;

/* --- モック管理関数の実装 --- */

void mock_time_provider_Init(void)
{
    CMock_Guts_MemFreeAll();
    memset(&Mock, 0, sizeof(Mock));
    Mock.head = CMOCK_GUTS_NONE;
    Mock.tail = CMOCK_GUTS_NONE;
}

void mock_time_provider_Verify(void)
{
    UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
    if (Mock.isIgnore) { return; }
    if (Mock.head != CMOCK_GUTS_NONE) {
        UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
    }
}

void mock_time_provider_Destroy(void)
{
    CMock_Guts_MemFreeAll();
}

/* --- 期待設定関数の実装 --- */

void time_provider_get_time_ExpectAndReturn(time_t toReturn)
{
    UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
    CMOCK_MEM_INDEX_TYPE idx;
    CMOCK_time_provider_get_time_CALL_INSTANCE *p;

    idx = CMock_Guts_MemNew(sizeof(CMOCK_time_provider_get_time_CALL_INSTANCE));
    p = (CMOCK_time_provider_get_time_CALL_INSTANCE *)CMock_Guts_GetAddressFor(idx);
    UNITY_TEST_ASSERT(p != NULL, cmock_line, CMockStringOutOfMemory);

    p->LineNumber = cmock_line;
    p->ReturnVal  = toReturn;

    Mock.tail = CMock_Guts_MemChain(Mock.tail, idx);
    if (Mock.head == CMOCK_GUTS_NONE) { Mock.head = idx; }
}

void time_provider_get_time_IgnoreAndReturn(time_t toReturn)
{
    Mock.isIgnore    = 1;
    Mock.ignoreReturn = toReturn;
}

/* --- モック本体: 実際のテスト時にリンクされ time_provider.c の代わりに使われる --- */

time_t time_provider_get_time(void)
{
    UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
    CMOCK_time_provider_get_time_CALL_INSTANCE *p;
    time_t ret;

    if (Mock.isIgnore) { return Mock.ignoreReturn; }

    UNITY_TEST_ASSERT(Mock.head != CMOCK_GUTS_NONE, cmock_line, CMockStringCalledMore);

    p = (CMOCK_time_provider_get_time_CALL_INSTANCE *)CMock_Guts_GetAddressFor(Mock.head);
    ret = p->ReturnVal;

    Mock.head = CMock_Guts_MemNext(Mock.head);
    if (Mock.head == CMOCK_GUTS_NONE) { Mock.tail = CMOCK_GUTS_NONE; }

    return ret;
}
