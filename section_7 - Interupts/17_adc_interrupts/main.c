#include "uart.h"
#include "adc.h"

uint32_t sensor_value;
static void ADC_callback(void);

int main(void)
{
	uart2_rxtx_init();
	pa1_adc_ISR_init();
	start_conversion();

	while(1);
}

static void ADC_callback(void)
{
	sensor_value = ADC1->DR;
	printf("Sensor value: %d \n\r", (int)sensor_value);
}

void ADC_IRQHandler(void)
{
	if((ADC1->SR |= SR_EOC) != 0) {
		ADC1->SR &= ~SR_EOC;

		ADC_callback();
	}
}
