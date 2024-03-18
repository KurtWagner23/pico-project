#!/bin/bash

cmake -B out/build-bin -S . -D CMAKE_BUILD_TYPE=Debug
cd out/build-bin
make -j4