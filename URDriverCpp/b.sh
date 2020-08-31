#!/usr/bin/env sh
cmake ./CMakeLists.txt -B ./build/ -G "Unix Makefiles"
cd build && make -j2
cd ..

