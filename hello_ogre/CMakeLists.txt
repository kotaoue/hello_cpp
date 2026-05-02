cmake_minimum_required(VERSION 3.16)
project(ogre_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    message(FATAL_ERROR
        "OGRE not found.\n"
        "Tried CMAKE_PREFIX_PATH='${CMAKE_PREFIX_PATH}'.\n"
        "Please install OGRE and re-run CMake with one of:\n"
        "  cmake -DOGRE_DIR=<path-to-OGREConfig.cmake-directory> ..\n"
        "  cmake -DCMAKE_PREFIX_PATH=<ogre-prefix> .."
    )
endif()

add_executable(ogre_hello main.cpp)

target_include_directories(ogre_hello PRIVATE ${OGRE_INCLUDE_DIRS})
target_link_libraries(ogre_hello PRIVATE OgreMain OgreBites OgreRTShaderSystem)
