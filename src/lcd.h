#ifndef LCD_H
#define LCD_H

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in14.h"

extern UDOUBLE Imagesize;

void init_lcd(void);

void update_image(UWORD *image);

void display_text_lcd(void);

#endif // LCD_H