# Top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

OPTION(BUILD_TESTS "Build the test binary" OFF)
if(BUILD_TESTS)
  project(test)
  enable_language(C CXX ASM)
  add_subdirectory(./test)
else()
  set(PICO_SDK_FETCH_FROM_GIT on)
  include(cmake/pico_sdk_import.cmake)
  project(test)
  pico_sdk_init()
  enable_language(C CXX ASM)
  add_subdirectory(./src)
endif()

