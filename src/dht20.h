#ifndef DHT20_H
#define DHT20_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef SW_TESTS
#include "../test/prototypes/prototypes.h"
#else
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#endif
// #include "dht20_test.c"

/*
*
*   Library for connecting the Seeed DHT20 Temperature & Humidity Sensor with
I2C interface.
*
Connections:
GND -> GND
VCC -> 3V3
Default SDA Pin -> GP16
Default SCL Pin -> GP17
*/

#define DEFAULT_SDA_PIN 16
#define DEFAULT_SCL_PIN 17
#define DHT20_ADDR (0x38)
#define STATUS_WORD (0x71)
#define POLYNOMIAL (0x31)
#define DHT20_STATUS_WORD (0x71)
#define TRIGGER_MESSUREMENT (0xAC)
#define TRIGGER_MESSUREMENT_PARAM1 (0x33)
#define TRIGGER_MESSUREMENT_PARAM2 (0x00)

/*
Variables and Structs
*/
typedef struct {
    float temp;
    float hum;
} dht20_values;

extern i2c_inst_t* _i2c_dht20;
extern uint8_t _address_dht20;

/*
Function Prototypes
*/

int init_dht20(i2c_inst_t* i2c,
               uint8_t hardwareAddress,
               uint8_t scl_pin,
               uint8_t sda_pin);

uint8_t readData_dht20(uint8_t reg0, uint8_t reg1, uint8_t reg2);

dht20_values calculate_dht20(void);

dht20_values getTemperatureHumidity_dht20(void);

unsigned char calc_checksum_dht20(uint8_t ele1,
                                  uint8_t ele2,
                                  uint8_t ele3,
                                  uint8_t ele4,
                                  uint8_t ele5,
                                  uint8_t ele6,
                                  uint8_t ele7,
                                  uint8_t result);

int get_checksum_dht20(void);

// void test_dht20_checksum();

#endif // DHT20_H