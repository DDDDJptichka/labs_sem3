cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)
add_executable(tests tests.cpp)
add_executable(benchmark benchmark.cpp)

target_link_libraries(tests PRIVATE gtest_main)