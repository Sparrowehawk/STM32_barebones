/*
 * spi.c
 *
 *  Created on: May 31, 2025
 *      Author: HJ
 */

#include "spi.h"

void spi_gpio_init(void)
{

	// SPI1 is AF05
	// SCLK PA5
	// MOSI PA7
	// MISO PA6 -- NOT USED

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~GPIOA_CLR;

	GPIOA->MODER |= SPI_SCLK;
	GPIOA->MODER |= SPI_MOSI;

	GPIOA->AFR[0] &= ~SPI_AF05_CLR;
	GPIOA->AFR[0] |= SPI_AFO5_SCLK;
	GPIOA->AFR[0] |= SPI_AFO5_MOSI;

	GPIOA->MODER |= SPI_RST;
	GPIOA->MODER |= SPI_DC;
	GPIOA->MODER |= SPI_CS;

	GPIOA->ODR |= SPI_CS_OUT;  // Set CS high
	GPIOA->ODR |= SPI_DC_OUT;  // Set DC high
	GPIOA->ODR |= SPI_RST_OUT; // Set RST high (after reset pulse)

}

void spi_config(void)
{
	spi_gpio_init();

	RCC->APB2ENR |= SPI1_EN;

	SPI1->CR1 |= SPI_BAUD_RATE;
	SPI1->CR1 |= SPI_CPOL;
	SPI1->CR1 |= SPI_MSTR;
	SPI1->CR1 |= SPI_CPHA;
	SPI1->CR1 |= SPI_SSI;
	SPI1->CR1 |= SPI_SSM;

	SPI1->CR1 |= SPI_SPE;
}


void spi_write(uint8_t data)
{

	volatile uint8_t tmp;

	while(!(SPI1->SR & SPI_TXE_FLAG));
	SPI1->DR = data;
	while(!(SPI1->SR & SPI_TXE_FLAG));
	while(SPI1->SR & SPI_BUSY_FLAG);

	tmp = SPI1->DR;
	tmp = SPI1->SR;
}

void spi_write_16bit(uint16_t data)
{
	spi_write(data >> 8);
	spi_write(data & 0xFF);
}

void spi_write_data(void)
{
	GPIOA->ODR &= ~SPI_CS_OUT;
	GPIOA->ODR |= SPI_DC_OUT;
}

void spi_write_command(void)
{
	GPIOA->ODR &= ~SPI_CS_OUT;
	GPIOA->ODR &= ~SPI_DC_OUT;
}

void spi_end_write(void)
{
	GPIOA->ODR |= SPI_CS_OUT;
}
