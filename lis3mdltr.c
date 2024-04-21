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


/*
 * function: lis3mdltr_GetDataRate
 *
 * description: read current settings
 *
 * return: current settings on success or -1 on failure.
 */
uint8_t lis3mdltr_GetDataRate(){
	status_t status = STATUS_ERROR;
	uint8_t reg_value;

	status = i2c_read( LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG1_ADDR, 1u, &reg_value );
	if (status == STATUS_OK)
		return reg_value;

	return -1;
}


/*
 * function: lis3mdltr_SetDataRate
 *
 * description: Read current settings, clear and update with new provided data.
 * 				0: 0.625Hz
 * 				1: 1.25Hz
 * 				2: 2.5Hz
 * 				3: 5Hz
 * 				4: 10Hz
 * 				5: 20Hz
 * 				6: 40Hz
 * 				7: 80Hz
 *
 * return: status success or failure.
 */
status_t lis3mdltr_SetDataRate(uint8_t data_rate){
	status_t status = STATUS_ERROR;
	// value should not exceed beyond 7
	if(data_rate < 8){
		uint8_t get_current_settings = lis3mdltr_GetDataRate();

		// clear DO2, DO1 and DO0 bits
		uint8_t new_settings = get_current_settings & ~0x1C;

		// set new data rate
		new_settings |= (data_rate << 2);
		status = i2c_write(LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG1_ADDR, 1U, &new_settings);
	}

	return status;
}




