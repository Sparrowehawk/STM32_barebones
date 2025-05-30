#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

uint32_t sensor_value;

#define GPIOA_5				(1U<<5)
#define LED_PIN				GPIOA_5


int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b01 << 10);

	uart2_rxtx_init();
	tim2_1hz_init();

	while(1){

		while(!(TIM2->SR & TIM2_SR));

		TIM2->SR &= ~TIM2_SR;

		printf("A second has passed \n\r");
		GPIOA->ODR ^= LED_PIN;
	}
}
