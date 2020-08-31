#!/usr/bin/env sh
PWD=$(pwd)
cmake ./CMakeLists.txt -B ./build/ -G "Unix Makefiles" && cd build && make -j2
cd $PWD

