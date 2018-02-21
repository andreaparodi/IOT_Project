/*
 * lsm6ds0.h
 *
 *  Created on: 21 feb 2018
 *      Author: andre
 */

#ifndef LSM6DS0_H_
#define LSM6DS0_H_

#include "main.h"

#define LSM6DS0_add				0x5F	//HTS221 7bit address (<<1|1 for read, <<1&0xFE for write)
#define LSM6DS0_Who_Am_I		0x0F
#define LSM6DS0_Who_Am_I_Val	0xBC
#define LSM6DS0_AV_Conf			0x10
#define LSM6DS0_CTRL_Reg1		0x20
#define LSM6DS0_CTRL_Reg2		0x21
#define LSM6DS0_CTRL_Reg3		0x22
#define LSM6DS0_Stat_Reg		0x27
#define LSM6DS0_HumidityL		0x28
#define LSM6DS0_HumidityH		0x29
#define LSM6DS0_TempL			0x2A
#define LSM6DS0_TempH			0x2B

FunctionalState	LSM6DS0_present;
int16_t LSM6DS0_H0_T0_Out, LSM6DS0_H1_T0_Out, LSM6DS0_T0_Out, LSM6DS0_T1_Out, LSM6DS0_T0_degC_x8, LSM6DS0_T1_degC_x8;
uint8_t LSM6DS0_H0_rHx2, LSM6DS0_H1_rHx2;
float mT,mH;

void	LSM6DS0_Config(uint8_t, uint8_t, uint8_t, uint8_t );
uint8_t	LSM6DS0_WhoAmI(void);
float	LSM6DS0_ReadHumidity(void);  	//non ha senso
float	LSM6DS0_ReadTemperature(void);	//non ha senso
void	LSM6DS0_ReadCalib(void);



#endif /* LSM6DS0_H_ */
