cmake_minimum_required(VERSION 3.29.0)
project(ood)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(lab5_cmake)
add_subdirectory(lab7)

add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE external/catch2/)
add_executable(slides lab7/slides/main.cpp lab7/slides/main.h)
