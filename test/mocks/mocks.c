#include "mocks.h"

uint i2c_init(i2c_inst_t *inst, uint baudrate)
{
    // check_expected(inst);
    // check_expected(baudrate);
}

int i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop)
{
}

int i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop)
{
    // allow the calling test to specify the data it wants back
    // and copy it back out
    for (int i = 0; i < len; i++)
    {
        dst[i] = mock_type(uint8_t);
    }
    return len;
}

void gpio_set_function(uint gpio, enum gpio_function fn)
{
    // check_expected(gpio);
    // check_expected(fn);
}

void sleep_ms(uint32_t ms)
{
    // check_expected(ms);
}

void gpio_pull_up(uint gpio)
{
}
