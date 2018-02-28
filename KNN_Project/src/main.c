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
	USART1_Init();
	MX_USART2_UART_Init();
	I2C1_init();

	if(LSM6DS0_Who_Am_I()==LSM6DS0_Who_am_i_val)
	{
		LSM6DS0_present = ENABLE;
		char *msg="\n\rLSM6DS0 found on the I2C bus! \r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
		LSM6DS0_Config();
	}
	else
	{
		char *msg="\n\rNOT FOUND \r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
		LSM6DS0_present = DISABLE;
	}

	char buffer[100];
	char *newline = "\n\r";
	char *tab = "\t";

	int cycleNum=0;

	float acceleration_data[3]={0};
	float gyro_data[3]={0};

	float trainingSetAccelerationX[nOfSamples][vectorLength]=
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
	float trainingSetAccelerationY[nOfSamples][vectorLength]=
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
	float trainingSetAccelerationZ[nOfSamples][vectorLength]=
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
	float trainingSetGyroX[nOfSamples][vectorLength]=
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
	float trainingSetGyroY[nOfSamples][vectorLength]=
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
	float trainingSetGyroZ[nOfSamples][vectorLength]=
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
	/*
	for (int ri = 0; ri < nOfSamples; ri++)
	{
		trainingSetFeatures[ri][0] = calculateMean(trainingSetAcceleration[ri]);
		trainingSetFeatures[ri][1] = calculateMean(trainingSetDirection[ri]);
		trainingSetFeatures[ri][2] = sqrt(calculateVar(trainingSetAcceleration[ri],trainingSetFeatures[ri][0]));
		trainingSetFeatures[ri][3] = sqrt(calculateVar(trainingSetDirection[ri], trainingSetFeatures[ri][1]));
		trainingSetFeatures[ri][4] = calculateCorr(trainingSetAcceleration[ri], trainingSetDirection[ri], trainingSetFeatures[ri][0], trainingSetFeatures[ri][1], trainingSetFeatures[ri][2], trainingSetFeatures[ri][3]);
	}
	 */
	/*
	  indici trainingFeatures:
	  0		media accelerazione x
	  1		media accelerazione y
	  2		media accelerazione z
	  3		media gyro x
	  4		media gyro y
	  5		media gyro z
	  6		dev accelerazione x
	  7		dev accelerazione y
	  8		dev accelerazione z
	  9		dev gyro x
	  10	dev gyro y
	  11	dev gyro z
	  12	corr x
	  13	corr y
	  14	corr z
	 */

	for (int ri = 0; ri < nOfSamples; ri++)
	{
		trainingSetFeatures[ri][0] = calculateMean(trainingSetAccelerationX[ri]);
		trainingSetFeatures[ri][1] = calculateMean(trainingSetAccelerationY[ri]);
		trainingSetFeatures[ri][2] = calculateMean(trainingSetAccelerationZ[ri]);

		trainingSetFeatures[ri][3] = calculateMean(trainingSetGyroX[ri]);
		trainingSetFeatures[ri][4] = calculateMean(trainingSetGyroY[ri]);
		trainingSetFeatures[ri][5] = calculateMean(trainingSetGyroZ[ri]);

		trainingSetFeatures[ri][6] = sqrt(calculateVar(trainingSetAccelerationX[ri],trainingSetFeatures[ri][0]));
		trainingSetFeatures[ri][7] = sqrt(calculateVar(trainingSetAccelerationY[ri],trainingSetFeatures[ri][1]));
		trainingSetFeatures[ri][8] = sqrt(calculateVar(trainingSetAccelerationZ[ri],trainingSetFeatures[ri][2]));

		trainingSetFeatures[ri][9] = sqrt(calculateVar(trainingSetGyroX[ri],trainingSetFeatures[ri][3]));
		trainingSetFeatures[ri][10] = sqrt(calculateVar(trainingSetGyroY[ri],trainingSetFeatures[ri][4]));
		trainingSetFeatures[ri][11] = sqrt(calculateVar(trainingSetGyroZ[ri],trainingSetFeatures[ri][5]));

		trainingSetFeatures[ri][12] = calculateCorr(trainingSetAccelerationX[ri], trainingSetGyroX[ri], trainingSetFeatures[ri][0], trainingSetFeatures[ri][3], trainingSetFeatures[ri][6], trainingSetFeatures[ri][9]);
		trainingSetFeatures[ri][13] = calculateCorr(trainingSetAccelerationY[ri], trainingSetGyroY[ri], trainingSetFeatures[ri][1], trainingSetFeatures[ri][4], trainingSetFeatures[ri][7], trainingSetFeatures[ri][10]);
		trainingSetFeatures[ri][14] = calculateCorr(trainingSetAccelerationZ[ri], trainingSetGyroZ[ri], trainingSetFeatures[ri][2], trainingSetFeatures[ri][5], trainingSetFeatures[ri][8], trainingSetFeatures[ri][11]);
	}
	/*
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
	 */
	//float sampleToClassify_acceleration[vectorLength] = { 35,1,2,3,66,0,12,6,18,1 };
	//float sampleToClassify_direction[vectorLength] = { 4,21,6,6,18,10,9,61,12,11 };

	//test
	/*
	float sampleToClassify_acceleration[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };
	float sampleToClassify_direction[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };

	float sampleFeatures[nOfFeatures] = { 0 };

	sampleFeatures[0] = calculateMean(sampleToClassify_acceleration);
	sampleFeatures[1] = calculateMean(sampleToClassify_direction);
	sampleFeatures[2] = sqrt(calculateVar(sampleToClassify_acceleration, sampleFeatures[0]));
	sampleFeatures[3] = sqrt(calculateVar(sampleToClassify_direction, sampleFeatures[1]));
	sampleFeatures[4] = calculateCorr(sampleToClassify_acceleration, sampleToClassify_direction, sampleFeatures[0], sampleFeatures[1], sampleFeatures[2], sampleFeatures[3]);
	 */
	/*
	float sampleToClassify_accelerationX[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };
	float sampleToClassify_accelerationY[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };
	float sampleToClassify_accelerationZ[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };

	float sampleToClassify_gyroX[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };
	float sampleToClassify_gyroY[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };
	float sampleToClassify_gyroZ[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };

	float sampleFeatures[nOfFeatures] = { 0 };
	 */

	float sampleToClassify_accelerationX[vectorLength] = { 0 };
	float sampleToClassify_accelerationY[vectorLength] = { 0 };
	float sampleToClassify_accelerationZ[vectorLength] = { 0 };

	float sampleToClassify_gyroX[vectorLength] = { 0 };
	float sampleToClassify_gyroY[vectorLength] = { 0 };
	float sampleToClassify_gyroZ[vectorLength] = { 0 };

	float sampleFeatures[nOfFeatures] = { 0 };

	/*
	sampleFeatures[0] = calculateMean(sampleToClassify_accelerationX);
	sampleFeatures[1] = calculateMean(sampleToClassify_accelerationY);
	sampleFeatures[2] = calculateMean(sampleToClassify_accelerationZ);
	sampleFeatures[3] = calculateMean(sampleToClassify_gyroX);
	sampleFeatures[4] = calculateMean(sampleToClassify_gyroY);
	sampleFeatures[5] = calculateMean(sampleToClassify_gyroZ);

	sampleFeatures[6] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
	sampleFeatures[7] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
	sampleFeatures[8] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));
	sampleFeatures[9] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
	sampleFeatures[10] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
	sampleFeatures[11] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));

	sampleFeatures[12] = calculateCorr(sampleToClassify_accelerationX, sampleToClassify_gyroX, sampleFeatures[0], sampleFeatures[3], sampleFeatures[6], sampleFeatures[9]);
	sampleFeatures[13] = calculateCorr(sampleToClassify_accelerationY, sampleToClassify_gyroY, sampleFeatures[1], sampleFeatures[4], sampleFeatures[7], sampleFeatures[10]);
	sampleFeatures[14] = calculateCorr(sampleToClassify_accelerationZ, sampleToClassify_gyroZ, sampleFeatures[2], sampleFeatures[5], sampleFeatures[8], sampleFeatures[11]);
	 */
	int knn_index[nOfSamples] = { 0 };
	for (int i = 0; i < nOfSamples; i++)
	{
		knn_index[i] = i;
	}
	//ordina gli indici contenuti in knn_index in maniera crescente rispetto alla distanza, in maniera da mantenere un
	//riferimento al rispettivo vettore di training
	/*
	findKNN(trainingSetFeatures, knn_index, sampleFeatures);
	 */
	/*
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
	 */
	//sfrutta gli indici ordinati e va a vedere il rispettivo valore di essi per capire la classe del vettore sampleToClassify
	//int sampleLabel = classificate(trainingLabels, knn_index);

	char *class="";
	/*
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
	 */
	/*
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	char *placeHolder = "Acc_X";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Acc_Y";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Acc_Z";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Gyr_X";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Gyr_Y";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Gyr_Z";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	 */
	for(;;)
	{
		/*
		for(int i = 0; i<nOfSamples;i++)
		{
			snprintf(buffer, sizeof buffer, "%d", knn_index[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
		 */
		LSM6DS0_ReadAcceleration(acceleration_data);
		LSM6DS0_ReadGyro(gyro_data);
		/*
		for(int i = 0; i<3;i++)
		{
			snprintf(buffer, sizeof buffer, "%f", acceleration_data[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		for(int i = 0; i<3;i++)
		{
			snprintf(buffer, sizeof buffer, "%f", gyro_data[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
		 */

		if(cycleNum<vectorLength)
		{
			sampleToClassify_accelerationX[cycleNum] = acceleration_data[0];
			sampleToClassify_accelerationY[cycleNum] = acceleration_data[1];
			sampleToClassify_accelerationZ[cycleNum] = acceleration_data[2];

			sampleToClassify_gyroX[cycleNum] = gyro_data[0];
			sampleToClassify_gyroY[cycleNum] = gyro_data[1];
			sampleToClassify_gyroZ[cycleNum] = gyro_data[2];

			cycleNum++;
		}
		else
		{
			cycleNum=0;

			sampleFeatures[0] = calculateMean(sampleToClassify_accelerationX);
			sampleFeatures[1] = calculateMean(sampleToClassify_accelerationY);
			sampleFeatures[2] = calculateMean(sampleToClassify_accelerationZ);
			sampleFeatures[3] = calculateMean(sampleToClassify_gyroX);
			sampleFeatures[4] = calculateMean(sampleToClassify_gyroY);
			sampleFeatures[5] = calculateMean(sampleToClassify_gyroZ);

			sampleFeatures[6] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
			sampleFeatures[7] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
			sampleFeatures[8] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));
			sampleFeatures[9] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
			sampleFeatures[10] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
			sampleFeatures[11] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));

			sampleFeatures[12] = calculateCorr(sampleToClassify_accelerationX, sampleToClassify_gyroX, sampleFeatures[0], sampleFeatures[3], sampleFeatures[6], sampleFeatures[9]);
			sampleFeatures[13] = calculateCorr(sampleToClassify_accelerationY, sampleToClassify_gyroY, sampleFeatures[1], sampleFeatures[4], sampleFeatures[7], sampleFeatures[10]);
			sampleFeatures[14] = calculateCorr(sampleToClassify_accelerationZ, sampleToClassify_gyroZ, sampleFeatures[2], sampleFeatures[5], sampleFeatures[8], sampleFeatures[11]);

					for(int ri = 0; ri<nOfFeatures; ri++)
					{
						snprintf(buffer, sizeof buffer, "%f", sampleFeatures[ri]);
						HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
						HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
					}
					HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);

			/*
			for (int i = 0; i < nOfSamples; i++)
			{
				knn_index[i] = i;
			}
			findKNN(trainingSetFeatures, knn_index, sampleFeatures);
			sampleLabel = classificate(trainingLabels, knn_index);
			class="";
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
			 */
		}
		HAL_Delay(250);
	}
}
	/*
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
	 */
	//configurazione dei pin per comunicazione

	/*
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

		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}
	 */
