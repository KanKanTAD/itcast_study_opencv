cmake_minimum_required(VERSION 3.0.0)

project(paint_svg VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)


find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread )


include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test src/test.cpp)
target_link_libraries(test 
	${Boost_LIBRARIES}
	${OpenCV_LIBS}
)
