/*
 * vector_extraction.c
 *
 *  Created on: 13 feb 2018
 *      Author: andre
 */
#include "vector_extraction.h"


float calculateMean(float vect[], int length)
{
	float mean =0.0;
	//int length = sizeof(vect)/sizeof(vect[0]);
	int i;
	for(i=0;i<length;i++)
	{
		mean= mean+vect[i];
	}
	mean = mean/length;
	return mean;
}

float calculateVar(float vect[], float mean, int length)
{
	float var=0.0;
	//int length = sizeof(vect)/sizeof(vect[0]);
	int i;
	for(i=0;i<length;i++)
	{
		var+=pow((vect[i]-mean),2);
	}
	var=var/length;

	return var;
}

float calculateCov(float vect[])
{
	float cov=0.0;

	return cov;
}
float calculateCorr(float vect1[], float vect2[], int length, int med1, int med2, int stdDev1, int stdDev2)
{
	float corr=0.0;
	int i;
	for (i=0;i<length;i++)
	{
		corr=(vect1[i]-med1);
		corr=corr*(vect2[i]-med2);
	}
	corr=corr/length;
	corr=corr/(stdDev1*stdDev2);
	return corr;
}
