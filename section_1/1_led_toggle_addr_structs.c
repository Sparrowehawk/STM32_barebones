// LED is on PC13
#include <stdint.h>


#define PERIPH_BASE 	(0x40000000UL)
#define PORTC_OFFSET 	(0x00011000UL)

#define PORTC_BASE		(PERIPH_BASE + PORTC_OFFSET)

#define RCC_OFFSET		(0x00021000UL)
#define RCC_BASE 		(PERIPH_BASE + RCC_OFFSET)

// Offset for EN is 0x18

#define APB2EN_R_OFSET 	(0x18UL)
#define RCC_APB2EN_R  	(*(volatile unsigned int *) (RCC_BASE + APB2EN_R_OFSET))

#define IOPCEN 			(1U << 4)

#define GPIO_CRL_OFFSET (0x00UL)						// Pins 0 ~ 7
#define GPIO_CRH_OFFSET (0x04UL)						// Pins 8 ~ 15

#define GPIO_CRL_BASE 	(*(volatile unsigned int *)(PORTC_BASE + GPIO_CRL_OFFSET))
#define GPIO_CRH_BASE   (*(volatile unsigned int *)(PORTC_BASE + GPIO_CRH_OFFSET))

#define PIN13_OUTPUT	(0b0010 << (20))
#define PIN13_RST		(0xF << 20)						// Ensures that the 4 bits are clear, 0xF = 0

#define GPIO_ODR_OFFSET (0x0C)
#define GPIO_ODR_BASE	(*(volatile unsigned int *)(PORTC_BASE + GPIO_ODR_OFFSET))
#define PIN13			(1U << 13)
#define LED_PIN 		PIN13

// 0x4001 1000 <=> 0x4001 1400
// Guess is PC13 is 0x4001 1340

#define __IO volatile

typedef struct
{
	__IO uint32_t CRL;
	__IO uint32_t CRH;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
//	__IO uint32_t BSRR;
//	__IO uint32_t BRR;
//	__IO uint32_t LCKR;
}GPIOC_TypeDef;

typedef struct{
//	__IO uint32_t CR;
//	__IO uint32_t CFGR;
//	__IO uint32_t CIR;
//	__IO uint32_t APB2RSTR;
//	__IO uint32_t APB1RSTR;
//	__IO uint32_t AHBENR;
	__IO uint32_t dummy[6];
	__IO uint32_t APB2ENR;
//	__IO uint32_t APB1ENR;
//	__IO uint32_t BDCR;
//	__IO uint32_t CSR;
} RCC_TypeDef;

#define RCC				((RCC_TypeDef*) RCC_BASE)
#define GPIOC			((GPIOC_TypeDef*) PORTC_BASE)

int main (void)
{
	// Enable clock to GPIOC
	RCC->APB2ENR |= IOPCEN;

	// Set PC13 as output pin
	GPIOC->CRH &= ~PIN13_RST;
	GPIOC->CRH |= PIN13_OUTPUT;

	while(1)
	{
		// Toggle LED
		GPIOC->ODR ^= LED_PIN;

		for(int i = 0; i < 100000; i++)
		{

		}

	}
}
