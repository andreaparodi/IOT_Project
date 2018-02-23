/*
 * knn.h
 *
 *  Created on: 18 feb 2018
 *      Author: andre
 */

#ifndef KNN_H_
#define KNN_H_

#include "main.h"



float calculateDistance(float feature_vect1[], float feature_vect2[]);
void findKNN(float trainingFeatures[nOfSamples][nOfFeatures], int index[], float sampleFeatures[]);
int classificate(int labels[], int indexes[]);

#endif /* KNN_H_ */
