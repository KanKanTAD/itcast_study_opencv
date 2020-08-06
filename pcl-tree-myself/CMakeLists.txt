cmake_minimum_required(VERSION 3.0.0)

project(kd-tree VERSION 0.1.0)
add_compile_options(--std=c++14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(kd-tree-1 src/kd-tree-1.cpp)

add_executable(octree-1 src/octree-1.cpp)
