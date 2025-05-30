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
	TIM2->CR1 |= TIM_EN;

}

void tim2_output_compare(void)
{
	// Enable clock to GPIOA5
	RCC->AHB1ENR |= GPIOAEN;

	// Enable PA5 to be alternate mode
	GPIOA->MODER &= ~PA5_MODE_RST;
	GPIOA->MODER |= PA5_MODE_ALT;

	GPIOA->AFR[0] &= ~PIN5_AFR_RST;
	GPIOA->AFR[0] |= PIN5_AFR;

	// Enable clock acsess
	RCC->APB1ENR |= TIM2ENR;

	// Set prescaler val
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1600 = 10 000

	// Set ARR val
	TIM2->ARR = 10000 - 1 ;

	// Set output compare toggle mode
	TIM2->CCMR1 &= ~TIM2_CH1_CCR_RST;
	TIM2->CCMR1 |= TIM2_CH1_CCR;

	// Enable tim2 ch1
	TIM2->CCER |= TIM2_CH1_CCER;

	// declare timer counter
	TIM2->CNT = 0;

	// Enable timer
	TIM2->CR1 |= TIM_EN;

}

void tim3_input_capture(void)
{
	// Tim3 Ch1 is PA6 on AF02

	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Enable PA5 to be alternate mode
	GPIOA->MODER &= ~PA6_MODE_RST;
	GPIOA->MODER |= PA6_MODE_ALT;

	GPIOA->AFR[0] &= ~PIN6_AFR_RST;
	GPIOA->AFR[0] |= PIN6_AFR;

	// Enable clock acsess
	RCC->APB1ENR |= TIM3ENR;

	// Set prescaler val
	TIM3->PSC = 16000 - 1; // 16 000 000 / 1600 = 10 000

	// Set ch1 to capture at every edge
	TIM3->CCMR1 &= ~CC1S_RST;
	TIM3->CCMR1 |= CC1S;


	// Set ch1 to caputure at rising edge
	TIM3->CCER |= CCER_CC1E;

	// Enable timer 3
	TIM3->CR1 |= TIM_EN;


}

