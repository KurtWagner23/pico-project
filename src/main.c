#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "lcd.h"
#include "lis3dhtr.h"
#include "Debug.h"

// put here every setup code for running only once
void setup()
{
    // init pico default LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    init_lcd();

    init_LIS3DHTR(i2c0, LIS3DHTR_HW_ADDRESS, DEFAULT_SCL_PIN, DEFAULT_SDA_PIN);
}

int main()
{
    // setup function called once
    setup();

    char acc[50];
    char temp[10];

    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    // main loop
    while (1)
    {

        sprintf(acc, "Acc x:%.2f, y:%.2f, z:%.2f",
                getAccelerationX_LIS3DHTR(),
                getAccelerationY_LIS3DHTR(),
                getAccelerationZ_LIS3DHTR());
        display_text_lcd(1, acc);

        sprintf(temp, "Temp: %.2f oC", getTemp_LIS3DHTR());
        display_text_lcd(2, temp);

        sleep_ms(1000);
    }
}