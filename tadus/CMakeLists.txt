cmake_minimum_required(VERSION 3.0.0)

project(tadus VERSION 0.1.0)
add_compile_options(--std=c++14)
#add_compile_options(-pthread)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
find_package(GTest REQUIRED)
find_package(Threads )

message("GTEST_FOUND--" GTEST_FOUND)
include_directories(
	include
	${GTEST_INCLUDE_DIRS}
)

add_executable(gtest_demo_1 test/gtest_demo.cc)
target_link_libraries(gtest_demo_1
	${GTEST_BOTH_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)


#add_executable(foo foo.cc)
#add_library(foo foo.h)
#target_link_libraries(foo ${GTEST_BOTH_LIBRARIES})
#add_test(AllTestsInFoo foo)
#GTEST_ADD_TESTS(FooTest "${FooTestArgs}" FooUnitTest.cc)


add_test(NAME gtest_demo_1 COMMAND gtest_demo_1)
