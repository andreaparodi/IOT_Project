/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */
#include "main.h"

int main(void)
{
	HAL_Init();
	MX_USART2_UART_Init();

	LSM6DS0_Config(0x40, 0x00, 0x40, 0x38,0x38,0x40,0x00,0x04,0x00,0x00,0x00);

	//#########PARTE NUOVA##########
	//float vettore1[10] = { 45,4,5,7,2,1,8,66,8,12 };
	char buffer[100];
		char *newline = "\n\r";
		char *tab = "\t";

		float acceleration_data[3];
		float gyro_data[3];
	//float vettore1[10] = { 5,5,5,5,5,5,5,5,5,5 };
	float trainingSetAcceleration[nOfSamples][vectorLength] =
	{
			{ 98,97,102,124,135,100,89,126,89,122 },
			{ 99,102,100,101,99,135,98,90,88,121 },
			{ 105,89,105,107,102,111,86,126,98,125 },
			{ 4,4,4,4,4,5,4,4,4,4 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 97,101,102,99,87,107,89,123,89,127 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};


	float trainingSetDirection[nOfSamples][vectorLength]=
	{
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};



	//etichette del training set (note)
	//
	// 0: appartenenza a "classe1"
	// 1: appartenenza a "classe2"
	int trainingLabels[nOfSamples] = {1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0};

	float trainingSetFeatures[nOfSamples][nOfFeatures];
	/*
		indici trainingFeatures:
		0 : media accelerazione
		1 : media direzione
		2 : deviazione standard accelerazione
		3 : deviazione standard direzione
		4 : correlazione tra accelerazione e direzione
	 */

	//estrazione delle features dei vettori di training
	for (int ri = 0; ri < nOfSamples; ri++)
	{
		trainingSetFeatures[ri][0] = calculateMean(trainingSetAcceleration[ri]);
		trainingSetFeatures[ri][1] = calculateMean(trainingSetDirection[ri]);
		trainingSetFeatures[ri][2] = sqrt(calculateVar(trainingSetAcceleration[ri],trainingSetFeatures[ri][0]));
		trainingSetFeatures[ri][3] = sqrt(calculateVar(trainingSetDirection[ri], trainingSetFeatures[ri][1]));
		trainingSetFeatures[ri][4] = calculateCorr(trainingSetAcceleration[ri], trainingSetDirection[ri], trainingSetFeatures[ri][0], trainingSetFeatures[ri][1], trainingSetFeatures[ri][2], trainingSetFeatures[ri][3]);
	}

	for(int c=0;c<nOfSamples;c++)
	{
		for(int ri = 0; ri<nOfFeatures; ri++)
		{
			snprintf(buffer, sizeof buffer, "%f", trainingSetFeatures[c][ri]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	}

	//float sampleToClassify_acceleration[vectorLength] = { 35,1,2,3,66,0,12,6,18,1 };
	//float sampleToClassify_direction[vectorLength] = { 4,21,6,6,18,10,9,61,12,11 };

	//test
	float sampleToClassify_acceleration[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };
	float sampleToClassify_direction[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };

	float sampleFeatures[nOfFeatures] = { 0 };
	//feature extraction
	sampleFeatures[0] = calculateMean(sampleToClassify_acceleration);
	sampleFeatures[1] = calculateMean(sampleToClassify_direction);
	sampleFeatures[2] = sqrt(calculateVar(sampleToClassify_acceleration, sampleFeatures[0]));
	sampleFeatures[3] = sqrt(calculateVar(sampleToClassify_direction, sampleFeatures[1]));
	sampleFeatures[4] = calculateCorr(sampleToClassify_acceleration, sampleToClassify_direction, sampleFeatures[0], sampleFeatures[1], sampleFeatures[2], sampleFeatures[3]);

	//test per verificare che calculate distance funzioni
	/*
		float sampleFeatures2[nOfFeatures] = { 0 };
		sampleFeatures2[0] = sampleFeatures[0];
		sampleFeatures2[1] = sampleFeatures[1];
		sampleFeatures2[2] = sampleFeatures[2];
		sampleFeatures2[3] = 21;
		sampleFeatures2[4] = sampleFeatures[4];
		float d = calculateDistance(sampleFeatures, sampleFeatures2);
	 */

	int knn_index[nOfSamples] = { 0 };
	for (int i = 0; i < nOfSamples; i++)
	{
		knn_index[i] = i;
	}
	//ordina gli indici contenuti in knn_index in maniera crescente rispetto alla distanza, in maniera da mantenere un
	//riferimento al rispettivo vettore di training
	findKNN(trainingSetFeatures, knn_index, sampleFeatures);

	//char *newline = "\n\r\r";
	//char *tab = "\t";

	//char test[100];
	//char buffer[100];

	for(int i = 0; i<nOfSamples;i++)
	{
		snprintf(buffer, sizeof buffer, "%d", knn_index[i]);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	for(int i = 0; i<nOfSamples;i++)
	{
		int temp=knn_index[i];
			snprintf(buffer, sizeof buffer, "%d", trainingLabels[temp]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);

	//sfrutta gli indici ordinati e va a vedere il rispettivo valore di essi per capire la classe del vettore sampleToClassify
	int sampleLabel = classificate(trainingLabels, knn_index);

	char *class="";
	if (sampleLabel == 0)
	{
		class="classe 1\t\t";
	}
	else
	{
		class="classe 2\t\t";
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)class, strlen(class), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	//int a = 0;

	LSM6DS0_ReadAcceleration();
	LSM6DS0_ReadGyro();

	//#########FINE PARTE NUOVA#####

	//char *c1 = "Acceleration\t\t";
	//char *c2 = "Speed\t\t";
	//char *c3 = "Direction\r\n";
	//int prova = 124;

	for(;;)
	{
		/*
		 snprintf(buffer, sizeof buffer, "%d", varianza1);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
		 */

		//HAL_UART_Transmit(&huart2, (uint8_t*)class, strlen(c1), 0xFFFF);
		//HAL_Delay(100);

		//snprintf(buffer, sizeof buffer, "%d", sampleLabel);
		//HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
		/*
					for(int i = 0; i<nOfSamples;i++)
					{
						snprintf(buffer, sizeof buffer, "%d", knn_index[i]);
						HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
						HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
					}
					HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
		 */
		/*
		HAL_UART_Transmit(&huart2, (uint8_t*)c1, strlen(c1), 0xFFFF);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)c2, strlen(c2), 0xFFFF);
			HAL_Delay(100);
			HAL_UART_Transmit(&huart2, (uint8_t*)c3, strlen(c3), 0xFFFF);
		 */
		HAL_Delay(10000);

	}
}

//inizializzazione della seriale
void MX_USART2_UART_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	HAL_UART_Init(&huart2);
}
//configurazione dei pin per comunicazione

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(huart->Instance==USART2)
	{
		__GPIOA_CLK_ENABLE();
		__USART2_CLK_ENABLE();

		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}
