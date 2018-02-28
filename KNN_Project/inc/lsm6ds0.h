/*
 * lsm6ds0.h
 *
 *  Created on: 21 feb 2018
 *      Author: andre
 */


#ifndef LSM6DS0_H_
#define LSM6DS0_H_

#include "i2c.h"

#define LSM6DS0_add				0x6B
#define LSM6DS0_REFERENCE_G  	0x0B
#define LSM6DS0_WHO_AM_I  		0x0F
#define LSM6DS0_Who_am_i_val	0x68
#define LSM6DS0_CTRL_REG1_G  	0X10 //Modificare questi tre basandosi su tabella pag.39
#define LSM6DS0_CTRL_REG2_G		0x11
#define LSM6DS0_CTRL_REG3_G		0x12
#define LSM6DS0_ORIENT_CFG_G	0X13
#define LSM6DS0_OUT_X_L_G		0x18
#define LSM6DS0_OUT_X_H_G		0x19
#define LSM6DS0_OUT_Y_L_G		0x1A
#define LSM6DS0_OUT_Y_H_G		0x1B
#define LSM6DS0_OUT_Z_L_G		0x1C
#define LSM6DS0_OUT_Z_H_G 		0x1D
#define LSM6DS0_CTRL_REG4		0X1E
#define LSM6DS0_CTRL_REG5_XL	0X1F
#define LSM6DS0_CTRL_REG6_XL	0X20
#define LSM6DS0_CTRL_REG7_XL	0X21
#define LSM6DS0_CTRL_REG8		0X22
#define LSM6DS0_CTRL_REG9		0X23
#define LSM6DS0_CTRL_REG10		0X24
#define LSM6DS0_OUT_X_L_XL		0X28
#define LSM6DS0_OUT_X_H_XL		0X29
#define LSM6DS0_OUT_Y_L_XL		0X2A
#define LSM6DS0_OUT_Y_H_XL		0X2B
#define LSM6DS0_OUT_Z_L_XL		0X2C
#define LSM6DS0_OUT_Z_H_XL		0X2D

FunctionalState LSM6DS0_present;

void LSM6DS0_Config();
uint8_t LSM6DS0_Who_Am_I(void);
void LSM6DS0_ReadAcceleration(float vect[]);
void LSM6DS0_ReadGyro(float vect[]);

#endif
