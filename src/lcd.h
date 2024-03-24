#ifndef LCD_H
#define LCD_H

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in14.h"

/*
Variables and Structs
*/

typedef struct {
    UWORD width;
    UWORD height;
    UWORD* image;
} Image;

extern Image image_lcd;

/*
Function Prototypes
*/

int init_lcd(void);

void update_image(void);

void display_text_lcd(int line, char* str);

void display_line_1(char* str);

void display_line_2(char* str);

int init_image(void);

void clear_image(void);

void clear_line_1(void);

void clear_line_2(void);

#endif // LCD_H