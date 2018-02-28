/*
 * vector_extraction.c
 *
 *  Created on: 13 feb 2018
 *      Author: andre
 */
#include "vector_extraction.h"


float calculateMean(float vect[])
{
	float mean = 0.0;

	int i;
	for (i = 0; i<vectorLength; i++)
	{
		mean = mean + vect[i];
	}
	mean = mean / vectorLength;
	return mean;
}
float calculateVar(float vect[], float mean)
{
	float var = 0.0;
	//int length = sizeof(vect)/sizeof(vect[0]);
	int i;
	for (i = 0; i<vectorLength; i++)
	{
		var += pow((vect[i] - mean), 2);
	}
	var = var / vectorLength;
	return var;
}

float calculateCorr(float vect1[], float vect2[], int med1, int med2, int stdDev1, int stdDev2)
{
	float corr = 0.0;
	float temp = 0.0;
	int i;
	for (i = 0; i<vectorLength; i++)
	{
		temp = (vect1[i] - med1);
		temp = temp * (vect2[i] - med2);
		corr = corr + temp;
		temp = 0.0;
	}
	corr = corr / vectorLength;

	//serve un controllo su deviazioni standard diverse da zero
	int tempStdDev1=fabs(stdDev1);
	int tempStdDev2=fabs(stdDev2);
	if(tempStdDev1<1 || tempStdDev2<1)
	{
		if(stdDev1>0)
		{
			stdDev1=cutoff_correlation;
		}
		else
		{
			stdDev1=-cutoff_correlation;
		}
		if(stdDev2>0)
		{
			stdDev2=cutoff_correlation;
		}
		else
		{
			stdDev2=-cutoff_correlation;
		}
	}
	corr = corr / (stdDev1*stdDev2);
	return corr;
}
