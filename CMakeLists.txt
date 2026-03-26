cmake_minimum_required(VERSION 3.16)
project(hello_cpp_tests C)

set(CMAKE_C_STANDARD 11)

# --- インクルードパス ---

set(UNITY_SRC_DIR  ${CMAKE_SOURCE_DIR}/vendor/unity/src)
set(CMOCK_SRC_DIR  ${CMAKE_SOURCE_DIR}/vendor/cmock/src)
set(SRC_DIR        ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR       ${CMAKE_SOURCE_DIR}/test)
set(MOCK_DIR       ${CMAKE_SOURCE_DIR}/test/mocks)

# --- Unity ライブラリ ---

add_library(unity STATIC
    ${UNITY_SRC_DIR}/unity.c
)
target_include_directories(unity PUBLIC ${UNITY_SRC_DIR})

# --- CMock ライブラリ ---

add_library(cmock STATIC
    ${CMOCK_SRC_DIR}/cmock.c
)
target_include_directories(cmock PUBLIC ${CMOCK_SRC_DIR} ${UNITY_SRC_DIR})
target_link_libraries(cmock PUBLIC unity)

# --- プロダクションコード ---

add_library(calculator STATIC ${SRC_DIR}/calculator.c)
target_include_directories(calculator PUBLIC ${SRC_DIR})

add_library(clock STATIC ${SRC_DIR}/clock.c)
target_include_directories(clock PUBLIC ${SRC_DIR})

# --- テスト 1: Unity を使った calculator のテスト ---

add_executable(test_calculator
    ${TEST_DIR}/test_calculator.c
    ${SRC_DIR}/calculator.c
)
target_include_directories(test_calculator PRIVATE ${SRC_DIR} ${UNITY_SRC_DIR})
target_link_libraries(test_calculator PRIVATE unity)

# --- テスト 2: CMock を使った clock のテスト (time_provider をモック化) ---

add_executable(test_clock
    ${TEST_DIR}/test_clock.c
    ${SRC_DIR}/clock.c
    ${MOCK_DIR}/mock_time_provider.c   # モック (time_provider.c の代わり)
)
target_include_directories(test_clock PRIVATE
    ${SRC_DIR}
    ${UNITY_SRC_DIR}
    ${CMOCK_SRC_DIR}
    ${MOCK_DIR}
)
target_link_libraries(test_clock PRIVATE unity cmock)

# --- CTest 登録 ---

enable_testing()
add_test(NAME calculator_tests COMMAND test_calculator)
add_test(NAME clock_tests      COMMAND test_clock)
