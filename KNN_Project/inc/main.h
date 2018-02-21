#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "vector_extraction.h"
#include "knn.h"
#include "i2c.h"
#include <stdio.h>
#include <string.h>

#ifndef MAIN_H_
#define MAIN_H_

//lunghezza dei vettori di sampling
#define vectorLength 10
//numero dei vettori di training
#define nOfSamples 20
//numero di features che vengono estratte (media acc, media direz, devstand acc, devstand direz, correlaz acc/direz)
#define nOfFeatures 5
//numero di vicini considerati
#define k 7

UART_HandleTypeDef huart2;

//functions
void MX_USART2_UART_Init(void);

#endif /* MAIN_H_ */
