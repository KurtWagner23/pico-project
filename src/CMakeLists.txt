# src/CMakeLists.txt

add_executable(${PROJECT_NAME}
    main.c
)


# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib)
# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})