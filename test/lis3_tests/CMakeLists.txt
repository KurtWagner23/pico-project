# test/lis3_tests/CMakeLists.txt

set(EXECUTABLE_NAME test_lis3)

file(GLOB MOCK_FILES ${PROJECT_SOURCE_DIR}/test/mocks/*.c)

add_cmocka_test(${EXECUTABLE_NAME}
                SOURCES main.c ${MOCK_FILES}
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES src cmocka-static
)

set_property(TARGET ${EXECUTABLE_NAME}
             PROPERTY LINK_FLAGS
             "${DEFAULT_LINK_FLAGS} -Wl,--wrap=i2c_write_blocking,
             --wrap=i2c_read_blocking"
)

include_directories(../mocks)
include_directories(../../src)
include_directories(../prototypes)
