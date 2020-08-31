include_directories(../driver/)

add_executable(simple_test_urdata simple_test_urdata.cpp)
target_link_libraries(simple_test_urdata driver)

add_executable(simple_test_1 simple_test_1.cpp)
target_link_libraries(simple_test_1 driver)

add_executable(test main.cpp MainWindow.cpp)
target_link_libraries(
        test
        ${QT_LIBRARIES}
		driver
)
