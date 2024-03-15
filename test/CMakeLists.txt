# test/CMakeLists.txt

set(EXECUTABLE_NAME tests)

include(${PROJECT_SOURCE_DIR}/cmake/cmocka.cmake)

file(GLOB MOCK_FILES ${PROJECT_SOURCE_DIR}/test/mocks/*.c)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

# remove main.c in src-directory and also lcd.c, because we are not testing the LCD-Module
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.c)
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/lcd.c)

add_executable(${EXECUTABLE_NAME} 
    main.c 
    # place here all files in test-directory


    ${MOCK_FILES}
    ${SOURCE_FILES} 
)

#target_compile_options(${EXECUTABLE_NAME} PRIVATE ${DEFAULT_C_COMPILE_FLAGS})

set_target_properties(${EXECUTABLE_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


target_include_directories(${EXECUTABLE_NAME} PRIVATE 
    "${PROJECT_SOURCE_DIR}/src" 
    "${PROJECT_SOURCE_DIR}/test/mocks"
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE cmocka-static
#    "-Wl,\
#    --wrap=sleep_ms\
#    --wrap=i2c_init\
#    --wrap=gpio_set_function\
#    --wrap=gpio_pull_up\
#    --wrap=i2c_write_blocking\ 
#    --wrap=i2c_read_blocking"
)
