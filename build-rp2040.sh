#!/bin/bash

cmake -B build-rp2040 -S . -D CMAKE_BUILD_TYPE=Debug
cd build-rp2040
make -j4