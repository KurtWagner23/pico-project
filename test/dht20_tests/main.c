#include "mocks.h"

// include file with functions to test
#include "config.h"
#include "dht20.h"

/*
    Define here all your test cases and add them in the main function!
*/

static void test_init_dht20(void** state) {
    i2c_inst_t* i2c = {10};
    uint8_t return_value;
    uint8_t expected_return_value = 0;
    uint8_t expected_addr = 56;
    uint8_t expected_buffer[7] = {
        24, 0, 0, 0, 0, 0, 0 /* other expected values */};

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, expected_addr);
    expect_value(__wrap_i2c_read_blocking, len, 7);

    // calling will return 7 times because the mock-stack needs 7 values to
    // return
    for (int i = 0; i < 7; i++) {
        will_return(__wrap_i2c_read_blocking, expected_buffer[i]);
    }
    return_value =
        init_dht20(i2c, DHT20_ADDR, DEFAULT_SCL_PIN, DEFAULT_SDA_PIN);

    assert_int_equal(return_value, expected_return_value);
}

static void test_init_dht20_ERROR_RETURN(void** state) {
    i2c_inst_t* i2c = {10};
    uint8_t return_value;
    uint8_t expected_return_value = -1;
    uint8_t expected_addr = 56;
    uint8_t expected_buffer[7] = {
        0, 0, 0, 0, 0, 0, 0 /* other expected values */};

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, expected_addr);
    expect_value(__wrap_i2c_read_blocking, len, 7);

    // calling will return 7 times because the mock-stack needs 7 values to
    // return
    for (int i = 0; i < 7; i++) {
        will_return(__wrap_i2c_read_blocking, expected_buffer[i]);
    }
    return_value =
        init_dht20(i2c, DHT20_ADDR, DEFAULT_SCL_PIN, DEFAULT_SDA_PIN);

    assert_int_equal(return_value, expected_return_value);
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

static void test_readData_dht20(void** state) {
    uint8_t reg0 = 0xAC;
    uint8_t reg1 = 0x33;
    uint8_t reg2 = 0x00;
    i2c_inst_t* i2c = {10};
    uint8_t return_value;
    uint8_t expected_return_value = 0;
    uint8_t expected_addr = 56;
    uint8_t expected_data[7] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

    expect_any(__wrap_i2c_write_blocking, addr);
    expect_any(__wrap_i2c_write_blocking, src);
    will_return(__wrap_i2c_write_blocking, 0);

    expect_value(__wrap_i2c_read_blocking, addr, _address_dht20);
    expect_value(__wrap_i2c_read_blocking, len, 1);
    will_return(__wrap_i2c_read_blocking,
                0x00); // Assuming success on the first try

    // data
    expect_value(__wrap_i2c_read_blocking, addr, expected_addr);
    expect_value(__wrap_i2c_read_blocking, len, 7);
    // calling will return 7 times because the mock-stack needs 7 values to
    // return
    for (int i = 0; i < 7; i++) {
        will_return(__wrap_i2c_read_blocking, expected_data[i]);
    }

    return_value = readData_dht20(reg0, reg1, reg2);

    assert_int_equal(return_value, expected_return_value);
}
static void test_calculate_negative_dht20(void** state) {
    uint8_t data[7] = {28, 132, 154, 211, 235, 119, 108};
    float expected_Humidity = 55.32;
    float expected_Temperature = -1.00;

    dht20_values result = calculate_dht20(data);

    assert_float_equal(result.hum, expected_Humidity, 0.01);
    assert_float_equal(result.temp, expected_Temperature, 0.01);
}
static void test_calculate_positive_dht20(void** state) {
    uint8_t data[7] = {28, 65, 251, 199, 51, 52, 201, 1};
    float expected_Humidity = 31.13;
    float expected_Temperature = 40.00;

    dht20_values result = calculate_dht20(data);

    assert_float_equal(result.hum, expected_Humidity, 0.01);
    assert_float_equal(result.temp, expected_Temperature, 0.01);
}
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_i2c_read_blocking),
        cmocka_unit_test(test_init_dht20),
        cmocka_unit_test(test_init_dht20_ERROR_RETURN),
        cmocka_unit_test(test_readData_dht20),
        cmocka_unit_test(test_calculate_negative_dht20),
        cmocka_unit_test(test_calculate_positive_dht20),

    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}