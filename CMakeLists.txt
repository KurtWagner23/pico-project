# Top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

# Define a CMake variable to control the inclusion of certain headers
option(SW_TESTS "Exclude certain headers" OFF)
OPTION(BUILD_TESTS "Build the test binary" OFF)

if(SW_TESTS)
    add_compile_definitions(SW_TESTS)
endif()

if(BUILD_TESTS)
  project(test)
  enable_language(C CXX ASM)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_CXX_STANDARD 17)
  add_subdirectory(test)
else()
  set(PICO_SDK_FETCH_FROM_GIT on)
  include(cmake/pico_sdk_import.cmake)
  project(main)
  pico_sdk_init()
  enable_language(C CXX ASM)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_CXX_STANDARD 17)
  # Add a compilation subdirectory
  add_subdirectory(src)
  #add_subdirectory(test)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Infrared)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Icm20948)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/LCD)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Fonts)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Config)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/GUI)
  #add_subdirectory(external/Pico-LCD-1.14/c/examples)


endif()

