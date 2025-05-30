/*
 * mpu6050.h
 *
 *  Created on: May 30, 2025
 *      Author: HJ
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "stm32f4xx.h"
#include <stdint.h>

#include "i2c.h"

#define MPU6050_ADDR			0x68

#define MPU6050_PWR_MGMT_1	    0x6B
#define MPU6050_SMPLRT_DIV	    0x19
#define MPU6050_CONFIG         	0x1A
#define MPU6050_GYRO_CONFIG    	0x1B
#define MPU6050_ACCEL_CONFIG   	0x1C
#define MPU6050_WHO_AM_I       	0x75

#define MPU6050_ACCEL          	0x3B
#define MPU6050_TEMP           	0x41
#define MPU6050_GYRO           	0x43

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} accel_data_t;

typedef struct {
    int16_t temperature;
} temp_data_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} gyro_data_t;

void mpu6050_init(void);
void mpu6050_read_accel(accel_data_t* accel);
void mpu6050_read_temp(temp_data_t* temp);
void mpu6050_read_gyro(gyro_data_t* gyro);


#endif /* MPU6050_H_ */
