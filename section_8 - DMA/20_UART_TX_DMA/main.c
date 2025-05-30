#include "uart.h"

char key;

#define GPIOAEN 		(1U << 0)
#define GPIOA_5			(1U << 5)
#define LED_PIN			GPIOA_5

static void dma_callback(void);

int main(void)
{

	char message[31] = "HALLO FrOM STM32 DMA \n\r";

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b01 << 10);

	uart2_rxtx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 31 );

	while(1){

	}
}

static void dma_callback(void)
{
	GPIOA->ODR |= LED_PIN;

}

void DMA1_Stream6_IRQHandler(void)
{
	if(DMA1->HISR & HISR_TCIF6) {
		DMA1->HIFCR |= HIFCR_CTCIF6;

		dma_callback();
	}
}
