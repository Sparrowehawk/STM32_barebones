/*
 * systick.h
 *
 *  Created on: May 29, 2025
 *      Author: HJ
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#define SYSTICK_LOAD_VAL			16000		// 1ms
#define SYSTICK_CSR_EN				(1U << 0)
#define SYS_CSR_CLK_SRC			    (1U << 2)
#define CSR_COUNT_FLAG				(1U << 16)

void systickDelayMS(int delay);
void systick_1hz_ISR(void);

#define ONE_SEC_LOAD				16000000
#define SYSTICK_CSR_ISR				(1U << 1)

#endif /* SYSTICK_H_ */
