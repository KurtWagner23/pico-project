# src/CMakeLists.txt

find_program(PICOTOOL NAMES picotool)
if(PICOTOOL)
    message(STATUS "Picotool found")
else()
    message(WARNING "Picotool not found! Consider installing when you want to upload automatically! Instructions for installing Picotool in the Readme.md")
endif()


include_directories(../external/Pico-LCD-1.14/c/lib/Config)
include_directories(../external/Pico-LCD-1.14/c/lib/GUI)
include_directories(../external/Pico-LCD-1.14/c/lib/Icm20948)
include_directories(../external/Pico-LCD-1.14/c/lib/LCD)
include_directories(../external/Pico-LCD-1.14/c/lib/Infrared)

# include all files inside source folder into executable
file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
)

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link Pico-specific and LCD libraries to target
target_link_libraries(${PROJECT_NAME} PUBLIC 
    # pico libraries
    pico_stdlib
    hardware_i2c
    hardware_spi
    # LCD libraries 
    LCD 
    Infrared 
    Icm20948 
    GUI 
    Fonts 
    Config
)
# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Add a custom target for uploading
add_custom_target(upload
    COMMAND picotool load -f ${CMAKE_BINARY_DIR}/bin/main.uf2
    DEPENDS main
    COMMENT "Uploading the binary to Raspberry Pi Pico"
)
