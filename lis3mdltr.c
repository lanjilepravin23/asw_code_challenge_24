/*
 * lis3mdltr.c
 *
 *  Created on: 21 Apr 2024
 *      Author: Pravin Lanjile
 */

#include "lis3mdltr.h"


/*
 * function: lis3mdltr_init
 *
 * description: Read and compare device identification using WHO_AM_I(dummy)
 * 				  register.
 *
 * return: status
 */
status_t lis3mdltr_init(){
	status_t status = STATUS_ERROR;
	uint8_t rxBuff;

	if(STATUS_OK == i2c_read(LIS3MDLTR_I2C_ADDR, LIS3MDLTR_WHOAMI_REG_ADDR, 1u, &rxBuff))
	{
		if(rxBuff == LIS3MDLTR_DEVICE_ID){
			status = STATUS_OK;
		}
	}

	return status;
}

/*
 * function: lis3mdltr_GetFullScaleConfig
 *
 * description: Read current full scale config using CTRL_REG2 register
 *
 * return: current full_scale_config value on success or -1 on failure.
 */
uint8_t lis3mdltr_GetFullScaleConfig(){
	status_t status = STATUS_ERROR;
	uint8_t reg_value;

	status = i2c_read( LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG2_ADDR, 1u, &reg_value );
	if (status == STATUS_OK)
		return reg_value;

	return -1;
}






