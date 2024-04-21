/*
 * main.c
 *
 *  Created on: 21 Apr 2024
 *      Author: pubu
 */
#include <stdio.h>
#include "lis3mdltr.h"

int main(){
	uint8_t get_val;
	status_t status;
	status = lis3mdltr_init();
	if (status == STATUS_OK)
	{
		printf("[DEBUG] LIS3MDLTR initialisation success.\n");
	}
	else{
		printf("[ERROR] LIS3MDLTR initialisation failed.\n");
		return 0;
	}
	get_val = lis3mdltr_GetFullScaleConfig();
	lis3mdltr_GetDataRate();
	lis3mdltr_SetDataRate(2);

	return 0;
}
