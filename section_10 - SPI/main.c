#include "systick.h"
#include "spi.h"
#include "st7789.h"

// MOSI -> PA7
// SCLK -> PA5

// CS  -> PA6
// RST -> PA8
// DC  -> PA9

int main(void)
{


	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b01 << 10);


	spi_config();
	st7789_init();

	st7789_clear_screen(GREEN);

    while(1)
    {



    }
}

