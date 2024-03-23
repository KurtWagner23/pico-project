#!/bin/bash

cmake -B build-tests -S . -D BUILD_TESTS=ON -D SW_TESTS=ON
cd build-tests
make