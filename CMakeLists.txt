# Top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.20)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()


# variable for including certain headers, when defined
option(SW_TESTS "Exclude certain headers" OFF)
if(SW_TESTS)
  add_compile_definitions(SW_TESTS)
endif()

# Variable controls whether Unit-Tests or Binaries for RPI Pico get configured
OPTION(BUILD_TESTS "Build the test binary" OFF)
if(BUILD_TESTS)
  project(test)
  enable_language(C ASM)
  set(CMAKE_C_STANDARD 11)
  enable_testing()
  add_subdirectory(test)
else()
  set(PICO_SDK_FETCH_FROM_GIT on)
  include(cmake/pico_sdk_import.cmake)
  project(main)
  pico_sdk_init()
  enable_language(C ASM)
  set(CMAKE_C_STANDARD 11)
  add_subdirectory(src)
  # Include directories from external LCD-Driver library
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Infrared)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Icm20948)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/LCD)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Fonts)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/Config)
  add_subdirectory(external/Pico-LCD-1.14/c/lib/GUI)
endif()

