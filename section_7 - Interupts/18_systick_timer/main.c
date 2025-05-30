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
	systick_1hz_ISR();

	while(1);
}

void systick_callback(void){
	printf("A second has passed \n\r");
	GPIOA->ODR ^= LED_PIN;
}

void SysTick_Handler(void)
{
	systick_callback();
}
