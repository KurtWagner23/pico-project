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
        cmocka_unit_test(test_i2c_read_blocking),
        cmocka_unit_test(test_init_dht20),

    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}