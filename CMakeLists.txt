cmake_minimum_required(VERSION 3.8)
project(ood)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
add_subdirectory(lib/Catch2)

add_subdirectory(lab5_cmake)

add_library(lib/Catch2)

target_include_lib(lib/Catch2 ${CMAKE_CURRENT_SOURCE_DIR}/lab5_cmake)