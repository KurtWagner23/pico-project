#include "dht20.h"

// #include "dht20_test.c"
i2c_inst_t* _i2c_dht20;
uint8_t _address_dht20;

uint8_t data[7]; // register for dht20

// static const uint8_t DHT20_ADDR = 0x38;
// static const uint8_t REG_1 = 0x1B;
// static const uint8_t REG_2 = 0x1C;
// static const uint8_t REG_3 = 0x1E;

/******************************************************************************
function :	Internal function to reset the internal DHT20 registers, not
requiered parameter:  -
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
int init_dht20(i2c_inst_t* i2c,
               uint8_t hardwareAddress,
               uint8_t scl_pin,
               uint8_t sda_pin) {
    // int init_dht20() {
    _i2c_dht20 = i2c;
    _address_dht20 = hardwareAddress;

    uint8_t buf[7];

    sleep_ms(1500);

    // 0x71 113
    buf[1] = DHT20_STATUS_WORD;
    i2c_write_blocking(_i2c_dht20, _address_dht20, buf, 1, true);
    i2c_read_blocking(_i2c_dht20, _address_dht20, buf, 1, false);

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
uint8_t readData_dht20(uint8_t reg0, uint8_t reg1, uint8_t reg2) {
    data[0] = reg0;
    data[1] = reg1;
    data[2] = reg2;

    i2c_write_blocking(_i2c_dht20, _address_dht20, data, 3, false);
    bool success = false;
    for (int i = 0; i < 5; i++) {
        sleep_ms(80);
        i2c_read_blocking(_i2c_dht20, _address_dht20, data, 1, true);
        success = (data[0] & 0x80) == 0x0;
        if (success) {
            break;
        }
        if (!success) {
            printf("Sensor not ready. Maximum number of tries reached.");
            return EXIT_FAILURE;
        }
    }
    i2c_read_blocking(_i2c_dht20, _address_dht20, data, 7, false);
}

/******************************************************************************
function :	Public function for requesting data from sensor
parameter:  values (hum, temp)
******************************************************************************/
dht20_values getTemperatureHumidity_dht20() {
    readData_dht20(TRIGGER_MESSUREMENT,
                   TRIGGER_MESSUREMENT_PARAM1,
                   TRIGGER_MESSUREMENT_PARAM2);

    // calc_checksum_dht20();

    return calculate_dht20();
}

/******************************************************************************
function :	Internal function to check the received bits from DHT20 via CRC
parameter:
call from main via dht_checksum()
******************************************************************************/
unsigned char calc_checksum_dht20(uint8_t ele1,
                                  uint8_t ele2,
                                  uint8_t ele3,
                                  uint8_t ele4,
                                  uint8_t ele5,
                                  uint8_t ele6,
                                  uint8_t ele7,
                                  uint8_t result) {
    data[0] = ele1;
    data[1] = ele2;
    data[2] = ele3;
    data[3] = ele4;
    data[4] = ele5;
    data[5] = ele6;
    data[6] = ele7;
    int res = result;

    printf("checksum executed\n");
    unsigned char crc = 0xFF; // Initialize CRC with 0xFF

    for (int i = 0; i < 7; i++) {
        crc ^= data[i]; // XOR current data byte with CRC

        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) {                  // If MSB of CRC is 1
                crc = (crc << 1) ^ POLYNOMIAL; // XOR CRC with polynomial
            } else {
                crc <<= 1; // Shift CRC left by 1 bit
            }
        }
    }
    if (crc = res) {
        printf("dht20_checksum = %x\n", crc);
        return crc;
    } else
        return -1;
}

int get_checksum_dht20() {
    calc_checksum_dht20(28, 132, 194, 115, 236, 30, 153, 0);
    calc_checksum_dht20(28, 39, 172, 186, 35, 230, 40, 0);
}

/******************************************************************************
function :	Internal function for converting from bytes to numerial
parameter:  values (hum, temp)
******************************************************************************/
dht20_values calculate_dht20() {
    int humidity_raw = (data[1] << 12) | (data[2] << 8) | (data[3] >> 4);
    int temperature_raw =
        ((data[3] << 16) | (data[4] << 8) | data[5]) & 0xfffff;

    dht20_values my_values;
    my_values.hum = (humidity_raw / powf(2, 20)) * 100;
    my_values.temp = ((temperature_raw / powf(2, 20)) * 200) - 50;

    return my_values;
}