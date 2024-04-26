#include "lis3dhtr.h"

uint8_t _address_lis3;
i2c_inst_t* _i2c_lis3;

/******************************************************************************
function :	Initialize LIS3DHTR Sensor
parameter:
    i2c:                set the i2c channel u want to use for the sensor
    hardwareAddress:    Physical Device Address as  one byte hex (use
LIS3DHTR_HW_ADDRESS) scl_pin:            SCL-Pin where u connect to the pico
    sda_pin:            SDA-Pin where u connect to the pico
return:
    0:      if Sensor is initialized
    -1:     if no device present
******************************************************************************/
int init_LIS3DHTR(i2c_inst_t* i2c,
                  uint8_t hardwareAddress,
                  uint8_t scl_pin,
                  uint8_t sda_pin) {
    _i2c_lis3 = i2c;
    _address_lis3 = hardwareAddress;

    uint8_t buf[2];

    int error = 0;
    int return_value = 0; // Return 0 when no errors occur!

    sleep_ms(LIS3DHTR_CONVERSIONDELAY);

    // Normal Mode and 1.25 kHz data rate
    buf[0] = 0x20;
    buf[1] = 0x97;
    error = i2c_write_blocking(_i2c_lis3, _address_lis3, buf, 2, false);
    if (error == PICO_ERROR_GENERIC)
        return_value = -1;

    // Turn block data update on (for temperature sensing)
    buf[0] = 0x23;
    buf[1] = 0x80;
    error = i2c_write_blocking(_i2c_lis3, _address_lis3, buf, 2, false);
    if (error == PICO_ERROR_GENERIC)
        return_value = -1;

    // Turn ADC on
    buf[0] = 0x1F;
    buf[1] = 0xC0;
    error = i2c_write_blocking(_i2c_lis3, _address_lis3, buf, 2, false);
    if (error == PICO_ERROR_GENERIC)
        return_value = -1;

    sleep_ms(LIS3DHTR_CONVERSIONDELAY);

    return return_value;
}

/******************************************************************************
function :	Function to calculate the acceleration from raw data
parameter:
    rawData:    2 Byte raw data from recieved from sensor
    isAccel:    Specifies the calculation if it is acceleration data or
temperature data return:     Returns the calculated acceleration in m/s^2 or
temperature in °C
******************************************************************************/
float calculateAcceleration_LIS3DHTR(uint16_t rawData, bool isAccel) {
    // Convert with respect to the value being temperature or acceleration
    // reading
    float scaling = .0f;
    float senstivity = 0.004f; // g per unit

    if (isAccel) {
        scaling = 64 / senstivity;
        return (float)((int16_t)rawData) / scaling * EARTH_GRAVITY;
    } else {
        scaling = 64;
        return (float)((int16_t)rawData) / scaling;
    }
}

/******************************************************************************
function :	Function for reading data from registers
parameter:
    regLow:     The lower register address to read from
    isAccel:    To specify temperature or acceleration calculation
return:   Returns the calculated acceleration in m/s^2 or temperature in °C
******************************************************************************/
float readData_LIS3DHTR(uint8_t regLow, bool isAccel) {
    uint8_t lsb = 0;
    uint8_t msb = 0;
    uint16_t raw_accel = 0;
    uint8_t regHigh = regLow | 0x01;

    // lsb = readReg(regLow);
    // msb = readReg(regHigh);

    i2c_write_blocking(_i2c_lis3, _address_lis3, &regLow, 1, true);
    i2c_read_blocking(_i2c_lis3, _address_lis3, &lsb, 1, false);

    i2c_write_blocking(_i2c_lis3, _address_lis3, &regHigh, 1, true);
    i2c_read_blocking(_i2c_lis3, _address_lis3, &msb, 1, false);

    raw_accel = (msb << 8) | lsb;

    return calculateAcceleration_LIS3DHTR(raw_accel, isAccel);
}

/******************************************************************************
function :	Function for reading data from the specified register
parameter:
    reg:     The register address to read from
return:   Returns one byte of read date
******************************************************************************/
uint8_t readReg(uint8_t reg) {
    uint8_t byte = 0;
    // read register
    i2c_write_blocking(_i2c_lis3, _address_lis3, &reg, 1, true);
    i2c_read_blocking(_i2c_lis3, _address_lis3, &byte, 1, false);

    return byte;
}

/******************************************************************************
function :	For getting the acceleration in X - direction
parameter:  -
return:     Returns the calculated acceleration in X in m/s^2
******************************************************************************/
float getAccelerationX_LIS3DHTR() {
    return readData_LIS3DHTR(0x28, true);
}

/******************************************************************************
function :	For getting the acceleration in Y - direction
parameter:  -
return:     Returns the calculated acceleration in Y in m/s^2
******************************************************************************/
float getAccelerationY_LIS3DHTR() {
    return readData_LIS3DHTR(0x2A, true);
}

/******************************************************************************
function :	For getting the acceleration in Z - direction
parameter:  -
return:     Returns the calculated acceleration in Z in m/s^2
******************************************************************************/
float getAccelerationZ_LIS3DHTR() {
    return readData_LIS3DHTR(0x2C, true);
}

/******************************************************************************
function :	For getting the temperature of the sensor
parameter:  -
return:     Returns the temperature of the sensor in °C
******************************************************************************/
float getTemp_LIS3DHTR() {
    return 25 + readData_LIS3DHTR(0x0C, false);
}