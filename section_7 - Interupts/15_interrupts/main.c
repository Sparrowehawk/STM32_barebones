#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIOAEN			(1U << 0)

#define PA5_MODE_RST		(0b11 << 10)
#define PA5_MODE_OUT		(0b01 << 10)

#define PIN5				(1U << 5)

static void exti_callback(void);

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &= ~PA5_MODE_RST;
	GPIOA->MODER |= PA5_MODE_OUT;

	pc13_exti_init();
	uart2_rxtx_init();

	while(1){

	}
}

static void exti_callback(void)
{
	printf("BTN pressed ... \n\r");
	GPIOA->ODR ^= PIN5;
}

void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & LINE_13) != 0){
		EXTI->PR |= LINE_13;
		exti_callback();
	}
}
