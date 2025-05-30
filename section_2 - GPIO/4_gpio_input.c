#include "stm32f103x6.h"

// I've set a btn to be on PB1

#define GPIOCEN			(1U << 4)
#define GPIOBEN 		(1U << 3)

#define PIN13			(1U << 13)
#define PIN13_BSRR		(1U << 29)

#define PIN1			(1U << 1)
#define PIN1_BSRR 		(1U << 17)

#define LED_PIN 		PIN13
#define BTN_PIN			PIN1

#define PIN13_OUTPUT	(0b0010 << 20)
#define PIN13_RST		(0xF << 20)

#define PIN1_INPUT		(0b0000 << 12)
#define PIN1_RST 		(0xF << 12)

int main(void)
{
	RCC->APB2ENR |= GPIOCEN;
	RCC->APB2ENR |= GPIOBEN;

	// Set PC13 as output pin
	GPIOC->CRH &= ~PIN13_RST;
	GPIOC->CRH |= PIN13_OUTPUT;

	// Set PB1 as input
	GPIOB->CRL &= ~PIN1_RST;
	GPIOB->CRL |= PIN1_INPUT;


	while(1)
	{
		// If btn is pressed
		if(GPIOB->IDR & BTN_PIN)
		{
			// Toggle LED
			GPIOC->BSRR = PIN13_BSRR;
		} else {
			// Toggle LED
			GPIOC->BSRR = PIN13;
		}
	}
}
