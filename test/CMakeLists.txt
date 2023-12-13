# test/CMakeLists.txt

file(GLOB FILES *.c *.h)
add_executable(test ${FILES})

include(../cmake/cmocka.cmake)

target_link_libraries(test PRIVATE cmocka-static)