/*
 * main.c
 *
 *  Created on: 21 Apr 2024
 *      Author: pubu
 */
#include <stdio.h>
#include "lis3mdltr.h"

#define DATA_RATE_SETTING 2
int main(){
	uint8_t get_val;
	uint16_t get_axis_data;
	status_t status;

	// Init
	status = lis3mdltr_init();
	if (status == STATUS_OK)
	{
		printf("[DEBUG] LIS3MDLTR initialisation success.\n");
	}
	else{
		printf("[ERROR] LIS3MDLTR initialisation failed.\n");
		return 0;
	}

	// Test 1
	get_val = lis3mdltr_GetFullScaleConfig();
	printf("[DEBUG] LIS3MDLTR Current FullScaleConfig : %d\n", get_val);

	// Test 2
	get_val = lis3mdltr_GetDataRate();
	printf("[DEBUG] LIS3MDLTR Current DataRate Setting : %d\n", get_val);
	status = lis3mdltr_SetDataRate(2);
	if (status == STATUS_OK)
	{
		printf("[DEBUG] LIS3MDLTR SetDataRate success.\n");
	}
	else{
		printf("[ERROR] LIS3MDLTR SetDataRate failed.\n");
		return 0;
	}

	// Test 3
	get_val = lis3mdltr_ReadInterruptConfig();
	printf("[DEBUG] LIS3MDLTR Interrupt :  %d\n", get_val);

	status = lis3mdltr_EnableInterrupt();
	if (status == STATUS_OK)
	{
		printf("[DEBUG] LIS3MDLTR EnableInterrupt success.\n");
	}
	else{
		printf("[ERROR] LIS3MDLTR EnableInterrupt failed.\n");
		return 0;
	}

	status = lis3mdltr_DisableInterrupt();
	if (status == STATUS_OK)
	{
		printf("[DEBUG] LIS3MDLTR DisableInterrupt success.\n");
	}
	else{
		printf("[ERROR] LIS3MDLTR DisableInterrupt failed.\n");
		return 0;
	}

	// Test 4
	get_axis_data = lis3mdltr_read_axis_data(AXIS_X);
	printf("[DEBUG] LIS3MDLTR read_axis_data :  %d\n", get_axis_data);
	return 0;
}
