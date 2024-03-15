#include "dht20.h"
#include <stdio.h>
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <math.h>

#include <stdlib.h>

#include <stdbool.h>
//#include "dht20_test.c"

uint8_t data[7]; // register for dht20

//static const uint8_t DHT20_ADDR = 0x38;
//static const uint8_t REG_1 = 0x1B;
//static const uint8_t REG_2 = 0x1C;
//static const uint8_t REG_3 = 0x1E;


/******************************************************************************
function :	Internal function to reset the internal DHT20 registers, not requiered
parameter:  -
******************************************************************************/
/*
void resetRegisters() {
  uint8_t buf1[3] = {REG_1, 0x00, 0x00};
  i2c_write_blocking(i2c0, DHT20_ADDR, buf1, 3, false);
  uint8_t buf2[3] = {REG_2, 0x00, 0x00};
  i2c_write_blocking(i2c0, DHT20_ADDR, buf2, 3, false);
  uint8_t buf3[3] = {REG_3, 0x00, 0x00};
  i2c_write_blocking(i2c0, DHT20_ADDR, buf3, 3, false);
  sleep_ms(100);
}
*/
/******************************************************************************
function :	Public function for initializing DHT20 sensor
parameter:  -
******************************************************************************/
int dht20_init() {

  sleep_ms(1500);
  i2c_init(i2c0, 400 * 1000);

   gpio_set_function(Default_SDA_PIN, GPIO_FUNC_I2C);   //Default_SDA_PIN 16
  gpio_set_function(Default_SCL_PIN, GPIO_FUNC_I2C);   //Default_SCL_PIN 17

  gpio_pull_up(Default_SCL_PIN);
  gpio_pull_up(Default_SDA_PIN);

 //0x71 113
	uint8_t buf[1] = {0x71};
  i2c_write_blocking(i2c_default, DHT20_ADDR, buf , 1, true);
  i2c_read_blocking(i2c_default, DHT20_ADDR, buf, 1, false);

  if (buf[0] != 24) {
    printf("init fail%x\n", buf[0]);
    return -1;
  }
  
  sleep_ms(10);
  return 1;
}

/******************************************************************************
function :	Internal function for DHT20 status word (0x18)
parameter:  status
******************************************************************************/
uint8_t dht20_readStatus() {
  bool success = false;
  for (int i = 0; i < 5; i++) {
    sleep_ms(80);
    i2c_read_blocking(i2c_default, DHT20_ADDR, data, 1, true);
    success = (data[0] & 0x80) == 0x0;
    if (success) {
      break;
    }
    if (!success) {
    printf("Sensor not ready. Maximum number of tries reached.");
    return EXIT_FAILURE;
    }
  }
}

/******************************************************************************
function :	Public function for requesting data from sensor
parameter:  values (hum, temp)
******************************************************************************/
dht20_values dht20_read() {
  data[0] = 172;
  data[1] = 51;
  data[2] = 0;

  i2c_write_blocking(i2c0, DHT20_ADDR, data, 3, false);
  dht20_readStatus();
  i2c_read_blocking(i2c0, DHT20_ADDR, data, 7, false);
  return dht20_convert(data);
}

/******************************************************************************
function :	Internal function to check the received bits from DHT20 via CRC
parameter:  
call from main via dht_checksum()
******************************************************************************/
unsigned char dht20_checksum(){
  printf("checksum executed\n");
  unsigned char crc = 0xFF; // Initialize CRC with 0xFF

    for (int i = 0; i < 7; i++) {
        crc ^= data[i]; // XOR current data byte with CRC

        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) { // If MSB of CRC is 1
                crc = (crc << 1) ^ POLYNOMIAL; // XOR CRC with polynomial
            } else {
                crc <<= 1; // Shift CRC left by 1 bit
            }
        }
    }
    printf("dht20_checksum = %x\n", crc);
    return crc;
}

/******************************************************************************
function :	Internal function for converting from bytes to numerial
parameter:  values (hum, temp)
******************************************************************************/
dht20_values dht20_convert(uint8_t data[7]) {
  
  int humidity_raw = (data[1] << 12) | (data[2] << 8) | (data[3] >> 4);
  int temperature_raw = ((data[3] << 16) | (data[4] << 8) | data[5]) & 0xfffff;

  dht20_values my_values;
  my_values.hum = (humidity_raw / powf(2, 20)) * 100;
  my_values.temp = ((temperature_raw / powf(2, 20)) * 200) - 50;

  return my_values;
}