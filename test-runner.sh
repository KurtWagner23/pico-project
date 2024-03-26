#!/bin/bash

cmake --preset "test"
cmake --build --preset "test"
cd build/test/bin
./tests