/*
 * usart.h
 *
 *  Created on: 24 feb 2018
 *      Author: andre
 */

#ifndef USART_H_
#define USART_H_

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

void USART1_Init();
//void USART2_Init();
void MX_USART2_UART_Init(void);
void HAL_UART_MspInit();
void HAL_UART_MspDeInit();
UART_HandleTypeDef HandleSelect(int portNum);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* USART_H_ */
