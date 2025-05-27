#include "stm32f103x6.h"

#define GPIOCEN			(1U << 4)
#define PIN13			(1U << 13)
#define LED_PIN 		PIN13

#define PIN13_OUTPUT	(0b0010 << (20))
#define PIN13_RST		(0xF << 20)

int main(void)
{
	RCC->APB2ENR |= GPIOCEN;

	// Set PC13 as output pin
	GPIOC->CRH &= ~PIN13_RST;
	GPIOC->CRH |= PIN13_OUTPUT;

	while(1)
	{
		GPIOC->ODR |= LED_PIN;

	}
}
