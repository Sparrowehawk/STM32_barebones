/*
 * tim.c
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#include "tim.h"

void tim2_1hz_init(void)
{
	// Enable clock acsess
	RCC->APB1ENR |= TIM2ENR;

	// Set prescaler val
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1600 = 10 000

	// Set ARR val
	TIM2->ARR = 10000 - 1 ;

	// declare timer counter
	TIM2->CNT = 0;

	// Enable timer
	TIM2->CR1 |= TIM2EN;

}
