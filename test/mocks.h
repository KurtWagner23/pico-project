#ifndef MOCKS_H
#define MOCKS_H

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "prototypes.h"

/*
    Define here all functions that should be wrapped for testing
    !IMPORTANT! Don't forget to add the functions to the link-flags in
   ./test/CMakeLists.txt
*/

int __wrap_i2c_write_blocking(
    i2c_inst_t* i2c, uint8_t addr, const uint8_t* src, size_t len, bool nostop);
int __wrap_i2c_read_blocking(
    i2c_inst_t* i2c, uint8_t addr, uint8_t* dst, size_t len, bool nostop);

#endif // MOCKS_H