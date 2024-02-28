
#include "lcd.h"

Image image_lcd;

/******************************************************************************
function :	Public function for initializing LCD
parameter:  -
return:
    0:  if initializing the DEV-Module and init_image was succesful
    -1: if error at initializing
******************************************************************************/
int init_lcd()
{
    printf("Init LCD\n");
    if (DEV_Module_Init() != 0)
    {
        return -1;
    }

    // LCD Init
    printf("Initialize in horizontal mode\n");
    LCD_1IN14_Init(HORIZONTAL);

    return init_image();
}

/******************************************************************************
function :	Private function for initializing Image dimensions
parameter:  -
return:
    -1: if image memory could not be allocated
    0:  if image memory could be allocated
******************************************************************************/
int init_image()
{
    image_lcd.image = (UWORD *)malloc(LCD_1IN14_HEIGHT * LCD_1IN14_WIDTH * 2);
    if (image_lcd.image == NULL)
        return -1;
    image_lcd.height = LCD_1IN14.HEIGHT;
    image_lcd.width = LCD_1IN14.WIDTH;

    Paint_NewImage((UBYTE *)image_lcd.image, image_lcd.width, image_lcd.height, 0, WHITE);
    Paint_SetScale(65);
    clear_image();
    update_image();

    return 0;
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
