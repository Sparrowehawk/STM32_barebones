/*
 * systick.c
 *
 *  Created on: May 29, 2025
 *      Author: HJ
 */

#include "systick.h"

void systickDelayMS(int delay)
{
	// Conf systick
	// Reload with num of clocks per ms
	SysTick->LOAD= SYSTICK_LOAD_VAL;

	// Clear current value
	SysTick->VAL = 0;

	// Enable systick
	SysTick->CTRL = SYSTICK_CSR_EN | SYS_CSR_CLK_SRC;

	for(int i = 0; i < delay; i++){
		// Wait until count flag is set

		while((SysTick->CTRL & CSR_COUNT_FLAG) == 0);

	}

	SysTick->CTRL = 0;

}

void systick_1hz_ISR(void)
{
	// Conf systick
	// Reload with num of clocks per ms
	SysTick->LOAD= ONE_SEC_LOAD - 1;

	// Clear current value
	SysTick->VAL = 0;

	// Enable systick
	SysTick->CTRL = SYSTICK_CSR_EN | SYS_CSR_CLK_SRC | SYSTICK_CSR_ISR;


}

