cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(cv_test_tri VERSION 0.1.0)
add_compile_options(--std=c++2a)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(range_1 src/range_for_1.cpp )


