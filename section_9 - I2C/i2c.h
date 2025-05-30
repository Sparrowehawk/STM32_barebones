/*
 * i2c.h
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOBEN				(1U << 1)
#define I2C1_EN				(1U << 21)

#define PB8_CLR				(0b11 << 16)
#define PB8_AF				(0b10 << 16)
#define PB8_AFR_CLR			(0b0100 << 0)
#define PB8_AFR				(0b0100 << 0)
#define PB8_OTYPER			(1U << 8)
#define PB8_PULLUP_CLR		(0b11 << 16)
#define PB8_PULLUP			(0b01 << 16)

#define PB9_CLR				(0b11 << 18)
#define PB9_AF				(0b10 << 18)
#define PB9_AFR_CLR			(0b0100 << 4)
#define PB9_AFR				(0b0100 << 4)
#define PB9_OTYPER			(1U << 9)
#define PB9_PULLUP_CLR		(0b11 << 18)
#define PB9_PULLUP			(0b01 << 18)

#define I2C_SWRST			(1U << 15)
#define I2C_SPEED_CLR		(0b111111 << 0)
#define I2C_SPEED			(0b010000 << 0)
#define I2C_100KHZ			80
#define SD_MODE_MAX_RISE	17
#define I2C_PE_EN			(1U << 0)

#define I2C_BUSY			(1U << 1)
#define I2C_START_BIT		(1U << 8)
#define I2C_STOP_BIT		(1U << 9)
#define I2C_ACK_BIT			(1U << 10)

#define I2C_START_FLAG		(1U << 0)
#define I2C_ADDR_FLAG		(1U << 1)
#define I2C_TXE_FLAG		(1U << 7)
#define I2C_RXNE_FLAG		(1U << 6)
#define I2C_BTF_FLAG		(1U << 2)

void I2C1_init(void);
void I2C1_readByte(char saddr, char maddr, char* data);
void I2C1_burstRead(char saddr, char maddr, int n, char* data);
void I2C1_burstWrite(char saddr, char maddr, int n, char* data);

#endif /* I2C_H_ */
