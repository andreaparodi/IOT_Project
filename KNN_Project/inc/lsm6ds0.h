/*
 * lsm6ds0.h
 *
 *  Created on: 21 feb 2018
 *      Author: andre
 */
/*
#ifndef LSM6DS0_H_
#define LSM6DS0_H_

#include "main.h"

#define LSM6DS0_add				0x5F	//HTS221 7bit address (<<1|1 for read, <<1&0xFE for write)
#define LSM6DS0_Who_Am_I		0x0F
#define LSM6DS0_Who_Am_I_Val	0xBC //
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

 #ifndef LSM6DS0_H_
 #define LSM6DS0_H_

 #include "i2c.h"
/*
#define ACT_THS  0x04
#define ACT_DUR  0x05
#define INT_GEN_CFG_XL 0x06
#define INT_GEN_THS_X_XL  0x07
#define INT_GEN_THS_Y_XL 0x08
#define INT_GEN_THS_Z_XL 0x09
#define INT_GEN_DUR_XL 0x0A
#define REFERENCE_G  0x0B
#define INT_CTRL 0x0C
*/

 #define LSM6DS0_add			0x5D // nel datasheet non fa riferimento a nessun 0x5F sia per l'hts221 che per questo quindi dovrebbe essere un registro temp

#define LSM6DS0_REFERENCE_G  	0x0B
 #define LSM6DS0_WHO_AM_I  		0x0F
 #define LSM6DS0_CTRL_REG1_G  	0X10 //Modificare questi tre basandosi su tabella pag.39
 #define LSM6DS0_CTRL_REG2_G	0x11
 #define LSM6DS0_CTRL_REG3_G	0x12
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

//#define LSM6DS0_FIFO_CTRL 0x2E inizializzato nel config a valore 11000000 (0xC0)
// usa la FIFO in modalità continua piuttosto che in "ByPass mode"

 FunctionalState LSM6DS0_present;

 //Definizione variabili di uscita/di conversione/ecc.. ->
 //

 void LSM6DS0_Config(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t); //Chiedere Ansovini per registri
 uint8_t LSM6DS0_Who_Am_I(void);
void LSM6DS0_ReadAcceleration(float vect[]);
void LSM6DS0_ReadGyro(float vect[]);

 #endif
