#include "mocks.h"

// include file with functions to test
#include "config.h"
#include "lis3dhtr.h"

/*
    Define here all your test cases and add them in the main function!
*/

static void test_init_LIS3DHTR(void** state) {
    i2c_inst_t* i2c = {10};
    int return_value;
    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    return_value = init_LIS3DHTR(
        i2c, LIS3DHTR_HW_ADDRESS, DEFAULT_SCL_PIN, DEFAULT_SDA_PIN);

    assert_int_equal(return_value, 0);
}

static void test_init_LIS3DHTR_ERROR_RETURN(void** state) {
    i2c_inst_t* i2c = {10};
    int return_value;

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, PICO_ERROR_GENERIC);

    return_value = init_LIS3DHTR(
        i2c, LIS3DHTR_HW_ADDRESS, DEFAULT_SCL_PIN, DEFAULT_SDA_PIN);

    assert_int_equal(return_value, -1);
}

static void test_readReg_zero_return(void** state) {
    uint8_t byte;
    uint8_t check_addr = 0x19;

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, check_addr);
    expect_value(__wrap_i2c_read_blocking, len, 1);
    will_return(__wrap_i2c_read_blocking, 0b00000000);

    byte = readReg(0x28);

    assert_int_equal(byte, 0);
}

static void test_readData_LIS3DHTR_Acceleration_pos_value(void** state) {
    float acceleration;
    int check_addr = 0x19;

    // first function call of readReg
    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, check_addr);
    expect_value(__wrap_i2c_read_blocking, len, 1);
    // here lsb value
    will_return(__wrap_i2c_read_blocking, 0b11110000);

    // second function call of readReg
    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, check_addr);
    expect_value(__wrap_i2c_read_blocking, len, 1);
    // here msb value
    will_return(__wrap_i2c_read_blocking, 0b01111111);

    acceleration = readData_LIS3DHTR(0x28, true);

    assert_float_equal(acceleration, 20.5, 0.5);
}

static void test_readData_LIS3DHTR_Acceleration_neg_value(void** state) {
    float acceleration;
    int check_addr = 0x19;

    // first function call of readReg
    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, check_addr);
    expect_value(__wrap_i2c_read_blocking, len, 1);
    // here lsb value
    will_return(__wrap_i2c_read_blocking, 0b11111111);

    // second function call of readReg
    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, check_addr);
    expect_value(__wrap_i2c_read_blocking, len, 1);
    // here msb value
    will_return(__wrap_i2c_read_blocking, 0b11000000);

    acceleration = readData_LIS3DHTR(0x28, true);

    assert_float_equal(acceleration, -12, 0.5); // -9.81
}

static void test_i2c_read_blocking(void** state) {
    // (void)state; // Unused parameter

    uint8_t expected_addr = 0x42;
    size_t expected_len = 2;
    uint8_t mock_buffer[2] = {24, 22};
    uint8_t actual_buffer[2];
    int result;

    // Set up the expected values
    expect_value(__wrap_i2c_read_blocking, addr, expected_addr);
    expect_value(__wrap_i2c_read_blocking, len, expected_len);

    // Provide the mock buffer to be returned
    will_return(__wrap_i2c_read_blocking, mock_buffer[0]);
    will_return(__wrap_i2c_read_blocking, mock_buffer[1]);

    // Call the function under test
    result = i2c_read_blocking(
        NULL, expected_addr, actual_buffer, expected_len, false);
    //  Check the result and buffer contents
    assert_int_equal(mock_buffer[0], actual_buffer[0]);
    assert_int_equal(mock_buffer[1], actual_buffer[1]);
    assert_int_equal(expected_len, result);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_LIS3DHTR),
        cmocka_unit_test(test_init_LIS3DHTR_ERROR_RETURN),
        cmocka_unit_test(test_readReg_zero_return),
        cmocka_unit_test(test_readData_LIS3DHTR_Acceleration_pos_value),
        cmocka_unit_test(test_readData_LIS3DHTR_Acceleration_neg_value),
        cmocka_unit_test(test_i2c_read_blocking),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}