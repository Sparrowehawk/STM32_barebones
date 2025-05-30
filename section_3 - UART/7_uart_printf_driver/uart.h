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
#define UARTEN			(1U << 13)
#define SR_TXE			(1U << 7)

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ
#define BAUDRATE		115200

void uart2_tx_init(void);

#endif /* UART_H_ */
