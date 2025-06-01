/*
 * st7789.h
 *
 *  Created on: May 31, 2025
 *      Author: HJ
 */

#ifndef ST7789_H_
#define ST7789_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#include "spi.h"
#include "fonts.h"
#include "systick.h"

// ST7789 register locations
#define ST7789_SWRST  0x01
#define ST7789_SLPOUT 0x11
#define ST7789_COLMOD 0x3A
#define ST7789_MADCTL 0x36
#define ST7789_CASET  0x2A
#define ST7789_RASET  0x2B
#define ST7789_INVON  0x21
#define ST7789_NORON  0x13
#define ST7789_RAMWR  0x2C
#define ST7789_DISPON 0x29

#define ST7789_XSTART 0x0000
#define ST7789_YSTART 0x0000

#define LCD_WIDTH     ((uint16_t)240)
#define LCD_HEIGHT     ((uint16_t)320)
#define LCD_SIZE      ((uint32_t)LCD_WIDTH * LCD_HEIGHT)

// RGB565 Colors
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define CYAN    0x07FF
#define YELLOW  0xFFC0
#define PURPLE  0xF81F
#define PINK    0xD252

void st7789_init(void);
void st7789_set_addr(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);
void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t colour);
void st7789_draw_char(uint16_t x, uint16_t y, uint16_t colour, char letter);
void st7789_clear_screen(uint16_t colour);
void st7789_draw_string(uint16_t x, uint16_t y, uint16_t colour, char* string);

#endif /* ST7789_H_ */
