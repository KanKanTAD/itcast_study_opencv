cmake_minimum_required(VERSION 3.0.0)
project(aubo_robot_project VERSION 0.1.0)
add_compile_options(--std=c++14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread -Wl,--no-as-needed  -g3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/bin" CACHE PATH "Runtime directory" FORCE)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs" CACHE PATH "Library directory" FORCE)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs" CACHE PATH "Archive directory" FORCE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/tad/Software/aubo-i5-linux-sdk/cmake/linux_x64/)

find_package(AuBo REQUIRED)

message(STATUS "AuBoSDK library status:")
message(STATUS ${AuBo_INCLUDE_DIRS})
message(STATUS ${AuBo_LINK_DIRS})

find_package(Qt5 COMPONENTS Core Widgets Gui PrintSupport)
set(qt5_libs
	Qt5::Core 
	Qt5::Widgets 
	Qt5::Gui
	Qt5::PrintSupport
)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
 
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${AuBo_INCLUDE_DIRS})

link_directories(${AuBo_LINK_DIRS})
 
add_executable(simple_test src/test.cpp)

target_link_libraries(simple_test
	${qt5_libs}
	${AuBo_LIBRARIES}
)

add_executable(main src/main.cpp src/MainWindow.cpp src/Paintor.cpp)

target_link_libraries(main
	${qt5_libs}
	${AuBo_LIBRARIES}
)
