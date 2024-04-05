#!/bin/bash

cmake --preset "test"
cmake --build --preset "test"
cd build/test
ctest -VV