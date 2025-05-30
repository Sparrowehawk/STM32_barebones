/*
 * tim.h
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32f4xx.h"
#include <stdint.h>

#define TIM2ENR				(1U << 0)
#define TIM2EN				(1U << 0)

#define TIM2_SR				(1U << 0)

#define TIM2_CH1_CCR_RST	(0b111 << 4)
#define TIM2_CH1_CCR		(0b011 << 4)
#define TIM2_CH1_CCER		(1U << 0)

#define GPIOAEN			(1U << 0)
#define PIN5_RST		(0b11 << 10)
#define PIN5_ALT_MODE	(0b10 << 10)
#define PIN5_AFR_RST	(0b1111 << 20)
#define PIN5_AFR		(0b0001 << 20)

void tim2_1hz_init(void);
void tim2_output_compare(void);

#endif /* TIM_H_ */
