/*
 * lsm6ds0.h
 *
 *  Created on: 21 feb 2018
 *      Author: andre
 */
/* ***********************************************************************
 * Author: Andrea Parodi, Jacopo Fabrini.
 * Libreria sensore LSM6DS0 integrato su expansion board X-NUCLEO-IKS01A1.
 * Questo file contiene la definizione degli indirizzi dei registri interni
 * del sensore e la definizione delle funzioni di verifica funzionamento,
 * lettura e configurazione.
 *************************************************************************/

#ifndef LSM6DS0_H_
#define LSM6DS0_H_

#include "i2c.h"

/************************************************************************
 * Definizione degli indirizzi dei registri del sensore.
 * N.B. Non sono stati definiti tutti i registri interni del sensore
 * ma solo tutti quelli necessari alla sua configurazione e funzionamento.
 * Per maggiori informazioni scaricare il datasheet al seguente indirizzo:
 * www.st.com/resource/en/datasheet/lsm6ds0.pdf
 * Gli indirizzi e contenuti di default dei registri possono essere
 * consultati alle pagine 33-34 del Datasheet.
 ***********************************************************************/

#define LSM6DS0_add				0x6B	//01101011 Slave ADress (SAD). Se il pin SD0/SA0 è collegato a massa l'indirizzo sarà 01101010 (0x6A).[pag.27 Datasheet]
//#define LSM6DS0_REFERENCE_G  	0x0B	-> Non utilizzato?
#define LSM6DS0_WHO_AM_I  		0x0F	//Indirizzo del registro WHO_AM_I
#define LSM6DS0_Who_am_i_val	0x68	//Valore del registro WHO_AM_I, da inviare per avviare la comunicazione.
#define LSM6DS0_CTRL_REG1_G  	0X10	//Indirizzo del primo registro di controllo, associato alla configurazione del giroscopio.
#define LSM6DS0_CTRL_REG2_G		0x11	//Indirizzo del secondo registro di controllo, associato alla configurazione del giroscopio.
#define LSM6DS0_CTRL_REG3_G		0x12	//Indirizzo del terzo registo di controllo, associato alla configurazione del giroscopio.
#define LSM6DS0_ORIENT_CFG_G	0X13	//Indirizzo del registro di configurazione del segno associato ai valori del giroscopio.
#define LSM6DS0_OUT_X_L_G		0x18	//Indirizzo di output degli 8 LSB dell'asse di pitch (X) del giroscopio.
#define LSM6DS0_OUT_X_H_G		0x19	//Indirizzo di output degli 8 MSB dell'asse di pitch (X) del giroscopio.
#define LSM6DS0_OUT_Y_L_G		0x1A	//Indirizzo di output degli 8 LSB dell'asse di roll (Y) del giroscopio.
#define LSM6DS0_OUT_Y_H_G		0x1B	//Indirizzo di output degli 8 MSB dell'asse di roll (Y) del giroscopio.
#define LSM6DS0_OUT_Z_L_G		0x1C	//Indirizzo di output degli 8 LSB dell'asse di yaw (Z) del giroscopio.
#define LSM6DS0_OUT_Z_H_G 		0x1D	//Indirizzo di output degli 8 MSB dell'asse di yaw (Z) del giroscopio.
#define LSM6DS0_CTRL_REG4		0X1E	//Indirizzo del quarto registro di controllo, associato alla configurazione del giroscopio. (Abilitazione assi in output).
#define LSM6DS0_CTRL_REG5_XL	0X1F	//Indirizzo del quinto registro di controllo, associato alla configurazione dell'accelerometro.
#define LSM6DS0_CTRL_REG6_XL	0X20	//Indirizzo del sesto registro di controllo, associato alla configurazione dell'accelerometro.
#define LSM6DS0_CTRL_REG7_XL	0X21	//Indirizzo del settimo registro di controllo, associato alla configurazione dell'accelerometro.
#define LSM6DS0_CTRL_REG8		0X22	//Indirizzo dell'ottavo registro di controllo
#define LSM6DS0_CTRL_REG9		0X23	//Indirizzo del nono registro di controllo
#define LSM6DS0_CTRL_REG10		0X24	//Indirizzo del decimo registro di controllo
#define LSM6DS0_OUT_X_L_XL		0X28	//Indirizzo di output degli 8 LSB di accelerazione sull'asse X dell'accelerometro.
#define LSM6DS0_OUT_X_H_XL		0X29	//Indirizzo di output degli 8 MSB di accelerazione sull'asse X dell'accelerometro.
#define LSM6DS0_OUT_Y_L_XL		0X2A	//Indirizzo di output degli 8 LSB di accelerazione sull'asse Y dell'accelerometro.
#define LSM6DS0_OUT_Y_H_XL		0X2B	//Indirizzo di output degli 8 MSB di accelerazione sull'asse Y dell'accelerometro.
#define LSM6DS0_OUT_Z_L_XL		0X2C	//Indirizzo di output degli 8 LSB di accelerazione sull'asse Z dell'accelerometro.
#define LSM6DS0_OUT_Z_H_XL		0X2D	//Indirizzo di output degli 8 MSB di accelerazione sull'asse Z dell'accelerometro.

FunctionalState LSM6DS0_present;


void LSM6DS0_Config();							//Definizione della funzione di configurazione dei registri di controllo.
uint8_t LSM6DS0_Who_Am_I(void);					//Definizione della funzione di verifica della presenza del sensore sul bus I2C.
void LSM6DS0_ReadAcceleration(float vect[]);	//Definizione della funzione di lettura dei dati dell'accelerometro.
void LSM6DS0_ReadGyro(float vect[]);			//Definizione della funzione di lettura dei dati del giroscopio.

#endif
