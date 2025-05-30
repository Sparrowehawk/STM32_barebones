/*
 * exti.h
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOCEN				(1U << 2)
#define PIN_13_INPUT		(0b00 << 26)
#define SYSCFGEN			(1U << 14)
#define EXTICR4_C13			(0b0010 << 4)
#define EXTI_IMR_C13		(1U << 13)
#define FALLING_EDGE_C13	(1U << 13)

void pc13_exti_init(void);

#define LINE_13				(1U << 13)

#endif /* EXTI_H_ */
