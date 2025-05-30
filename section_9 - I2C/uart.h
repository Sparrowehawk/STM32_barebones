/*
 * uart.h
 *
 *  Created on: May 28, 2025
 *      Author: Hamid
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

// APB1 line
// PA2 TX, PA3 RX under AF07

#define GPIOAEN			(1U << 0)
#define USART2EN		(1U << 17)
#define CR1_TE			(1U << 3)
#define CR1_RE			(1U << 2)
#define UARTEN			(1U << 13)
#define SR_TXE			(1U << 7)
#define SR_RXNE 		(1U << 5)

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ
#define BAUDRATE		115200

void uart2_rxtx_init(void);
char uart2_read(void);
void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len);

#define DMA1_EN			(1U << 21)
#define DMA_SCR_EN		(1U << 0)

#define S6_CLR_ALL		(0b000000 << 16)
#define DMA_CR_CLR_SEl	(0b000 << 25)
#define DMA_CR_CH4		(0b100 << 25)
#define DMA_INC			(1U << 10)
#define DMA_DIR_CLR		(0b00 << 6)
#define DMA_DIR_M2P		(0b01 << 6)
#define DMA_TCIE_EN		(1U << 4)
#define DMA_EN			(1U << 0)

#define USART_DMA_TX_EN	(1U << 7)
#define USART_DMA_RX_EN	(1U << 6)

#define HISR_TCIF6		(1U << 21)
#define HIFCR_CTCIF6	(1U << 21)

#endif /* UART_H_ */
