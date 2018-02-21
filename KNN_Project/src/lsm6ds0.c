/*
 * lsm6ds0.c
 *
 *  Created on: 21 feb 2018
 *      Author: andre
 */

#include "LSM6DS0.h"

 uint8_t LSM6DS0_WhoAmI(void)
{
	const uint8_t I2C_RXBUFFERSIZE = 1;
	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];

	I2C_RxBuffer][0] = LSM6DS0_Who_Am_I;

	HAL_I2C_Master_Transmit(&I2C1Handle, (uint16_t)LSM6DS0_add<<1  & 0xFE, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Master_Receive(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);

	return I2C_RxBuffer[0];
}


 void LSM6DS0_Config(uint8_t ctrl1g, uint8_t ctrl2g, uint8_t ctrl3g, uint8_t ctrl4, uint8_t ctrl5xl, uint8_t ctrl6xl, uint8_t ctrl7xl, uint8_t ctrl8, uint8_t ctrl9, uint8_t ctrl10)
{
 const uint8_t I2C_TXBUFFERSIZE = 10;

 uint8_t I2C_TxBuffer[I2C_TXBUFFERSIZE];

 I2C_TxBuffer[0] = ctrl1g;
 I2C_TxBuffer[1] = ctrl2g;
 I2C_TxBuffer[2] = ctrl3g;
 I2C_TxBuffer[3] = ctrl4;
 I2C_TxBuffer[4] = ctrl5xl;
 I2C_TxBuffer[5] = ctrl6xl;
 I2C_TxBuffer[6] = ctrl7xl;
 I2C_TxBuffer[7] = ctrl8;
 I2C_TxBuffer[8] = ctrl9;
 I2C_TxBuffer[9] = ctrl10;


 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG1_G, 1, (uint8_t *)&I2C_TxBuffer[0], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG2_G, 1, (uint8_t *)&I2C_TxBuffer[1], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG3_G, 1, (uint8_t *)&I2C_TxBuffer[2], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG4, 1, (uint8_t *)&I2C_TxBuffer[3], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG5_XL, 1, (uint8_t *)&I2C_TxBuffer[4], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG6_XL, 1, (uint8_t *)&I2C_TxBuffer[5], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG7_XL, 1, (uint8_t *)&I2C_TxBuffer[6], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG8, 1, (uint8_t *)&I2C_TxBuffer[7], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG9, 1, (uint8_t *)&I2C_TxBuffer[8], 1, 10000);
 HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_REG10, 1, (uint8_t *)&I2C_TxBuffer[9], 1, 10000);
}

//Da inserire la lettura dei dati (->Vedi ultimo lab, commento di seguito)
float[3] LSM6DS0_ReadAcceleration(void)
{
	return acceleration;
}
float[3] LSM6DS0_ReadDirection(void)
{
	return direction;
}

/*float LPS25HB_ReadPressure(void)
{
 const uint8_t I2C_RXBUFFERSIZE = 3;

 uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];

 HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LPS25HB_add<<1 | 1, LPS25HB_press_XL, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
 HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LPS25HB_add<<1 | 1, LPS25HB_press_L, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
 HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LPS25HB_add<<1 | 1, LPS25HB_press_H, 1, (uint8_t *)&I2C_RxBuffer[2], 1, 10000);
 int32_t data = ((uint32_t)I2C_RxBuffer[2]<<16 | (uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0]);
 return (float)data/4096;
}


float HTS221_ReadTemperature(void)
{
 const uint8_t I2C_RXBUFFERSIZE = 2;

 uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];
 float Temperature;

 HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)HTS221_add<<1 | 1, HTS221_TempL, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
 HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)HTS221_add<<1 | 1, HTS221_TempH, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
 int16_t data = (((uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0]));
 Temperature = (float)data*mT+(float)HTS221_T0_degC_x8/8;
 return Temperature;
}*/



/*
#include "lsm6ds0.h"


uint8_t LSM6DS0_WhoAmI(void)
{
	const uint8_t	I2C_RXBUFFERSIZE = 1;
	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];

	I2C_RxBuffer[0] = LSM6DS0_Who_Am_I;
	HAL_I2C_Master_Transmit(&I2C1Handle, (uint16_t)LSM6DS0_add<<1  & 0xFE, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Master_Receive(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	//HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)HTS221_add<<1 | 1, HTS221_Who_Am_I, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	return I2C_RxBuffer[0];
}

float LSM6DS0_ReadHumidity(void)
{
	const uint8_t	I2C_RXBUFFERSIZE = 2;

	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];
	float Humidity;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_HumidityL, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_HumidityH, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
	int16_t data = (((uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0]));
	Humidity = (float)data*mH+(float)LSM6DS0_H0_rHx2/2;
	return Humidity;
}

float LSM6DS0_ReadTemperature(void)
{
	const uint8_t	I2C_RXBUFFERSIZE = 2;

	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];
	float Temperature;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_TempL, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_TempH, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
	int16_t data = (((uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0]));
	Temperature = (float)data*mT+(float)LSM6DS0_T0_degC_x8/8;
	return Temperature;
}

void LSM6DS0_Config(uint8_t AVconf, uint8_t ctrl1, uint8_t ctrl2, uint8_t ctrl3)
{
	const uint8_t	I2C_TXBUFFERSIZE = 4;

	uint8_t I2C_TxBuffer[I2C_TXBUFFERSIZE];

	I2C_TxBuffer[0] = AVconf;
	I2C_TxBuffer[1] = ctrl1;
	I2C_TxBuffer[2] = ctrl2;
	I2C_TxBuffer[3] = ctrl3;

	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_AV_Conf, 1, (uint8_t *)&I2C_TxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_Reg1, 1, (uint8_t *)&I2C_TxBuffer[1], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_Reg2, 1, (uint8_t *)&I2C_TxBuffer[2], 1, 10000);
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_CTRL_Reg3, 1, (uint8_t *)&I2C_TxBuffer[3], 1, 10000);

}

void LSM6DS0_ReadCalib(void)
{
	const uint8_t	I2C_RXBUFFERSIZE = 3;

	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x30, 1, (uint8_t *)&LSM6DS0_H0_rHx2, 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x31, 1, (uint8_t *)&LSM6DS0_H1_rHx2, 1, 10000);

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x32, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x33, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);;
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x35, 1, (uint8_t *)&I2C_RxBuffer[2], 1, 10000);
	LSM6DS0_T0_degC_x8 = ((uint16_t)I2C_RxBuffer[2]<<8 & 0x300) | I2C_RxBuffer[0];
	LSM6DS0_T1_degC_x8 = ((uint16_t)I2C_RxBuffer[2]<<6 & 0x300) | I2C_RxBuffer[1];

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x36, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x37, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
	LSM6DS0_H0_T0_Out = (uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0];

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x3A, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x3B, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
	LSM6DS0_H1_T0_Out = (uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0];

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x3C, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x3D, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
	LSM6DS0_T0_Out = (uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0];

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x3E, 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, 0x3F, 1, (uint8_t *)&I2C_RxBuffer[1], 1, 10000);
	LSM6DS0_T1_Out = (uint16_t)I2C_RxBuffer[1]<<8 | I2C_RxBuffer[0];

	mT=(((float)LSM6DS0_T1_degC_x8/8)-((float)LSM6DS0_T0_degC_x8/8))/(LSM6DS0_T1_Out-LSM6DS0_T0_Out);
	mH=(((float)LSM6DS0_H1_rHx2/2)-((float)LSM6DS0_H0_rHx2/2))/(LSM6DS0_H1_T0_Out-LSM6DS0_H0_T0_Out);

}
*/
