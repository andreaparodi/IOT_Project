/*
 * vector_extraction.h
 *
 *  Created on: 13 feb 2018
 *      Author: andre
 */

#ifndef VECTOR_EXTRACTION_H_
#define VECTOR_EXTRACTION_H_

#include "math.h"

float calculateMean(float vect[], int length);
float calculateVar(float vect[], float mean, int length);
float calculateCov(float vect[]);
float calculateCor(float vect[]);


#endif /* VECTOR_EXTRACTION_H_ */
