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
	uint8_t rxBuff;

	status = i2c_read( LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG2_ADDR, 1u, &rxBuff );
	if (status == STATUS_OK)
		return rxBuff;

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
	uint8_t rxBuff;

	status = i2c_read( LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG1_ADDR, 1u, &rxBuff);
	if (status == STATUS_OK)
		return rxBuff;

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

/*
 * function: lis3mdltr_ReadInterruptConfig
 *
 * description: read interrupt config
 *
 * return: current settings on success or -1 on failure.
 */
uint8_t lis3mdltr_ReadInterruptConfig(){
	status_t status;
	uint8_t rxBuff;

	status = i2c_read( LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG3_ADDR, 1u, &rxBuff );
	if (STATUS_OK == status)
	{
		return rxBuff;
	}
	return -1;
}

/*
 * function: lis3mdltr_EnableInterrupt
 *
 * description: set IE bit
 *
 * return: status success or failure.
 */
status_t lis3mdltr_EnableInterrupt(){
	status_t status = STATUS_ERROR;
	uint8_t rxBuff = lis3mdltr_ReadInterruptConfig();
	uint8_t enable_intr = rxBuff | 0x80; 	// set IE bit
	status = i2c_write(LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG3_ADDR, 1u, &enable_intr);
	return status;
}

/*
 * function: lis3mdltr_DisableInterrupt
 *
 * description: clear IE bit
 *
 * return: status success or failure.
 */
status_t lis3mdltr_DisableInterrupt(){
	status_t status = STATUS_ERROR;
	uint8_t rxBuff = lis3mdltr_ReadInterruptConfig();
	uint8_t enable_intr = rxBuff & ~0x80; 	// clear IE bit
	i2c_write(LIS3MDLTR_I2C_ADDR, LIS3MDLTR_CTRL_REG3_ADDR, 1u, &enable_intr);
	return status;
}

/*
 * function: lis3mdltr_read_axis_data
 *
 * description: read axis data.
 *
 * return: requested axis data.
 */
uint16_t lis3mdltr_read_axis_data(axis ax){
	uint8_t l_reg, h_reg;
	switch(ax){
		case AXIS_X:
			l_reg = 0x28; // OUT_X_L
			h_reg = 0x29; // OUT_X_H
			break;

		case AXIS_Y:
			l_reg = 0x2A; // OUT_Y_L
			h_reg = 0x2B; // OUT_Y_H
			break;

		case AXIS_Z:
			l_reg = 0x2C; // OUT_Z_L
			h_reg = 0x2D; // OUT_Z_H
			break;

		default:
			return 0; // return for undefined axis

	}

	uint8_t low_data_byte, high_data_byte;
	i2c_read( LIS3MDLTR_I2C_ADDR, l_reg, 1u, &low_data_byte );
	i2c_read( LIS3MDLTR_I2C_ADDR, h_reg, 1u, &high_data_byte );

	//combine data
	uint16_t axis_data = (high_data_byte << 8) | low_data_byte;
	return axis_data;
}


