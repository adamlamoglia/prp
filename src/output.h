/*
 * output.h
 *
 *  Created on: 10 de jul de 2018
 *      Author: adamr
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "input.h"


class Output {

public:
	//Represents a pointer to class Input.
	Input *in;

	//Used to output a sequence of nodes representing the vertex of graph that was visited.
	vector<int> route;

	//Sequence of indexes related to vehicle route
	vector<int> index;

	Output(Input *in);

	void printDistanceMatrix();

	void printRoute();

	void printIndexes();

	void printFitness();

	void printArray2d();

	void fitness_set(int f);

	int fitness_get();
private:
	//Represents the value of route.
	int fitness;
};

#endif /* OUTPUT_H_ */
