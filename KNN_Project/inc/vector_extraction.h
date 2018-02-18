/*
 * vector_extraction.h
 *
 *  Created on: 13 feb 2018
 *      Author: andre
 */

#ifndef VECTOR_EXTRACTION_H_
#define VECTOR_EXTRACTION_H_

//lunghezza dei vettori di sampling
#define vectorLength 10
//numero dei vettori di training
#define nOfSamples 20
//numero di features che vengono estratte (media acc, media direz, devstand acc, devstand direz, correlaz acc/direz)
#define nOfFeatures 5
//numero di vicini considerati
#define k 7

#include "math.h"

/*
float calculateMean(float vect[], int length);
float calculateVar(float vect[], float mean, int length);
float calculateCor(float vect[]);
*/

float calculateMean(float vect[]);
float calculateVar(float vect[], float mean);
float calculateCorr(float vect1[], float vect2[], int med1, int med2, int stdDev1, int stdDev2);

#endif /* VECTOR_EXTRACTION_H_ */
