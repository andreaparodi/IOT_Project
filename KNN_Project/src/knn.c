/*
 * knn.c
 *
 *  Created on: 18 feb 2018
 *      Author: andre
 */
#include "knn.h"
//calcola la distanza tra due vettori calcolando la distanza euclidea tra le features
float calculateDistance(float feature_vect1[], float feature_vect2[])
{
	float distance = 0.0;
	float temp = 0.0;
	for (int i = 0; i < nOfFeatures; i++)
	{
		temp = (feature_vect1[i] - feature_vect2[i]);
		distance = distance + pow(temp, 2);
	}
	temp = 0.0;
	distance = sqrt(distance);
	return distance;
}

//calcola tutte le possibili distanze e le ordina
void findKNN(float trainingFeatures[nOfSamples][nOfFeatures], int index[], float sampleFeatures[])
{
	//copio matrice features per non modificarla nel main
	float temp[nOfSamples][nOfFeatures] = { 0 };
	float distances[nOfSamples] = { 0 };

	for (int ri = 0; ri < nOfSamples; ri++)
	{
		for (int col = 0; col < nOfFeatures; col++)
		{
			temp[ri][col] = trainingFeatures[ri][col];
		}
	}
	//calcolo delle distanze
	for (int i = 0; i < nOfSamples; i++)
	{
		distances[i] = calculateDistance(temp[i], sampleFeatures);
	}
	//codice trovato per il sorting

	//float a[vectorLength] = { 3,4,7,6,5,1,2,8,10,9 };           //Array declaration size-10
	//Temporary number for array size

	/*
	printf("\n\nArray Data : ");                    //Printing message
	for (int i = 0; i < nOfSamples; i++)                     //Loop for displaying the data of array
	{
		printf(" %f ", distances[i]);                   //Printing data
	}
	*/

	for (int i = 0; i <nOfSamples; i++)                     //Loop for ascending ordering
	{
		for (int j = 0; j < nOfSamples; j++)             //Loop for comparing other values
		{
			if (distances[j] > distances[i])                //Comparing other array elements
			{
				float tmp = distances[i];         //Using temporary variable for storing last value
				distances[i] = distances[j];            //replacing value
				distances[j] = tmp;             //storing last value

				int tmpIndex = index[i];
				index[i] = index[j];
				index[j] = tmpIndex;
			}
		}
	}

	/*
	printf("\n\nAscending : ");                     //Printing message
	for (int i = 0; i < nOfSamples; i++)                     //Loop for printing array data after sorting
	{
		printf(" %f ", distances[i]);
	}
	*/

}

int classificate(int labels[], int indexes[])
{
	int score = 0;
	for (int i = 0; i < k; i++)
	{
		//labels contiene 1 oppure 0 a seconda che sia una classe o l'altra
		score = score + labels[i];
	}
	if (score > 3)
		return 1;
	else
		return 0;
}

