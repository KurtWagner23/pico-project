# test/CMakeLists.txt

file(GLOB FILES *.c *.h)
add_executable(test-runner ${FILES})

include(${PROJECT_SOURCE_DIR}/cmake/cmocka.cmake)

set_target_properties( test-runner
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(test-runner PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(test-runner PRIVATE cmocka-static)