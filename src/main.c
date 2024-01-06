#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "lcd.h"

void setup()
{
    // init pico default LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    init_lcd();
}

int main()
{
    setup();

    // Display Image with Text

    // Displaying image with two different texts
    for (;;)
    {
        display_text_lcd();
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(2000);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(2000);
    }
}