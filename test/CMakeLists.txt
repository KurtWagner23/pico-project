# test/CMakeLists.txt

include(${PROJECT_SOURCE_DIR}/cmake/cmocka.cmake)

add_subdirectory(prototypes)
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
# remove main.c in src-directory and also lcd.c, because we are not testing the LCD-Module
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.c)
list(REMOVE_ITEM SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/lcd.c)
add_library(src ${SOURCE_FILES})
target_link_libraries(src prototypes)

add_subdirectory(lis3_tests)
add_subdirectory(dht20_tests)