/*
 * spi.h
 *
 *  Created on: May 31, 2025
 *      Author: HJ
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN				(1U << 0)
#define SPI1_EN				(1U << 12)
#define SPI_SCLK			(0b10 << 10)
#define SPI_MOSI			(0b10 << 14)

#define SPI_AF05			(0b0101)
#define SPI_AF05_CLR		(0xFF << 20)
#define SPI_AFO5_SCLK		(SPI_AF05 << 20)
#define SPI_AFO5_MOSI		(SPI_AF05 << 28)

#define SPI_RST				(0b01 << 16)
#define SPI_DC				(0b01 << 18)
#define SPI_CS				(0b01 << 12)

#define SPI_RST_OUT			(1U << 8)
#define SPI_DC_OUT			(1U << 9)
#define SPI_CS_OUT			(1U << 6)

#define GPIOA_CLR			(0x3FF << 10)


#define SPI_BAUD_RATE		(0b111 << 3)
#define SPI_CPOL			(1U << 1)
#define SPI_MSTR			(1U << 2)
#define SPI_CPHA 			(1U << 0)
#define SPI_SSI				(1U << 8)
#define SPI_SSM				(1U << 9)

#define SPI_SPE				(1U << 6)


#define SPI_TXE_FLAG		(1U << 1)
#define SPI_BUSY_FLAG		(1U << 7)


void spi_config(void);
void spi_write(uint8_t data);
void spi_write_16bit(uint16_t data);
void spi_write_data(void);
void spi_write_command(void);
void spi_end_write(void);

#endif /* SPI_H_ */
