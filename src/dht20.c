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
function :	Initializing DHT20 sensor
parameter:
    i2c:                set the i2c channel u want to use for the sensor
    hardwareAddress:    Physical Device Address as  one byte hex (use
DHT20_ADDR) scl_pin:            SCL-Pin where u connect to the pico sda_pin:
SDA-Pin where u connect to the pico
return:
    7: Sensor initialized -> len of i2c_*_blocking
    -1: Initialisation failed
******************************************************************************/
int init_dht20(i2c_inst_t* i2c,
               uint8_t hardwareAddress,
               uint8_t scl_pin,
               uint8_t sda_pin) {
    // int init_dht20() {
    _i2c_dht20 = i2c;
    _address_dht20 = hardwareAddress;

    int error = 0;
    int return_value = 0;

    uint8_t buf[7];
    uint8_t testvar = 113;

    sleep_ms(1500);

    // 0x71 113
    buf[1] = DHT20_STATUS_WORD;
    // i2c_write_blocking(_i2c_dht20, _address_dht20, buf, 7, true);
    error = i2c_write_blocking(_i2c_dht20, _address_dht20, buf, 7, true);
    if (error == PICO_ERROR_GENERIC)
        return_value = -1;
    //    i2c_read_blocking(_i2c_dht20, _address_dht20, buf, 7, false);
    error = i2c_read_blocking(_i2c_dht20, _address_dht20, buf, 7, false);
    if (error == PICO_ERROR_GENERIC)
        return_value = -1;

    // if (buf[0] != 24) {
    if (buf[0] != 24) {
        printf("init fail%x\n", buf[0]);
        return_value = -1;
        // return -1;
    }

    sleep_ms(10);
    return return_value;
}

/******************************************************************************
function :	Function for requesting data from sensor
parameter:
    TRIGGER_MESSUREMENT/ -PARAM1/ -Params2: start to read data from sensor
return:
    0: data received
    -1: failed to get values from sensor
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
    return 0;
}

/******************************************************************************
function :	Helper function for read and calculate
parameter:
    TRIGGER_MESSUREMENT/ -PARAM1/ -Params2: start to read data from sensor
return: Return the values.hum in g/m^3 and values.temp in C°C
******************************************************************************/
dht20_values getTemperatureHumidity_dht20() {
    readData_dht20(TRIGGER_MESSUREMENT,
                   TRIGGER_MESSUREMENT_PARAM1,
                   TRIGGER_MESSUREMENT_PARAM2);

    // calc_checksum_dht20();

    return calculate_dht20((uint8_t*)data);
}

/******************************************************************************
function :	Internal function to check the received bytes from DHT20 via CRC
parameter:
    data: 7 bytes recieved from sensor
return:
    crc: calculated checksum value -> 0
    -1: if data is wrong
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
    uint8_t res = 0;
    res = result;

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
    if (crc == res) {
        printf("dht20_checksum = %x\n", crc);
        return crc;
    } else
        return -1;
}

/******************************************************************************
function :	Function to test the calculation for the checksum
parameter: data(7), expected_value
******************************************************************************/
int get_checksum_dht20() {
    calc_checksum_dht20(
        28, 132, 194, 115, 236, 30, 153, 0); // data(7), expected_value
    calc_checksum_dht20(
        28, 39, 172, 186, 35, 230, 40, 0); // data(7), expected_value
}

/******************************************************************************
function :	Function to calculate temperature and humidity from raw data
parameter:
    data: 7 Bytes raw data recieved from sensor
    values.hum: calculated humidity in g/m^3
    values.temp: calculated temperatur °C
return: values.hum in g/m^3 and values.temp in C°C
******************************************************************************/
dht20_values calculate_dht20(uint8_t data[7]) {
    int humidity_raw = (data[1] << 12) | (data[2] << 8) | (data[3] >> 4);
    int temperature_raw =
        ((data[3] << 16) | (data[4] << 8) | data[5]) & 0xfffff;

    dht20_values my_values;
    my_values.hum = ((float)humidity_raw / powf(2, 20)) * 100;
    my_values.temp = (((float)temperature_raw / powf(2, 20)) * 200) - 50;

    return my_values;
}