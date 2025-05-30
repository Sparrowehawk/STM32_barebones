#include "uart.h"
#include "i2c.h"
#include "mpu6050.h"
#include "systick.h"

char key;

#define GPIOAEN 		(1U << 0)
#define GPIOA_5			(1U << 5)
#define LED_PIN			GPIOA_5

static void toggleLED(void);

uint16_t tempr;

int main(void)
{


	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b01 << 10);

	uart2_rxtx_init();
	I2C1_init();
	mpu6050_init();

    accel_data_t accel;
    temp_data_t temp;
    gyro_data_t gyro;


    while(1)
    {
        mpu6050_read_accel(&accel);
        mpu6050_read_gyro(&gyro);
        mpu6050_read_temp(&temp);

        tempr = temp.temperature;

        printf("ACCEL: X=%d, Y=%d, Z=%d\r\n", accel.x, accel.y, accel.z);
        printf("GYRO : X=%d, Y=%d, Z=%d\r\n", gyro.x, gyro.y, gyro.z);
        printf("TEMP : 0x%04X\r\n", tempr);  // HEX format
        printf("--------------------------\r\n");
        toggleLED();

        systickDelayMS(500);  // Read every 0.5s
    }
}

static void toggleLED(void)
{
	GPIOA->ODR |= LED_PIN;

}
