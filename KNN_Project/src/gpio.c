/*
 * gpio.c
 *
 *  Created on: 24 feb 2018
 *      Author: andre
 */
#include "gpio.h"
void gpioInit(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable the BUTTON Clock */
	__GPIOA_CLK_ENABLE();

	/* Configure Button pin as input */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 0 ,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	__GPIOB_CLK_ENABLE();
	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void HAL_GPIO_EXTI_Callback(uint16_t gpioPin)
{
	if(gpioPin == GPIO_PIN_0)
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);
	}
}

