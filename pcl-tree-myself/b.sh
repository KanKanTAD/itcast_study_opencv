#!/usr/bin/env sh
cmake ./CMakeLists.txt -B build -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd build && make
cd ..

