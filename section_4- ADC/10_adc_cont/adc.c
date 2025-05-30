/*
 * adc.c
 *
 *  Created on: May 28, 2025
 *      Author: Hamid
 */

#include "adc.h"

void pa1_adc_init(void)
{
	// Enable PA1 to be adc

	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA1 to be analogue
	GPIOA->MODER |= (0b11 << 2);

	// Conf ADC module
	// Enable clock access to ADC
	RCC->APB2ENR |= ADCEN;

	// Configure ADC params
	// Conversion sequence start
	ADC1->SQR3 = ADC_CH1;
	// Conversion sequence len
	ADC1->SQR1 = ADC_LEN;

	// Enable ADC module
	ADC1->CR2 |= CR2_ADC_ON;
}

void start_conversion(void)
{
	// Enable continuous
	ADC1->CR2 |= CR2_CONT;

	// Start conversion
	ADC1->CR2 |= CR2_SWST;
}
uint32_t adc_read(void)
{
	// wait for conversion
	while(!(ADC1->SR & SR_EOC));

	return(ADC1->DR);

}
