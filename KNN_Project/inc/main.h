#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "vector_extraction.h"
#include "knn.h"
#include "i2c.h"
#include "lsm6ds0.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

#ifndef MAIN_H_
#define MAIN_H_

//elementi di ogni vettore di training o di sample
#define vectorLength 50
//numero dei vettori di training
#define nOfSamples 100
//numero di features che vengono estratte (media acc, media direz, devstand acc, devstand direz, correlaz acc/direz)
#define nOfFeatures 15
//numero di vicini considerati
#define k 7
//numero di campionamenti in un secondo
#define sampleTime 100

UART_HandleTypeDef huart2;
UART_HandleTypeDef UARTHandle1;

#endif /* MAIN_H_ */
