cmake_minimum_required(VERSION 3.16)
project(URDriverCpp)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 自动调用moc，uic，rcc处理qt的扩展部分
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置find__xxx的路径
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qt)

# 设置输出的路径
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/bin" CACHE PATH "Runtime directory" FORCE)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs" CACHE PATH "Library directory" FORCE)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs" CACHE PATH "Archive directory" FORCE)

# qt  plugin
file(
        WRITE
        ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/qt.conf
        "[Paths]
#Prefix=../lib/Qt
#Binaries=bin
#Libraries=lib
Plugins=${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qt/plugins
#Imports=imports
#Qml2Imports=qml"
)
# 加载库
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
# qt加载的库
SET(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES}
        ${Qt5Network_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5Qml_LIBRARIES})
# 指定包含头文件目录
include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS})

#线程 固定配置
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread -Wl,--no-as-needed  -g3 -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# 子目录
add_subdirectory(src)

