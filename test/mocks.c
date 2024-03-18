#include "mocks.h"

int __wrap_i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop)
{
    check_expected(addr);
    check_expected(src);

    return mock_type(int);
}

int __wrap_i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop)
{
    check_expected(addr);
    check_expected(len);

    // allow the calling test to specify the data it wants back
    // and copy it back out
    for (int i = 0; i < len; i++)
    {
        dst[i] = mock_type(uint8_t);
    }
    return len;
}