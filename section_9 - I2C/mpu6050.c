/*
 * mpu6050.c
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#include "mpu6050.h"

void mpu6050_init(void)
{
	char data = 0x00;
	I2C1_burstWrite(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data);
	systickDelayMS(50000);

	data = 0x01;
	I2C1_burstWrite(MPU6050_ADDR, MPU6050_CONFIG, 1, &data);

	data = 0x09;
	I2C1_burstWrite(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 1, &data);

	data = 0x00;
	I2C1_burstWrite(MPU6050_ADDR, MPU6050_GYRO_CONFIG, 1, &data);
	I2C1_burstWrite(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1, &data);


}

void mpu6050_read_accel(accel_data_t* accel)
{
    char raw_data[6];
    I2C1_burstRead(MPU6050_ADDR, MPU6050_ACCEL, 6, raw_data);

    accel->x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    accel->y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    accel->z = (int16_t)((raw_data[4] << 8) | raw_data[5]);
}

void mpu6050_read_temp(temp_data_t* temp)
{
    char raw_data[2];
    I2C1_burstRead(MPU6050_ADDR, MPU6050_TEMP, 2, raw_data);

    temp->temperature = (int16_t)((raw_data[0] << 8) | raw_data[1]);
}

void mpu6050_read_gyro(gyro_data_t* gyro)
{
    char raw_data[6];
    I2C1_burstRead(MPU6050_ADDR, MPU6050_GYRO, 6, raw_data);

    gyro->x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    gyro->y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    gyro->z = (int16_t)((raw_data[4] << 8) | raw_data[5]);

}
