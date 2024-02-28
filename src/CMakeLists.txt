# src/CMakeLists.txt

# Add a header directories
#include_directories(../external/Pico-LCD-1.14/c/examples)
include_directories(../external/Pico-LCD-1.14/c/lib/Config)
include_directories(../external/Pico-LCD-1.14/c/lib/GUI)
include_directories(../external/Pico-LCD-1.14/c/lib/Icm20948)
include_directories(../external/Pico-LCD-1.14/c/lib/LCD)
include_directories(../external/Pico-LCD-1.14/c/lib/Infrared)


add_executable(${PROJECT_NAME}
    main.c
    lcd.c
    lis3dhtr.c  # acceleration sensor
)


set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Add pico_stdlib library which aggregates commonly used features
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
pico_enable_stdio_uart(${PROJECT_NAME} 0)