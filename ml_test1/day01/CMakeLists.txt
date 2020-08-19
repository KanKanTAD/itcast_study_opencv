cmake_minimum_required(VERSION 3.0.0)

project(cv_test_tri VERSION 0.1.0)
add_compile_options(--std=c++14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(day01_knn src/day01_knn.cpp)

