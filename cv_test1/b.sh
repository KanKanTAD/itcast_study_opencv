#!/usr/bin/env sh
cmake ./CMakeLists.txt -B ./build/ -G "Unix Makefiles" -D CMAKE_EXPORT_COMPILE_COMMANDS=ON 
cd ./build/ 
make -j2
cd ..

