cmake_minimum_required(VERSION 3.0.0)

project(pcl_proj VERSION 0.1.0)
add_compile_options(--std=c++17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}:/home/tad/Public/pcl/pcl_builds/pkg1.7.2/share/pcl-1.7/)
find_package(PCL REQUIRED)

message(${PCL_FOUND})

include_directories(
	include 
	${PCL_INCLUDE_DIR}
)
link_directories(${PCL_LIBRARIE_DIRS})

add_executable(01_demo src/01_feature.cpp)
target_link_libraries(01_demo ${PCL_LIBRARIES})

add_executable(02_demo src/02_resampling.cpp)
target_link_libraries(02_demo ${PCL_LIBRARIES})

add_executable(03_contain src/03_contain.cpp)
target_link_libraries(03_contain ${PCL_LIBRARIES})
