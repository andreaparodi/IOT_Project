/*
 * lsm6ds0.c
 *
 *  Created on: 21 feb 2018
 *      Author: andre
 */

#include "lsm6ds0.h"

uint8_t LSM6DS0_Who_Am_I(void)
{
	const uint8_t I2C_RXBUFFERSIZE = 1;
	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];

	I2C_RxBuffer[0] = LSM6DS0_WHO_AM_I;

	HAL_I2C_Master_Transmit(&I2C1Handle, (uint16_t)LSM6DS0_add<<1  & 0xFE, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Master_Receive(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);

	return I2C_RxBuffer[0];
}
void LSM6DS0_Config()
{
	const uint8_t I2C_TXBUFFERSIZE = 11;

	uint8_t I2C_TxBuffer[I2C_TXBUFFERSIZE];

	I2C_TxBuffer[0]		 = 0x60;//0x40
	I2C_TxBuffer[1]		 = 0x00;
	I2C_TxBuffer[2]		 = 0x00;//0x40
	I2C_TxBuffer[3]		 = 0x38;
	I2C_TxBuffer[4]		 = 0x38;
	I2C_TxBuffer[5]		 = 0x60; //0x40 -> forse da non scrivere
	I2C_TxBuffer[6]		 = 0x00;
	I2C_TxBuffer[7]		 = 0x04;//0x04
	I2C_TxBuffer[8]		 = 0x00;
	I2C_TxBuffer[9]		 = 0x00;
	I2C_TxBuffer[10]	 = 0x00;


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
	HAL_I2C_Mem_Write(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 & 0xFE, LSM6DS0_ORIENT_CFG_G, 1, (uint8_t *)&I2C_TxBuffer[10], 1, 10000);
}

void LSM6DS0_ReadAcceleration(float vect[])
{
	const uint8_t	I2C_RXBUFFERSIZE = 2;

	uint8_t I2C_RxBufferX[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferY[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferZ[I2C_RXBUFFERSIZE];

	float X_acc, Y_acc, Z_acc;
	//dato sperimentale
	float acc_sensitivity = 3.224669;
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_X_L_G, 1, (uint8_t *)&I2C_RxBufferX[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_X_H_G, 1, (uint8_t *)&I2C_RxBufferX[1], 1, 10000);
	int16_t dataX = (((uint16_t)I2C_RxBufferX[1]<<8 | I2C_RxBufferX[0]));
	//int16_t dataX = ((((uint16_t)I2C_RxBufferX[1]<<8) +(uint16_t)I2C_RxBufferX[0]));
	dataX = dataX>>4;
	X_acc = (float)dataX;

/*
	char buffer[100];
	char *tab = "\t";
	char *newline = "\n\r";
	*/
	/*
	snprintf(buffer, sizeof buffer, "%d", I2C_RxBufferX[0]);
	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	 */

	//*mH+(float)HTS221_H0_rHx2/2;
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Y_L_G, 1, (uint8_t *)&I2C_RxBufferY[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Y_H_G, 1, (uint8_t *)&I2C_RxBufferY[1], 1, 10000);
	int16_t dataY = (((uint16_t)I2C_RxBufferY[1]<<8 | I2C_RxBufferY[0]));
	//int16_t dataY = ((((uint16_t)I2C_RxBufferY[1]<<8) +(uint16_t)I2C_RxBufferY[0]));
	Y_acc = (float)dataY;
	/*
	snprintf(buffer, sizeof buffer, "%f", Y_acc);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	 */
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Z_L_G, 1, (uint8_t *)&I2C_RxBufferZ[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Z_H_G, 1, (uint8_t *)&I2C_RxBufferZ[1], 1, 10000);
	int16_t dataZ = (((uint16_t)I2C_RxBufferZ[1]<<8 | I2C_RxBufferZ[0]));
	//int16_t dataZ = ((((uint16_t)I2C_RxBufferZ[1]<<8) +(uint16_t)I2C_RxBufferZ[0]));
	Z_acc = (float)dataZ;
	/*
	snprintf(buffer, sizeof buffer, "%f", Z_acc);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	 */
	vect[0]=X_acc*acc_sensitivity/1000;
	vect[1]=Y_acc*acc_sensitivity/1000;
	vect[2]=Z_acc*acc_sensitivity/1000;
}
void LSM6DS0_ReadGyro(float vect[])
{
	const uint8_t	I2C_RXBUFFERSIZE = 2;

	uint8_t I2C_RxBufferX[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferY[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferZ[I2C_RXBUFFERSIZE];

	float X_gyr, Y_gyr, Z_gyr;
	float gyro_sensitivity =8.75;
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_X_L_XL, 1, (uint8_t *)&I2C_RxBufferX[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_X_H_XL, 1, (uint8_t *)&I2C_RxBufferX[1], 1, 10000);
	int16_t dataX = (((uint16_t)I2C_RxBufferX[1]<<8 | I2C_RxBufferX[0]));
	X_gyr = (float)dataX;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Y_L_XL, 1, (uint8_t *)&I2C_RxBufferY[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Y_H_XL, 1, (uint8_t *)&I2C_RxBufferY[1], 1, 10000);
	int16_t dataY = (((uint16_t)I2C_RxBufferY[1]<<8 | I2C_RxBufferY[0]));
	Y_gyr = (float)dataY;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Z_L_XL, 1, (uint8_t *)&I2C_RxBufferZ[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Z_H_XL, 1, (uint8_t *)&I2C_RxBufferZ[1], 1, 10000);
	int16_t dataZ = (((uint16_t)I2C_RxBufferZ[1]<<8 | I2C_RxBufferZ[0]));
	Z_gyr = (float)dataZ;

	vect[0]=X_gyr*gyro_sensitivity/1000;
	vect[1]=Y_gyr*gyro_sensitivity/1000;
	vect[2]=Z_gyr*gyro_sensitivity/1000;
}
