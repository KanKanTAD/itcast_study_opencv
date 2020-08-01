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

add_executable(day2_main1 src/day2_main1.cpp)
add_executable(day2_main2 src/day2_main2.cpp)
add_executable(day2_main3 src/day2_main3.cpp)
add_executable(day2_main4 src/day2_main4.cpp)
add_executable(day2_main5 src/day2_main5.cpp)
add_executable(day2_main6 src/day2_main6.cpp)
add_executable(day2_main7 src/day2_main7.cpp)
add_executable(day2_main8 src/day2_main8.cpp)
add_executable(orb_test src/orb_test1.cpp)
add_executable(orb_bfmatcher src/orb_bfmatcher.cpp)

target_link_libraries( surf_test ${OpenCV_LIBS})
target_link_libraries( sift_test ${OpenCV_LIBS})
target_link_libraries( cv_test_fst ${OpenCV_LIBS})
target_link_libraries( day2_main1 ${OpenCV_LIBS})
target_link_libraries( day2_main2 ${OpenCV_LIBS})
target_link_libraries( day2_main3 ${OpenCV_LIBS})
target_link_libraries( day2_main4 ${OpenCV_LIBS})
target_link_libraries( day2_main5 ${OpenCV_LIBS})
target_link_libraries( day2_main6 ${OpenCV_LIBS})
target_link_libraries( day2_main7 ${OpenCV_LIBS})
target_link_libraries( day2_main8 ${OpenCV_LIBS})
target_link_libraries( orb_test ${OpenCV_LIBS})
target_link_libraries( orb_bfmatcher ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
