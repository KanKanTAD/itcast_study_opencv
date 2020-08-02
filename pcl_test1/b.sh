#!/usr/bin/env sh
cmake ./CMakeLists.txt -B build \
	-G "Unix Makefiles" \
	-D CMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-D BUILD_TYPE=Debug
cd build && make
cd ..

