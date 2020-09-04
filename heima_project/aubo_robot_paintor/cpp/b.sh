#!/usr/bin/env sh
PWD=$(pwd)
cmake ./CMakeLists.txt -B build -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd build && make -j2
cd ${PWD} 

