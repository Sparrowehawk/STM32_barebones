/*
 * adc.h
 *
 *  Created on: May 28, 2025
 *      Author: Hamid
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include <stdint.h>

#define ADCEN			(1U << 8)
#define GPIOAEN			(1U << 0)
#define ADC_CH1			(1U << 0)
#define ADC_LEN			(0b0000 << 20)
#define CR2_ADC_ON		(1U << 0)
#define CR2_SWST		(1U << 30)
#define SR_EOC			(1U << 1)

void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
