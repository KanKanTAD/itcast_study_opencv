cmake_minimum_required(VERSION 3.0.0)
project(cv_test_fst VERSION 0.1.0)
add_compile_options(--std=c++14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/tad/opencv_build/pkg3.4.1/share/OpenCV/)
find_package(OpenCV  REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
 
include_directories(${OpenCV_INCLUDE_DIRS})
 
 
add_executable(cv_test_fst src/main.cpp)
add_executable(sift_test src/sift_test1.cpp)
add_executable(surf_test src/surf_test1.cpp)
add_executable(orb_test src/orb_test1.cpp)
add_executable(orb_bfmatcher src/orb_bfmatcher.cpp)
add_executable(detect_jiguang src/detect_jiguang.cpp)

target_link_libraries( surf_test ${OpenCV_LIBS})
target_link_libraries( sift_test ${OpenCV_LIBS})
target_link_libraries( cv_test_fst ${OpenCV_LIBS})
target_link_libraries( orb_test ${OpenCV_LIBS})
target_link_libraries( orb_bfmatcher ${OpenCV_LIBS})
target_link_libraries( detect_jiguang ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
