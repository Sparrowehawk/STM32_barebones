/*
 * i2c.c
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#include "i2c.h"

void I2C1_init(void)
{
	// Enable clock to GPIOB
	RCC->AHB1ENR |= GPIOBEN;

	// Alt func mapping AF04
	// PB9 SDA / PB8 SCL

	GPIOB->MODER &= ~PB8_CLR;
	GPIOB->MODER &= ~PB9_CLR;

	GPIOB->MODER |= PB8_AF;
	GPIOB->MODER |= PB9_AF;

	// Set open drain
	GPIOB->OTYPER |= PB8_OTYPER;
	GPIOB->OTYPER |= PB9_OTYPER;

	// Enable pullup for PB9 PB10
	GPIOB->PUPDR &= ~PB8_PULLUP_CLR;
	GPIOB->PUPDR &= ~PB9_PULLUP_CLR;

	GPIOB->PUPDR |= PB8_PULLUP;
	GPIOB->PUPDR |= PB9_PULLUP;

	GPIOB->AFR[1] &= ~PB8_AFR_CLR;
	GPIOB->AFR[1] &= ~PB9_AFR_CLR;

	GPIOB->AFR[1] |= PB8_AFR;
	GPIOB->AFR[1] |= PB9_AFR;

	// Enable clock to I2C1 (APB1)
	RCC->APB1ENR |= I2C1_EN;

	// Enter and leave reset
	I2C1->CR1 |= I2C_SWRST;
	I2C1->CR1 &= ~I2C_SWRST;

	// Set clock speed
	I2C1->CR2 &= ~I2C_SPEED_CLR;
	I2C1->CR2 |= I2C_SPEED;

	I2C1->CCR = I2C_100KHZ;
	I2C1->TRISE = SD_MODE_MAX_RISE;

	I2C1->CR1 |= I2C_PE_EN;
}


void I2C1_readByte(char saddr, char maddr, char* data)
{
	volatile int tmp;

	while(I2C1->SR2 & I2C_BUSY);

	I2C1->CR1 |= I2C_START_BIT;
	while(!(I2C1->SR1 & I2C_START_FLAG));

	I2C1->DR = saddr << 1;
	while(!(I2C1->SR1 & I2C_ADDR_FLAG));

	tmp = I2C1->SR2;

	I2C1->DR = maddr;
	while(!(I2C1->SR1 & I2C_TXE_FLAG));

	I2C1->CR1 |= I2C_START_BIT;
	while(!(I2C1->SR1 & I2C_START_FLAG));

	I2C1->DR = saddr << 1 | 1;
	while(!(I2C1->SR1 & I2C_ADDR_FLAG));

	I2C1->CR1 &= ~I2C_ACK_BIT;
	tmp = I2C1->SR2;
	I2C1->CR1 |= I2C_STOP_BIT;
	while(!(I2C1->SR1 & I2C_RXNE_FLAG));

	*data++ = I2C1->DR;
}

void I2C1_burstRead(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	while(I2C1->SR2 & I2C_BUSY);

	I2C1->CR1 |= I2C_START_BIT;
	while(!(I2C1->SR1 & I2C_START_FLAG));

	I2C1->DR = saddr << 1;
	while(!(I2C1->SR1 & I2C_ADDR_FLAG));

	tmp = I2C1->SR2;

	I2C1->DR = maddr;
	while(!(I2C1->SR1 & I2C_TXE_FLAG));

	I2C1->CR1 |= I2C_START_BIT;
	while(!(I2C1->SR1 & I2C_START_FLAG));

	I2C1->DR = saddr << 1 | 1;
	while(!(I2C1->SR1 & I2C_ADDR_FLAG));
	tmp = I2C1->SR2;
	I2C1->CR1 |= I2C_ACK_BIT;

	while(n>0U){
		if(n == 1) {
			I2C1->CR1 &= ~I2C_ACK_BIT;
			I2C1->CR1 |= I2C_STOP_BIT;
			while(!(I2C1->SR1 & I2C_RXNE_FLAG));

			*data++ = I2C1->DR;
		} else {
			while(!(I2C1->SR1 & I2C_RXNE_FLAG));
			*data++ = I2C1->DR;
		}

		n--;
	}
}

void I2C1_burstWrite(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	while(I2C1->SR2 & I2C_BUSY);

	I2C1->CR1 |= I2C_START_BIT;
	while(!(I2C1->SR1 & I2C_START_FLAG));

	I2C1->DR = saddr << 1;
	while(!(I2C1->SR1 & I2C_ADDR_FLAG));

	tmp = I2C1->SR2;
	while(!(I2C1->SR1 & I2C_TXE_FLAG));
	I2C1->DR = maddr;

	for(int i = 0; i<n; i++) {
		while(!(I2C1->SR1 & I2C_TXE_FLAG));
		I2C1->DR = *data++;

	}


	while(!(I2C1->SR1 & I2C_BTF_FLAG));
	I2C1->CR1 |= I2C_STOP_BIT;

}


