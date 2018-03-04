/*
 * lsm6ds0.c
 *
 *  Created on: 21 feb 2018
 *      Author: andre
 */

/**********************************************************************************
 * Author: Andrea Parodi, Jacopo Fabrini.
 * Questo file contiene le funzioni definite nel file lsm6ds0.h
 * Fare riferimento ai commenti esplicativi di tale file in caso di incomprensioni.
 **********************************************************************************/

#include "lsm6ds0.h"

//Funzione di verifica di presenza del sensore sul bus I2C
uint8_t LSM6DS0_Who_Am_I(void)
{
	const uint8_t I2C_RXBUFFERSIZE = 1;
	uint8_t I2C_RxBuffer[I2C_RXBUFFERSIZE];

	I2C_RxBuffer[0] = LSM6DS0_WHO_AM_I;

	HAL_I2C_Master_Transmit(&I2C1Handle, (uint16_t)LSM6DS0_add<<1  & 0xFE, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);
	HAL_I2C_Master_Receive(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, (uint8_t *)&I2C_RxBuffer[0], 1, 10000);

	return I2C_RxBuffer[0];
}

/*********************************************************************************
 * Funzione di configurazione dei registri interni del sensore.
 * In caso di modifica dei valori di configurazione consultare il datasheet da
 * pagina 33 in poi.
 *********************************************************************************/
void LSM6DS0_Config()
{

	const uint8_t I2C_TXBUFFERSIZE = 11;	//Dimensione pari al numero totale di registri inizializzati

	uint8_t I2C_TxBuffer[I2C_TXBUFFERSIZE];

	/********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG1_G: "01100000"
	 * ODR: 119Hz, Cutoff: 38Hz, Gyro full scale: 245dps
	 ********************************************************/
	I2C_TxBuffer[0]		 = 0x60;
	/*********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG2_G: "00000000"
	 * Selezione della configurazione degli interrupt e degli
	 * output di default.
	 ********************************************************/
	I2C_TxBuffer[1]		 = 0x00;
	/*********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG3_G: "00000000"
	 * Selezione della configurazione di default:
	 * Low power disabled, High Pass Filter disabled.
	 *********************************************************/
	I2C_TxBuffer[2]		 = 0x00;
	/**********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG4: "001111000"
	 * Abilitati gli output degli assi X,Y,Z del giroscopio.
	 **********************************************************/
	I2C_TxBuffer[3]		 = 0x38;
	/***********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG5_XL: "001111000"
	 * No decimazione dei valori di output dell'accelerometro
	 * e abilitazione delle uscite sugli assi X,Y,Z.
	 ***********************************************************/
	I2C_TxBuffer[4]		 = 0x38;
	/***********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG6_XL: "01100000"
	 * ODR acc: 119Hz, BW: 50Hz, Full Scale: +/- 2g
	 ***********************************************************/
	I2C_TxBuffer[5]		 = 0x60;
	/**********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG7_XL: "00000000"
	 * High Resolution Mode disabled,High Pass Filter disabled.
	 **********************************************************/
	I2C_TxBuffer[6]		 = 0x00;
	/*********************************************************
	 * Inizializzazione alla configurazione di default
	 * di LSM6DS0_CTRL_REG8: "00000100"
	 * Normal mode, Update continuo, pin interrupt di output
	 * attivo alto, push-pull mode, SPI Mode: 4-wire,
	 * register address automaticamente incrementato durante
	 * accesso a byte multiplo con I2C, LSB @Lower address.
	 *********************************************************/
	I2C_TxBuffer[7]		 = 0x04;
	/***********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG9: "00000000"
	 * FIFO disabled, I2C e SPI enabled.
	 ***********************************************************/
	I2C_TxBuffer[8]		 = 0x00;
	/**********************************************************
	 * Inizializzazione di LSM6DS0_CTRL_REG10: "00000000"
	 * Configurazione di default: self test disabilitati per
	 * entrambi i sensori.
	 **********************************************************/
	I2C_TxBuffer[9]		 = 0x00;
	/***********************************************************
	 * Inizializzazione di LSM6DS0_ORIENT_CFG_G: "00000000"
	 * Selezione della configurazione di default del segno
	 * dell'output del giroscopio: X,Y,Z a segno positivo.
	 **********************************************************/
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

//Funzione di lettura dei dati rilevati dall'accelerometro
void LSM6DS0_ReadAcceleration(float vect[])
{
	const uint8_t	I2C_RXBUFFERSIZE = 2;

	uint8_t I2C_RxBufferX[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferY[I2C_RXBUFFERSIZE];
	uint8_t I2C_RxBufferZ[I2C_RXBUFFERSIZE];

	float X_acc, Y_acc, Z_acc;
	float acc_sensitivity = 3.224669;
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_X_L_G, 1, (uint8_t *)&I2C_RxBufferX[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_X_H_G, 1, (uint8_t *)&I2C_RxBufferX[1], 1, 10000);
	int16_t dataX = (((uint16_t)I2C_RxBufferX[1]<<8 | I2C_RxBufferX[0]));
	X_acc = (float)dataX;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Y_L_G, 1, (uint8_t *)&I2C_RxBufferY[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Y_H_G, 1, (uint8_t *)&I2C_RxBufferY[1], 1, 10000);
	int16_t dataY = (((uint16_t)I2C_RxBufferY[1]<<8 | I2C_RxBufferY[0]));
	Y_acc = (float)dataY;

	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Z_L_G, 1, (uint8_t *)&I2C_RxBufferZ[0], 1, 10000);
	HAL_I2C_Mem_Read(&I2C1Handle, (uint16_t)LSM6DS0_add<<1 | 1, LSM6DS0_OUT_Z_H_G, 1, (uint8_t *)&I2C_RxBufferZ[1], 1, 10000);
	int16_t dataZ = (((uint16_t)I2C_RxBufferZ[1]<<8 | I2C_RxBufferZ[0]));
	Z_acc = (float)dataZ;
	vect[0]=X_acc*acc_sensitivity/1000;
	vect[1]=Y_acc*acc_sensitivity/1000;
	vect[2]=Z_acc*acc_sensitivity/1000;
}

//Funzione di lettura dei dati rilevati dal giroscopio
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
