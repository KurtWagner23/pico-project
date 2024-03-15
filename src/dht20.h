#ifndef DHT20_H

#define DHT_20

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

//#include "dht20_test.c"

/*
*
*   Library for connecting the Seeed DHT20 Temperature & Humidity Sensor with I2C interface.
*
Connections:
GND -> GND
VCC -> 3V3
Default SDA Pin -> GP16
Default SCL Pin -> GP17
*/

#define Default_SDA_PIN 16
#define Default_SCL_PIN 17
#define DHT20_ADDR (0x38)
#define STATUS_WORD (0x71)
#define POLYNOMIAL (0x31)

typedef struct {
  float temp;
  float hum;
} dht20_values ;

int dht20_init();


uint8_t dht20_readStatus();

dht20_values dht20_convert();

dht20_values dht20_read();

unsigned char dht20_checksum();

//void test_dht20_checksum();

#endif 