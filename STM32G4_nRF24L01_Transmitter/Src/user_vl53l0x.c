/*
 * user_vl53l0x.c
 *
 *  Created on: Jan 19, 2022
 *      Author: bot-10
 */


#include "user_vl53l0x.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_api.h"

void user_vl53l0x_init(VL53L0X_DEV Dev)
{


	uint8_t VhvSettings;
	uint8_t PhaseCal;
	uint32_t refSpadCount;
	uint8_t isApertureSpads;

	VL53L0X_Error status;

				status = VL53L0X_DataInit(Dev);
    			if( status ){
    				printf("VL53L0X_DataInit fail: %d\n",status);
    			}

    			status = VL53L0X_StaticInit(Dev);
                if( status ){
                    printf("VL53L0X_StaticInit failed\n");
                }

    			status = VL53L0X_PerformRefSpadManagement(Dev, &refSpadCount, &isApertureSpads);
    			if( status ){
    			   printf("VL53L0X_PerformRefSpadManagement failed\n");
    			}

                status = VL53L0X_PerformRefCalibration(Dev, &VhvSettings, &PhaseCal);
    			if( status ){
    			   printf("VL53L0X_PerformRefCalibration failed %d\n",status);
    			}


                status = VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_SINGLE_RANGING); // Setup in single ranging mode
                if( status ){
                   printf("VL53L0X_Set&DevMode failed\n");
                }

                status = VL53L0X_SetLimitCheckEnable(Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1); // Enable Sigma limit
    			if( status ){
    			   printf("VL53L0X_SetLimitCheckEnable failed\n");
    			}

    			status = VL53L0X_SetLimitCheckEnable(Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1); // Enable Signa limit
    			if( status ){
    			   printf("VL53L0X_SetLimitCheckEnable failed\n");
    			}
}
