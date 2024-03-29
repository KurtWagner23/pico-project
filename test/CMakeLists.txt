# test/CMakeLists.txt

set(EXECUTABLE_NAME tests)

include(${PROJECT_SOURCE_DIR}/cmake/cmocka.cmake)

add_subdirectory(prototypes)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
# remove main.c in src-directory and also lcd.c, because we are not testing the LCD-Module
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.c)
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/lcd.c)
add_library(src ${SOURCE_FILES})
target_link_libraries(src prototypes)


add_cmocka_test(${EXECUTABLE_NAME}
                SOURCES main.c mocks.c
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES src cmocka-static
)

# add_executable(${EXECUTABLE_NAME} main.c)
# target_link_libraries(${EXECUTABLE_NAME} mocks src cmock-static)
set_property(TARGET ${EXECUTABLE_NAME}
             PROPERTY LINK_FLAGS
             "${DEFAULT_LINK_FLAGS} -Wl,--wrap=i2c_write_blocking,--wrap=i2c_read_blocking"
)

set_target_properties(  ${EXECUTABLE_NAME}
                        PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
                        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
                        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

include_directories(${EXECUTABLE_NAME} ../src)
include_directories(${EXECUTABLE_NAME} prototypes)


enable_testing()


add_test(test_lis3 ${EXECUTABLE_NAME})