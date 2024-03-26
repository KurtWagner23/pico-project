#!/bin/bash

cmake --preset "rp2040"
cmake --build --preset "rp2040"
cd build/test/bin
./tests