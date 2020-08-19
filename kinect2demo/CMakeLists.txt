cmake_minimum_required(VERSION 3.0.0)

project(k_demo VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/tad/opencv_build/pkg3.4.1/share/OpenCV/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/tad/Software/dist-libfreenect2-v0.2.0/lib/cmake/freenect2/)
set(OpenCV_DIR /home/tad/opencv_build/pkg3.4.1/)
find_package(OpenCV REQUIRED)
find_package(freenect2 REQUIRED)
message(STATUS "freenect2 library status:")
message(STATUS "freenect2_VERSION:" ${freenect2_VERSION})
message(STATUS "freenect2_INCLUDE_DIRS:" ${freenect2_INCLUDE_DIRS})
message(STATUS "freenect2_LIBRARIES:" ${freenect2_LIBRARIES})
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
 
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${freenect2_INCLUDE_DIRS})
 
#target_link_libraries(cv_test_tri ${OpenCV_LIBS})
add_executable(demo_1 src/demo_1.cpp)
target_link_libraries(demo_1 
	${OpenCV_LIBS}
	${freenect2_LIBRARIES} 
)



