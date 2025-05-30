#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

int timeStamp = 0;

int main(void)
{

	// Set a wire between PA5 and PA6 (D13 and D12)


	tim2_output_compare();
	tim3_input_capture();

	while(1){

		while(!(TIM3->SR & SR_CC1IF));
		timeStamp = TIM3->CCR1;

	}
}
