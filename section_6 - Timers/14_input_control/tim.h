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

#define TIM_EN				(1U << 0)

#define TIM2ENR				(1U << 0)
#define TIM3ENR 			(1U << 1)

#define TIM2_SR				(1U << 0)

#define TIM2_CH1_CCR_RST	(0b111 << 4)
#define TIM2_CH1_CCR		(0b011 << 4)
#define TIM2_CH1_CCER		(1U << 0)

#define GPIOAEN				(1U << 0)

#define PA5_MODE_RST		(0b11 << 10)
#define PA5_MODE_ALT		(0b10 << 10)

#define PA6_MODE_RST		(0b11 << 12)
#define PA6_MODE_ALT		(0b10 << 12)

#define PIN5_AFR_RST		(0b1111 << 20)
#define PIN5_AFR			(0b0001 << 20)

#define PIN6_AFR_RST		(0b1111 << 24)
#define PIN6_AFR			(0b0010 << 24)

#define CC1S_RST			(0b11 << 0)
#define CC1S				(0b01 << 0)
#define CCER_CC1E			(1U << 0)

#define SR_CC1IF			(1U << 1)

void tim2_1hz_init(void);
void tim2_output_compare(void);
void tim3_input_capture(void);

#endif /* TIM_H_ */
