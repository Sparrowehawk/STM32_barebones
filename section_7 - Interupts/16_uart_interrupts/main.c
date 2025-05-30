#include "uart.h"

char key;

#define GPIOAEN 		(1U << 0)
#define GPIOA_5			(1U << 5)
#define LED_PIN			GPIOA_5



int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b01 << 10);

	uart2_rxtx_init();

	while(1){
		key = uart2_read();

		if(key == '1'){
			GPIOA->ODR |= LED_PIN;
		} else {
			GPIOA->ODR &= ~LED_PIN;
		}

	}
}

