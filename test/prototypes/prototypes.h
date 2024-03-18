#ifndef PROTOTYPES_H
#define PROTOTYPES_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*
Prototype functions so that everything compiles without the RaspberryPi Pico SDK
*/

#define PICO_ERROR_GENERIC -2

typedef unsigned int uint;

enum gpio_function
{
    GPIO_FUNC_I2C = 3,
};

typedef struct
{
    int dummy_member;
} i2c_inst_t;

void gpio_set_function(uint gpio, enum gpio_function fn);

void sleep_ms(uint32_t ms);

void gpio_pull_up(uint gpio);

uint i2c_init(i2c_inst_t *inst, uint baudrate);

int i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop);

int i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop);

#endif // PROTOTYPES_H