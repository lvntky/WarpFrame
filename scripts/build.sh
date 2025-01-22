#!/bin/bash
cd ./build
conan install .. --build=missing --output-folder=./
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
