cmake_minimum_required(VERSION 3.16)
project(ogre_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(OGRE_HELLO_REQUIRE_OGRE "Fail configure when OGRE is not found" OFF)

# ── OGRE CMake package の探索パスを拡張 ─────────────────────────────

# 環境変数ヒント
foreach(_env_var OGRE_DIR OGRE_HOME)
    if(DEFINED ENV{${_env_var}} AND NOT "$ENV{${_env_var}}" STREQUAL "")
        list(APPEND CMAKE_PREFIX_PATH "$ENV{${_env_var}}")
    endif()
endforeach()

# macOS ソースビルド時の一般的なインストール先を追加
list(APPEND CMAKE_PREFIX_PATH
    "$ENV{HOME}/ogre-dist"
    "/usr/local"
    "/opt/ogre"
)

find_package(OGRE QUIET CONFIG COMPONENTS Bites RTShaderSystem)

if(NOT OGRE_FOUND)
    string(CONCAT _ogre_message
        "OGRE not found.\n"
        "Tried CMAKE_PREFIX_PATH='${CMAKE_PREFIX_PATH}'.\n"
        "Install OGRE and re-run with one of:\n"
        "  cmake -DOGRE_DIR=<path-to-OGREConfig.cmake-directory> ..\n"
        "  cmake -DCMAKE_PREFIX_PATH=<ogre-prefix> .."
    )

    if(OGRE_HELLO_REQUIRE_OGRE)
        message(FATAL_ERROR "${_ogre_message}")
    else()
        message(WARNING "${_ogre_message}\nSkipping ogre_hello target.")
        return()
    endif()
endif()

add_executable(ogre_hello
    main.cpp
    src/scene_components.cpp
)

# plugins.cfg を生成してビルドディレクトリに配置
# OGRE のプラグイン実体がある RelWithDebInfo/ を優先し、なければ lib/OGRE/ にフォールバック
if(EXISTS "${OGRE_PREFIX_DIR}/lib/RelWithDebInfo")
    set(OGRE_PLUGIN_DIR "${OGRE_PREFIX_DIR}/lib/RelWithDebInfo")
else()
    set(OGRE_PLUGIN_DIR "${OGRE_PREFIX_DIR}/lib/OGRE")
endif()
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/plugins.cfg.in"
    "${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg"
    @ONLY
)


target_include_directories(ogre_hello PRIVATE
    ${OGRE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(ogre_hello PRIVATE OgreMain OgreBites OgreRTShaderSystem)
