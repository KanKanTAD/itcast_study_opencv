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
add_executable(gtest_tadus_str_alg test/tadus_str_alg_test.cc)
add_executable(gtest_tadus_functional test/tadus_functional_test.cc)

target_link_libraries(gtest_demo_1
	${GTEST_BOTH_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
target_link_libraries(gtest_tadus_str_alg
	${GTEST_BOTH_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
target_link_libraries(gtest_tadus_functional
	${GTEST_BOTH_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)


#add_executable(foo foo.cc)
#add_library(foo foo.h)
#target_link_libraries(foo ${GTEST_BOTH_LIBRARIES})
#add_test(AllTestsInFoo foo)
#GTEST_ADD_TESTS(FooTest "${FooTestArgs}" FooUnitTest.cc)


add_test(NAME Alltests COMMAND gtest_demo_1 gtest_tadus_functional gtest_tadus_str_alg)
add_test(NAME tadus_str_alg_test COMMAND gtest_tadus_str_alg)
add_test(NAME tadus_str_alg_test COMMAND gtest_tadus_functional)
