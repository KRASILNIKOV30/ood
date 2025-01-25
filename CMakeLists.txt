cmake_minimum_required(VERSION 3.29.0)
project(ood)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(lab5_cmake)
add_subdirectory(lab7)
add_subdirectory(lab8)
add_subdirectory(lab9)
add_subdirectory(lab10)

add_subdirectory(exam/src)

add_library(catch2 INTERFACE
        exam/src/main.cpp)
add_library(coutBuffer INTERFACE)
target_include_directories(catch2 INTERFACE external/catch2/)
target_include_directories(coutBuffer INTERFACE external/core/)
