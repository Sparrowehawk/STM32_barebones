#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

uint32_t sensor_value;

#define GPIOA_5				(1U<<5)
#define LED_PIN				GPIOA_5

static void tim2_callback(void);

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b01 << 10);

	uart2_rxtx_init();
	tim2_1hz_ISR();

	while(1);
}

static void tim2_callback(void)
{
	printf("A second has passed \n\r");
	GPIOA->ODR ^= LED_PIN;
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM2_SR;
	tim2_callback();

}
