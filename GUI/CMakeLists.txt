cmake_minimum_required(VERSION 3.16)

project(GUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(GUI main.cpp gamewindow.cpp gamewindow.h)

target_include_directories(GUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../includes)

target_link_libraries(GUI PRIVATE Qt6::Widgets)