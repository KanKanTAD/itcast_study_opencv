cmake_minimum_required(VERSION 3.0.0)
project(ur_sim VERSION 0.1.0)
add_compile_options(--std=c++14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Widgets Gui PrintSupport Network)
set(qt5_libs
	Qt5::Core 
	Qt5::Widgets 
	Qt5::Gui
	Qt5::PrintSupport
	Qt5::Network
)
#find_package(OpenCV REQUIRED) 
#message(STATUS "OpenCV library status:")
#message(STATUS "    version: ${OpenCV_VERSION}")
#message(STATUS "    libraries: ${OpenCV_LIBS}")
#message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
 
#include_directories(${OpenCV_INCLUDE_DIRS})
 
add_executable(ur_server src/ur_server.cpp)
add_executable(ur_client_test src/ur_client_test.cpp)

target_link_libraries(ur_server
	${qt5_libs}
	-lpthread -lm
)
target_link_libraries(ur_client_test
	${qt5_libs}
	-lpthread -lm
)



