cmake_minimum_required(VERSION 3.16)
project(ogre_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(OGRE_HELLO_REQUIRE_OGRE "Fail configure when OGRE is not found" OFF)

# OGRE CMake package の探索パスを拡張
set(_OGRE_HINT_PREFIXES
    "$ENV{OGRE_DIR}"
    "$ENV{OGRE_HOME}"
    "/opt/homebrew"
    "/usr/local"
    "/usr"
    "/usr/lib/OGRE/cmake"
    "/usr/lib/x86_64-linux-gnu/OGRE/cmake"
    "/usr/lib/aarch64-linux-gnu/OGRE/cmake"
)

foreach(_prefix IN LISTS _OGRE_HINT_PREFIXES)
    if(_prefix)
        list(APPEND CMAKE_PREFIX_PATH "${_prefix}")
    endif()
endforeach()

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
