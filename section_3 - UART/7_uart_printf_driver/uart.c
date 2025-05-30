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


int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_tx_init(void)
{

	/* Configure uart GPIO pins
	 * Enable clock to PA
	 * Set PA2 to alt func mode
	 * Set PA2 alt func type UART_TX(AF07)	*/

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (0b10 << 4);
	GPIOA->AFR[0]|= (0b0111 << 8);


	/* Configure UART module
	 * Enable clock acsess to uart2
	 * conf baudrate
	 * conf transfer direction
	 * enable uart module
	*/

	RCC->APB1ENR |= USART2EN;
	uart_set_baudrate(USART2, APB1_CLK, BAUDRATE);
	USART2->CR1 = CR1_TE;
	USART2->CR1 |= UARTEN;

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
