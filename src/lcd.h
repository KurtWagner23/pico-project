#ifndef LCD_H
#define LCD_H

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in14.h"

typedef struct
{
    UWORD width;
    UWORD height;
    UWORD *image;
} Image;

extern Image image_lcd;

void init_lcd(void);

void update_image(void);

void display_text_lcd(int, char *);

void display_line_1(char *);

void display_line_2(char *);

void init_image(void);

void clear_image(void);

void clear_line_1(void);

void clear_line_2(void);

#endif // LCD_H