
#include "lcd.h"

Image image_lcd;

/******************************************************************************
function :	Public function for initializing LCD
parameter:  -
******************************************************************************/
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

    init_image();
}

/******************************************************************************
function :	Public function for initializing LCD
parameter:  -
******************************************************************************/
void init_image()
{
    image_lcd.image = (UWORD *)malloc(LCD_1IN14_HEIGHT * LCD_1IN14_WIDTH * 2);
    image_lcd.height = LCD_1IN14.HEIGHT;
    image_lcd.width = LCD_1IN14.WIDTH;

    Paint_NewImage((UBYTE *)image_lcd.image, image_lcd.width, image_lcd.height, 0, WHITE);
    Paint_SetScale(65);
    clear_image();
    update_image();
}

/******************************************************************************
function :	Internal function for updating the image on the LCD
parameter:  -
******************************************************************************/
void update_image()
{
    LCD_1IN14_Display(image_lcd.image);
}

/******************************************************************************
function :	Internal function for displaying text on line 1
parameter:  str :   string to be displayed
******************************************************************************/
void display_line_1(char *str)
{
    Paint_DrawString_EN(1, 20, str, &Font20, WHITE, BLACK);
    LCD_1IN14_DisplayWindows(1, 1, 240, 67, image_lcd.image);
}

/******************************************************************************
function :	Internal function for displaying text on line 2
parameter:  str :   string to be displayed
******************************************************************************/
void display_line_2(char *str)
{
    Paint_DrawString_EN(1, 75, str, &Font20, WHITE, BLACK);
    LCD_1IN14_DisplayWindows(1, 68, 240, 135, image_lcd.image);
}

/******************************************************************************
function :	Public function for displaying text on line 1 or 2
parameter:
        line    : the line on which the text will be displayed
        str     : the string to be displayed on line 1 or 2
******************************************************************************/
void display_text_lcd(int line, char *str)
{

    if (line == 1)
    {
        clear_line_1();
        display_line_1(str);
    }
    else if (line == 2)
    {
        clear_line_2();
        display_line_2(str);
    }
}

/******************************************************************************
function :	Internal function for clearing the display
parameter:  -
******************************************************************************/
void clear_image()
{
    Paint_Clear(WHITE);
}

/******************************************************************************
function :	Internal function for clearing line 1
parameter:  -
******************************************************************************/
void clear_line_1()
{
    Paint_ClearWindows(1, 1, 240, 67, WHITE);
}

/******************************************************************************
function :	Internal function for clearing line 2
parameter:  -
******************************************************************************/
void clear_line_2()
{
    Paint_ClearWindows(1, 68, 240, 135, WHITE);
}
