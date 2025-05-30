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

void tim2_1hz_init(void);
void tim2_1hz_ISR(void);

#define TIM_DIER_ISR		(1U << 0)

#endif /* TIM_H_ */
