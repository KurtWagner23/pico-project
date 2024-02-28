#ifndef LIS3DHTR_H
#define LIS3DHTR_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

/*
*
*   Library for connecting the Seeed LIS3DHTR Acceleration Sensor with I2C interface.
*
Connections:
GND -> GND
VCC -> 3V3
Default SDA Pin -> GP20
Default SCL Pin -> GP21
*/

#define DEFAULT_SDA_PIN 20
#define DEFAULT_SCL_PIN 21
#define LIS3DHTR_HW_ADDRESS (0x19)
#define LIS3DHTR_CONVERSIONDELAY (100)
#define EARTH_GRAVITY 9.80665 // [m/s^2]

extern i2c_inst_t *_i2c;
extern uint8_t _address;

int init_LIS3DHTR(i2c_inst_t *i2c, uint8_t hardwareAddress, uint8_t scl_pin, uint8_t sda_pin);

float readData_LIS3DHTR(uint8_t regLow, bool isAccel);

float calculateAcceleration_LIS3DHTR(uint16_t rawData, bool isAccel);

float getTemp_LIS3DHTR(void);

float getAccelerationX_LIS3DHTR(void);

float getAccelerationY_LIS3DHTR(void);

float getAccelerationZ_LIS3DHTR(void);

#endif // LIS3DHTR_H
