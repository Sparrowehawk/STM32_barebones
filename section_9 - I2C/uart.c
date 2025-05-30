/*
 * uart.c
 *
 *  Created on: May 28, 2025
 *      Author: Hamid
 */

#include "uart.h"

int __io_putchar(int ch);
void uart2_write(int ch);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate);
static uint16_t uart_baudrate_div(uint32_t periphClk, uint32_t baudRate);

void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len)
{
	// Enable clock to DMA
	RCC->AHB1ENR |= DMA1_EN;

	// Disable DMA1 S6
	DMA1_Stream6->CR &= ~DMA_SCR_EN;

	while(DMA1_Stream6->CR & DMA_SCR_EN);

	// Clear all interrupt flags of S6
	DMA1->HIFCR &= ~S6_CLR_ALL;

	// Set destination buffer
	DMA1_Stream6->PAR = dst;

	// Set source buffer
	DMA1_Stream6->M0AR = src;

	// Set length
	DMA1_Stream6->NDTR = len;

	// Select S6 Ch4
	DMA1_Stream6->CR &= ~DMA_CR_CLR_SEl;
	DMA1_Stream6->CR |= DMA_CR_CH4;

	// Increment memory
	DMA1_Stream6->CR |= DMA_INC;

	// Config transfer direction, mem -> perph
	DMA1_Stream6->CR &= ~DMA_DIR_CLR;
	DMA1_Stream6->CR |= DMA_DIR_M2P;

	// Enable DMA transfer complete interrupt
	DMA1_Stream6->CR |= DMA_TCIE_EN;

	// Enable direct mode and disable FIFO
	DMA1_Stream6->FCR = 0;

	// Enable DMA1 S6
	DMA1_Stream6->CR |= DMA_EN;

	//Enable UASRT2 TX
	USART2->CR3 |= USART_DMA_TX_EN;

	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void uart2_rxtx_init(void)
{

	/* Configure uart GPIO pins
	 * Enable clock to PA
	 * Set PA2 and PA3 to alt func mode
	 * Set PA2 alt func type UART_TX(AF07)	*/

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= ((0b10 << 4) | (0b10 << 6));
	GPIOA->AFR[0]|= ((0b0111 << 8) | (0b0111 << 12));


	/* Configure UART module
	 * Enable clock acsess to uart2
	 * conf baudrate
	 * conf transfer direction
	 * enable uart module
	*/

	RCC->APB1ENR |= USART2EN;
	uart_set_baudrate(USART2, APB1_CLK, BAUDRATE);
	USART2->CR1 = (CR1_TE | CR1_RE);
	USART2->CR1 |= UARTEN;

}

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

char uart2_read(void)
{
	while(!(USART2->SR & SR_RXNE));
	return USART2->DR;
}

void uart2_write(int ch)
{
	// Make sure TX is empty
	while(!(USART2->SR & SR_TXE));

	// Write to TX
	USART2->DR = ch & 0xFF;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate)
{
	USARTx->BRR = uart_baudrate_div(periphClk, baudRate);


}

static uint16_t uart_baudrate_div(uint32_t periphClk, uint32_t baudRate)
{
	return ((periphClk + (baudRate / 2U)) / baudRate);
}

