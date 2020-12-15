project(RARBrutForce)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(EXISTS cmake-build-debug/conanbuildinfo.cmake) #Clion, with conanbuildinfo.cmake in root
    include(build/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
endif()
conan_basic_setup()

set(SRC ./src)

add_executable(RarBrutForce)

target_sources(RarBrutForce PUBLIC
    ${SRC}/main.cpp
    ${SRC}/ArgParser.cpp
    ${SRC}/WinrarBrutForcer.cpp
)

target_include_directories(RarBrutForce PUBLIC
    ./include
)

target_compile_options(RarBrutForce PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /MD -D_WIN32_WINNT=0x0A00 /D_ITERATOR_DEBUG_LEVEL=0 /permissive- /TP /std:c++17>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>: -Wall -Werror>
)