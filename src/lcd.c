
#include "lcd.h"

// TODO: put display size in struct

UDOUBLE Imagesize;

void init_lcd()
{
    printf("Init LCD\n");
    if (DEV_Module_Init() != 0)
    {
        exit(-1);
    }

    // LCD Init
    printf("Initialize in horizontal mode\n");
    LCD_1IN14_Init(HORIZONTAL);

    Imagesize = LCD_1IN14_HEIGHT * LCD_1IN14_WIDTH * 2;
}

void update_image(UWORD *image)
{
    LCD_1IN14_Display(image);
}

void display_text_lcd()
{
    // maybe static???
    UWORD Image[Imagesize];
    Paint_NewImage((UBYTE *)Image, LCD_1IN14.WIDTH, LCD_1IN14.HEIGHT, 0, WHITE);
    Paint_SetScale(65);

    Paint_Clear(WHITE);
    Paint_DrawString_EN(1, 40, "Hello World!", &Font20, 0x000f, 0xfff0);
    Paint_DrawString_EN(1, 100, "Pico-LCD-1.14", &Font16, RED, WHITE);

    update_image(Image);
}
