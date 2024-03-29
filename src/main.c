#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#include "dht20.h"
#include "lcd.h"
#include "lis3dhtr.h"

#define sda_controller_zero 16
#define scl_controller_zero 17
#define i2c_zero i2c0

// put here every setup code for running only once
void setup() {
    stdio_init_all();

    // init pico default LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    i2c_init(i2c_zero, 400 * 1000);
    gpio_set_function(scl_controller_zero, GPIO_FUNC_I2C);
    gpio_set_function(sda_controller_zero, GPIO_FUNC_I2C);

    // Enable pull-ups on Pin 20 (GP20) and Pin 21 (GP21)
    gpio_pull_up(scl_controller_zero);
    gpio_pull_up(sda_controller_zero);

    init_lcd();

    init_dht20(i2c_zero, DHT20_ADDR, scl_controller_zero, sda_controller_zero);
    sleep_ms(500);
    init_LIS3DHTR(i2c_zero,
                  LIS3DHTR_HW_ADDRESS,
                  scl_controller_zero,
                  sda_controller_zero);
}

int main() {
    // setup function called once
    setup();

    char acc[50];
    char temp[10];

    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    dht20_values Values;
    //  main loop
    while (1) {
        sprintf(acc,
                "Acc x:%.2f,      y:%.2f, z:%.2f",
                getAccelerationX_LIS3DHTR(),
                getAccelerationY_LIS3DHTR(),
                getAccelerationZ_LIS3DHTR());
        display_text_lcd(1, acc);

        Values = getTemperatureHumidity_dht20();
        sprintf(
            temp, "Temp: %.2f oC,  Hum: %.2f g/m^3", Values.temp, Values.hum);
        display_text_lcd(2, temp);

        sleep_ms(500);
    }
}