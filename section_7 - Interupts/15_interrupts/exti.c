/*
 * exti.c
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#include "exti.h"

void pc13_exti_init(void)
{
	// Disable global interrupt
	__disable_irq();

	// Configure PC13 for clock and input mode
	RCC->AHB1ENR |= GPIOCEN;

	// Enable clock for SYSFGP
	RCC->APB2ENR |= SYSCFGEN;

	// Select PC13 for EXTI13
	GPIOC->MODER &= PIN_13_INPUT;
	SYSCFG->EXTICR[3] |= EXTICR4_C13;

	// Unmask interrupt
	EXTI->IMR |= EXTI_IMR_C13;

	// Falling edge
	EXTI->FTSR |= FALLING_EDGE_C13;

	// Enable EXTI13 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);


	// Enable global interrupt
	__enable_irq();
}