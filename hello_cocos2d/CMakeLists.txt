cmake_minimum_required(VERSION 3.16)

if(APPLE AND NOT IOS AND CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64" AND NOT DEFINED CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architecture for Cocos2d-x macOS prebuilts" FORCE)
endif()

project(HelloCocos2dx CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cocos2d-x のルートディレクトリ（デフォルト: このディレクトリの隣の cocos2d-x/）
if(NOT DEFINED COCOS2DX_ROOT_PATH)
    set(COCOS2DX_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cocos2d-x")
endif()

set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

# macOS での iconv コンパイルエラーを回避するため、エラーを警告に変換
if(APPLE)
    # すべてのエラーを警告に変換
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")
endif()

# Cocos2d-x では iconv を使用するが、macOS SDK の最新版では型の問題がある
# iconv を使用しないようにマークしておく（UI フォント対応を無効化）
set(USE_COCOS_FREETYPE OFF CACHE BOOL "Disable FreeType to avoid iconv issues" FORCE)
set(COCOS2D_BUILD_WITH_FREETYPE OFF CACHE BOOL "Disable FreeType" FORCE)
set(ENABLE_ICONV OFF CACHE BOOL "Disable iconv" FORCE)
set(ICONV_FOUND FALSE CACHE BOOL "Mark iconv as not found" FORCE)

include(CocosBuildSet)

set(BUILD_LUA_LIBS OFF)
set(BUILD_JS_LIBS OFF)

add_subdirectory(
    ${COCOS2DX_ROOT_PATH}/cocos
    ${ENGINE_BINARY_PATH}/cocos/core
)

set(APP_HEADER_FILES
    Classes/AppDelegate.h
    Classes/HelloWorldScene.h
)

set(APP_SOURCE_FILES
    main.cpp
    Classes/AppDelegate.cpp
    Classes/HelloWorldScene.cpp
    iconv_stub.cpp
)

add_executable(${PROJECT_NAME}
    ${APP_HEADER_FILES}
    ${APP_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} cocos2d)
target_include_directories(${PROJECT_NAME} PRIVATE Classes)
