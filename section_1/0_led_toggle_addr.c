// LED is on PC13

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

// Could also just be 0b0010 << 20
#define PIN13_MODE	 	((0U << 20) | (1u << 21))
#define PIN13_CONF		((0U << 22) | (0u << 23))
#define PIN13_RST		(0xF << 20)						// Ensures that the 4 bits are clear, 0xF = 0

#define GPIO_ODR_OFFSET (0x0C)
#define GPIO_ODR_BASE	(*(volatile unsigned int *)(PORTC_BASE + GPIO_ODR_OFFSET))
#define PIN13			(1U << 13)
#define LED_PIN 		PIN13

// 0x4001 1000 <=> 0x4001 1400
// Guess is PC13 is 0x4001 1340


int main (void)
{
	// Enable clock to GPIOC
	RCC_APB2EN_R |= IOPCEN;

	// Set PC13 as output pin
	GPIO_CRH_BASE &= ~PIN13_RST;
	GPIO_CRH_BASE |= PIN13_MODE | PIN13_CONF;


	while(1)
	{
		// Toggle LED
		GPIO_ODR_BASE ^= LED_PIN;

		for(int i = 0; i < 100000; i++)
		{

		}

	}
}

