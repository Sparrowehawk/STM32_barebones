/*
 * st7789.c
 *
 *  Created on: May 31, 2025
 *      Author: HJ
 */


#include "st7789.h"

void st7789_init(void)
{
	spi_write_command();

	GPIOA->ODR &= ~SPI_RST_OUT;
	systickDelayMS(1000);
	GPIOA->ODR |= SPI_RST_OUT;
	systickDelayMS(1000);

	spi_write_command();
	spi_write(ST7789_SWRST);
	spi_write(ST7789_SLPOUT);

	spi_write(ST7789_COLMOD);
	spi_write_data();
	spi_write(0x55);

	spi_write_command();
	spi_write(ST7789_MADCTL);
	spi_write_data();
	spi_write(0x00);

	spi_write_command();
	spi_write(ST7789_CASET);
	spi_write_data();
	spi_write_16bit(ST7789_XSTART);
	spi_write_16bit(0x00EF);

	spi_write_command();
	spi_write(ST7789_RASET);
	spi_write_data();
	spi_write_16bit(ST7789_YSTART);
	spi_write_16bit(0x013F);

	spi_write_command();
    spi_write(ST7789_INVON);
    spi_write(ST7789_NORON);

    spi_write(ST7789_DISPON);
    spi_end_write();
}

void st7789_set_addr(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
    // Tell what LCD it is writing to
	spi_write_command();
	spi_write(ST7789_CASET);
    spi_write_data();
    spi_write_16bit(x0 + ST7789_XSTART);
    spi_write_16bit(x1 + ST7789_XSTART);

    spi_write_command();
    spi_write(ST7789_RASET);
    spi_write_data();
    spi_write_16bit(y0 + ST7789_YSTART);
    spi_write_16bit(y1 + ST7789_YSTART);

    spi_write_command();
    spi_write(ST7789_RAMWR); // Store in RAM
    spi_end_write();
}

void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t colour)
{
	st7789_set_addr(x, x+1, y, y+1);
	spi_write_data();
	spi_write_16bit(colour);
	spi_end_write();
}


void st7789_draw_char(uint16_t x, uint16_t y, uint16_t colour, char letter)
{
    if (letter < 32 || letter > 127) return; // Making sure it's standard ASCII

    int col, row;

    for (col = 0; col < 5; col++) {
        uint8_t line = ascii[letter - 32][col];

        for (row = 0; row < 8; row++) {
            if (line & (1 << row)) {
            	st7789_draw_pixel(x + col, y + row, colour);
            }
        }
    }
}

// Write to the entire screen a set colour
void st7789_clear_screen(uint16_t colour)
{
    uint32_t i;
    st7789_set_addr(0, LCD_WIDTH-1, 0, LCD_HEIGHT-1);

    spi_write_data();
    for(i = LCD_SIZE; i > 0; i--){
    	spi_write_16bit(colour);
    }
    spi_end_write();
}

void st7789_draw_string(uint16_t x, uint16_t y, uint16_t colour, char* string)
{
    int i;

    // Temp variables to allow to go to next line if there's an overflow
    uint16_t x_pos = x;
    uint16_t y_pos = y;

    for (i = 0; string[i] != '\0'; i++) {
        if(x_pos + 6 > LCD_WIDTH){          // If there's overflow in row
            y_pos += 8;
            x_pos = 0;

            if(y_pos + 8 > LCD_HEIGHT){     // If it has hit bottom of screen
                y_pos = 0;
            }

        }

        st7789_draw_char(x_pos, y_pos, colour, string[i]);
        x_pos += 6;
    }
}
