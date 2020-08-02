cmake_minimum_required(VERSION 3.0.0)

project(pcl_proj VERSION 0.1.0)
add_compile_options(--std=c++14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PCL REQUIRED)

message(${PCL_FOUND})

include_directories(${PCL_INCLUDE_DIR})
link_directories(${PCL_LIBRARIE_DIRS})

#target_link_libraries(pcl_proj ${PCL_LIBRARIES})


add_executable(fst src/fst.cpp)
add_executable(snd src/snd.cpp)


target_link_libraries(fst ${PCL_LIBRARIES})
target_link_libraries(snd ${PCL_LIBRARIES})
