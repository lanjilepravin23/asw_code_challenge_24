/*
 * lis3mdltr.h
 *
 *  Created on: 21 Apr 2024
 *      Author: pubu
 */

#ifndef LIS3MDLTR_H_
#define LIS3MDLTR_H_

#include "i2c.h"

/*
 * MACROS
 */
#define LIS3MDLTR_I2C_ADDR	0x1E
#define LIS3MDLTR_DEVICE_ID	0x3D

/*
 * Registers
 */
#define LIS3MDLTR_WHOAMI_REG_ADDR		0x0F		// device id register
#define LIS3MDLTR_CTRL_REG1_ADDR		0x20		// get/set data rate
#define LIS3MDLTR_CTRL_REG2_ADDR		0x21		// full scale config register

/*
 * functions
 */
status_t lis3mdltr_init(void);
uint8_t lis3mdltr_GetFullScaleConfig(void);
uint8_t lis3mdltr_GetDataRate(void);
status_t lis3mdltr_SetDataRate(uint8_t data_rate);


#endif /* LIS3MDLTR_H_ */
