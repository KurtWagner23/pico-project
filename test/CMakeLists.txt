# test/CMakeLists.txt

file(GLOB FILES *.c *.h)
add_executable(test ${FILES})

include(${PROJECT_SOURCE_DIR}/cmake/cmocka.cmake)

target_include_directories(test PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(test PRIVATE cmocka-static)