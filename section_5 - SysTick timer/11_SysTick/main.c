#include "uart.h"
#include "adc.h"
#include "systick.h"

uint32_t sensor_value;

#define GPIOAEN				(1U<<0)
#define GPIOA_5				(1U<<5)
#define LED_PIN				GPIOA_5


int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b01 << 10);

	uart2_rxtx_init();

	while(1){

		printf("A second has passed \n\r");
		systickDelayMS(1000);
		GPIOA->ODR ^= LED_PIN;
	}
}
