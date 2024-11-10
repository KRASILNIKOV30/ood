cmake_minimum_required(VERSION 3.0.0)
project(ood)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(lab5_cmake)
add_subdirectory(lab6)

add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE external/catch2/)
