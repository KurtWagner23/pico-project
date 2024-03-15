#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#include "lis3dhtr.h"

static void test(void **state)
{
    assert_int_equal(2, 2);
}

static void test_init_LIS3DHTR(void **state)
{
    i2c_inst_t *i2c = {10};
    assert_int_equal(init_LIS3DHTR(i2c, LIS3DHTR_HW_ADDRESS, DEFAULT_SCL_PIN, DEFAULT_SDA_PIN), 0);
}

int main()
{
    const struct CMUnitTest tests[] =
        {
            cmocka_unit_test(test),
            cmocka_unit_test(test_init_LIS3DHTR),
        };

    return cmocka_run_group_tests(tests, NULL, NULL);
}