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

if(APPLE)
    # macOS (Homebrew): brew --prefix ogre で正確なインストール先を取得
    execute_process(
        COMMAND brew --prefix ogre
        OUTPUT_VARIABLE _brew_ogre_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_VARIABLE _brew_error
        RESULT_VARIABLE _brew_result
    )
    if(_brew_result EQUAL 0 AND NOT _brew_ogre_prefix STREQUAL "")
        list(APPEND CMAKE_PREFIX_PATH "${_brew_ogre_prefix}")
        message(STATUS "Homebrew OGRE prefix: ${_brew_ogre_prefix}")
    elseif(_brew_error)
        message(STATUS "brew --prefix ogre: ${_brew_error}")
    endif()
elseif(UNIX)
    # Ubuntu / Debian: アーキテクチャ別ライブラリディレクトリを追加
    list(APPEND CMAKE_PREFIX_PATH
        "/usr/lib/x86_64-linux-gnu"
        "/usr/lib/aarch64-linux-gnu"
    )
endif()

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

add_executable(ogre_hello main.cpp)

target_include_directories(ogre_hello PRIVATE ${OGRE_INCLUDE_DIRS})
target_link_libraries(ogre_hello PRIVATE OgreMain OgreBites OgreRTShaderSystem)
