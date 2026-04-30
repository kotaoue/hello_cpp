cmake_minimum_required(VERSION 3.16)
project(ogre_hello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ubuntu では /usr/lib/x86_64-linux-gnu/OGRE/cmake 等にある
# CMake config を検索パスに追加
list(APPEND CMAKE_MODULE_PATH
    "/usr/lib/OGRE/cmake"
    "/usr/lib/x86_64-linux-gnu/OGRE/cmake"
    "/usr/lib/aarch64-linux-gnu/OGRE/cmake"
)

find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem)

add_executable(ogre_hello main.cpp)

target_include_directories(ogre_hello PRIVATE ${OGRE_INCLUDE_DIRS})
target_link_libraries(ogre_hello PRIVATE OgreMain OgreBites OgreRTShaderSystem)
