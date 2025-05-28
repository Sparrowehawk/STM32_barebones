#include "uart.h"

int main(void)
{

	uart2_tx_init();

	while(1){
		printf("magic in the air\n\r");

	}
}

